// Sensor board: read the LSM6DSOX, send each fresh six-axis sample by ESP-NOW,
// and expose the same readings over USB for bench checks.
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_system.h>
#include <SensorPacket.h>

// Station MAC of the paired receiver. Update this if the receiver is replaced.
constexpr uint8_t DISPLAY_MAC[6] = {0x44,0x1B,0xF6,0xCE,0x62,0xE4};
bool radioReady = false;
bool sendBusy = false;
uint32_t sessionId = 0, txDelivered = 0, txFailed = 0, txSkipped = 0;

// This callback runs on the Wi-Fi task. It only updates counters and signals
// the acquisition loop that it can submit the next sample.
void onSent(const esp_now_send_info_t *, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) __atomic_fetch_add(&txDelivered, 1u, __ATOMIC_RELAXED);
  else __atomic_fetch_add(&txFailed, 1u, __ATOMIC_RELAXED);
  __atomic_store_n(&sendBusy, false, __ATOMIC_RELEASE);
}

void startRadio() {
  if (!WiFi.mode(WIFI_STA)) return;
  WiFi.setSleep(false);
  if (esp_wifi_set_channel(sensorlink::CHANNEL, WIFI_SECOND_CHAN_NONE) != ESP_OK ||
      esp_now_init() != ESP_OK || esp_now_register_send_cb(onSent) != ESP_OK) return;
  esp_now_peer_info_t peer{};
  memcpy(peer.peer_addr, DISPLAY_MAC, 6);
  peer.channel = sensorlink::CHANNEL;
  peer.ifidx = WIFI_IF_STA;
  peer.encrypt = false;
  radioReady = esp_now_add_peer(&peer) == ESP_OK;
  sessionId = esp_random();
}

// Adafruit ESP32-S3 Feather: SDA=GPIO3, SCL=GPIO4, I2C_POWER=GPIO7.
// Use the selected Feather board's pin definitions, not the display's pins.
// Register definitions and sensitivities: ST LSM6DSOX datasheet.
constexpr uint8_t WHO_AM_I = 0x0F;
constexpr uint8_t CTRL1_XL = 0x10;
constexpr uint8_t CTRL2_G = 0x11;
constexpr uint8_t CTRL3_C = 0x12;
constexpr uint8_t STATUS_REG = 0x1E;
constexpr uint8_t OUTX_L_G = 0x22;
constexpr float ACCEL_SCALE = 0.000122f * 9.80665f; // +/-4 g -> m/s^2
constexpr float GYRO_SCALE = 0.0175f * PI / 180.0f; // +/-500 deg/s -> rad/s

uint8_t imuAddress = 0;
bool ready = false;
bool hostConnected = false;
uint32_t lastAttemptMs = 0;
uint32_t lastSampleMs = 0;
uint32_t sequence = 0;
uint32_t readErrors = 0;
uint32_t serialDrops = 0;
char serialRow[160];
size_t serialLength = 0, serialOffset = 0;

void flushSerialRow() {
  if (!Serial || serialOffset >= serialLength) return;
  const int space = Serial.availableForWrite();
  if (space <= 0) return;
  size_t count = serialLength - serialOffset;
  if (count > size_t(space)) count = size_t(space);
  serialOffset += Serial.write(reinterpret_cast<const uint8_t *>(serialRow + serialOffset), count);
}

bool readRegisters(uint8_t reg, uint8_t *data, size_t length) {
  Wire.beginTransmission(imuAddress);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(imuAddress, length, true) != length) {
    while (Wire.available()) Wire.read();
    return false;
  }
  for (size_t i = 0; i < length; ++i) data[i] = Wire.read();
  return true;
}

bool writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(imuAddress);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission() == 0;
}

// Check both address straps, then verify the chip and its sampling settings.
bool configureImu() {
  uint8_t value = 0;
  bool found = false;
  for (uint8_t address : {0x6A, 0x6B}) {
    imuAddress = address;
    if (readRegisters(WHO_AM_I, &value, 1) && value == 0x6C) {
      found = true;
      break;
    }
  }
  if (!found || !writeRegister(CTRL3_C, 0x01)) return false;
  const uint32_t resetStarted = millis();
  do {
    delay(1);
    if (!readRegisters(CTRL3_C, &value, 1)) return false;
    if (millis() - resetStarted > 100) return false;
  } while (value & 0x01);

  // BDU + register auto-increment; disable I3C; 104 Hz on both sensors.
  if (!writeRegister(CTRL3_C, 0x44) || !writeRegister(0x18, 0x02) ||
      !writeRegister(CTRL1_XL, 0x48) || !writeRegister(CTRL2_G, 0x44)) return false;
  uint8_t config[3];
  if (!readRegisters(CTRL1_XL, config, sizeof(config)) ||
      config[0] != 0x48 || config[1] != 0x44 || config[2] != 0x44) return false;
  delay(100); // Allow the gyro to settle after power-up.
  lastSampleMs = millis();
  return true;
}

int16_t signedWord(const uint8_t *data) {
  const uint16_t word = uint16_t(data[0]) | (uint16_t(data[1]) << 8);
  return word < 0x8000 ? int16_t(word) : int16_t(int32_t(word) - 65536);
}

void printHeader() {
  Serial.println("# Feather LSM6DSOX: 104 Hz, +/-4 g, +/-500 deg/s; raw, uncalibrated");
  Serial.println("# h=header/help; d=diagnostics; acceleration includes gravity");
  Serial.println("# ESP-NOW channel 1 -> display 44:1B:F6:CE:62:E4; USB does not gate wireless");
  Serial.println("sequence,sample_us,ax_m_s2,ay_m_s2,az_m_s2,gx_rad_s,gy_rad_s,gz_rad_s");
}

void sensorFault(const char *reason) {
  ++readErrors;
  ready = false;
  lastAttemptMs = millis();
  if (Serial) Serial.printf("# ERROR: %s; retrying in 2 seconds\n", reason);
}

void setup() {
  Serial.begin(115200);
  // Windows serial handshake changes must not reboot acquisition into ROM.
  // Enter download mode manually with BOOT/RESET for subsequent uploads.
  Serial.enableReboot(false);
  // Do not wait for USB: acquisition also works without a serial monitor.
#ifdef I2C_POWER
  pinMode(I2C_POWER, OUTPUT);
  digitalWrite(I2C_POWER, HIGH);
#endif
  delay(20);
  Wire.begin(SDA, SCL);
  Wire.setClock(400000);
  Wire.setTimeOut(20);
  startRadio();
  lastAttemptMs = millis() - 2000;
}

void loop() {
  const bool connected = bool(Serial);
  if (!connected) serialOffset = serialLength = 0;
  flushSerialRow();
  if (connected && !hostConnected) printHeader();
  hostConnected = connected;
  // Finish any partial CSV row before writing command diagnostics.
  if (Serial.available() && serialOffset >= serialLength) {
    const char command = Serial.read();
    if (command == 'h') printHeader();
    if (command == 'd') {
      Serial.printf("# ready=%u address=0x%02X samples=%lu read_errors=%lu serial_drops=%lu uptime_ms=%lu\n",
                    ready, imuAddress, (unsigned long)sequence, (unsigned long)readErrors,
                    (unsigned long)serialDrops, (unsigned long)millis());
      Serial.printf("# radio=%u tx_delivered=%lu tx_failed=%lu tx_skipped=%lu session=%lu mac=%s\n",
        radioReady, (unsigned long)__atomic_load_n(&txDelivered, __ATOMIC_RELAXED),
        (unsigned long)__atomic_load_n(&txFailed, __ATOMIC_RELAXED),
        (unsigned long)txSkipped, (unsigned long)sessionId, WiFi.macAddress().c_str());
    }
  }
  if (!ready) {
    if (millis() - lastAttemptMs >= 2000) {
      lastAttemptMs = millis();
      ready = configureImu();
      if (Serial) {
        if (ready) Serial.printf("# LSM6DSOX ready at 0x%02X; configuration verified\n", imuAddress);
        else Serial.println("# ERROR: LSM6DSOX not ready; check power, SDA/SCL and sensor model; retrying");
      }
    }
    delay(1);
    return;
  }

  // Both data-ready bits must be set before reading the six axes in one burst.
  uint8_t status = 0;
  if (!readRegisters(STATUS_REG, &status, 1)) {
    sensorFault("I2C status read failed");
    return;
  }
  if ((status & 0x03) != 0x03) {
    if (millis() - lastSampleMs > 500) sensorFault("no fresh accelerometer/gyro data");
    delay(1);
    return;
  }
  uint8_t data[12]; // Gyro XYZ followed by accelerometer XYZ, little endian.
  const uint32_t sampleUs = micros(); // Host acquisition time, wraps after ~71 min.
  if (!readRegisters(OUTX_L_G, data, sizeof(data))) {
    sensorFault("incomplete I2C sample");
    return;
  }
  lastSampleMs = millis();
  const uint32_t sampleSequence = sequence++;
  sensorlink::Packet packet;
  packet.session = sessionId;
  packet.sequence = sampleSequence;
  packet.sampleUs = sampleUs;
  for (unsigned i = 0; i < 3; ++i) {
    packet.axes[i] = signedWord(data + 6 + i * 2) * ACCEL_SCALE;
    packet.axes[i+3] = signedWord(data + i * 2) * GYRO_SCALE;
  }
  // Only one outstanding send; keep acquisition moving if the receiver is off.
  if (radioReady && !__atomic_exchange_n(&sendBusy, true, __ATOMIC_ACQ_REL)) {
    if (esp_now_send(DISPLAY_MAC, reinterpret_cast<uint8_t *>(&packet), sizeof(packet)) != ESP_OK) {
      __atomic_fetch_add(&txFailed, 1u, __ATOMIC_RELAXED);
      __atomic_store_n(&sendBusy, false, __ATOMIC_RELEASE);
    }
  } else ++txSkipped;
  char row[160];
  const int length = snprintf(row, sizeof(row), "%lu,%lu,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f\n",
      (unsigned long)sampleSequence, (unsigned long)sampleUs,
      signedWord(data + 6) * ACCEL_SCALE, signedWord(data + 8) * ACCEL_SCALE,
      signedWord(data + 10) * ACCEL_SCALE, signedWord(data) * GYRO_SCALE,
      signedWord(data + 2) * GYRO_SCALE, signedWord(data + 4) * GYRO_SCALE);
  // USB may have fewer bytes of free space than a complete CSV row. Send in
  // bounded chunks across loop iterations; never hold up sensor acquisition.
  if (connected) {
    if (length > 0 && length < int(sizeof(row)) && serialOffset >= serialLength) {
      memcpy(serialRow, row, length);
      serialLength = length;
      serialOffset = 0;
      flushSerialRow();
    } else {
      ++serialDrops;
    }
  }
}
