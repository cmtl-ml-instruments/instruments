// Bench receiver: validate Feather packets, apply the C4 tilt gate, and report
// note transitions and link health over USB.
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <SensorPacket.h>
#include "TiltNote.h"

// Station MAC of the paired Feather. Update this if the transmitter is replaced.
constexpr uint8_t FEATHER_MAC[6] = {0xF0,0x9E,0x9E,0x74,0x26,0x90};
struct Received {
  sensorlink::Packet packet;
  uint32_t receivedMs; // Receiver clock, used for freshness and note timing.
};
QueueHandle_t incoming = nullptr;
Received latest{};
bool haveSample = false, radioReady = false;
bool packetTestPassed = false;
uint32_t accepted = 0, invalid = 0, missed = 0, old = 0;
uint32_t queueDrops = 0, foreign = 0;
uint32_t lastReportMs = 0, lastRateMs = 0, lastRateCount = 0;
float receiveHz = 0;
TiltNote tiltNote;
float rollDegrees = 0;
TiltNote::Event pendingNote = TiltNote::Event::None;
uint32_t noteChanges = 0;
char reportBuffer[768];
size_t reportLength = 0, reportOffset = 0;

// Limit serial work so the radio queue can drain even with a slow USB reader.
void flushReport() {
  if (!Serial) { reportLength = reportOffset = 0; return; }
  if (reportOffset >= reportLength) return;
  const int space = Serial.availableForWrite();
  if (space <= 16) return; // Leave room for ring-buffer bookkeeping.
  size_t count = reportLength - reportOffset;
  if (count > 32) count = 32;
  if (count > size_t(space - 16)) count = size_t(space - 16);
  reportOffset += Serial.write(reinterpret_cast<const uint8_t *>(reportBuffer + reportOffset), count);
}

// Wi-Fi task: copy only. Parsing and logging run outside this callback.
void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int length) {
  if (!info || memcmp(info->src_addr, FEATHER_MAC, 6) != 0) {
    __atomic_fetch_add(&foreign, 1u, __ATOMIC_RELAXED);
    return;
  }
  if (length != sizeof(sensorlink::Packet)) {
    __atomic_fetch_add(&invalid, 1u, __ATOMIC_RELAXED);
    return;
  }
  Received row;
  memcpy(&row.packet, data, sizeof(row.packet));
  row.receivedMs = millis();
  if (xQueueSend(incoming, &row, 0) != pdTRUE) __atomic_fetch_add(&queueDrops, 1u, __ATOMIC_RELAXED);
}

bool live() {
  return radioReady && haveSample && millis() - latest.receivedMs < sensorlink::STALE_MS;
}

void rememberNoteEvent(TiltNote::Event event) {
  if (event == TiltNote::Event::None) return;
  // Keep the latest event if USB falls behind. Event numbers expose skipped logs.
  pendingNote = event;
  ++noteChanges;
}

void printNoteEvent() {
  using Event = TiltNote::Event;
  if (pendingNote == Event::None || !Serial || reportOffset < reportLength) return;
  const char *reason = "tilt";
  switch (pendingNote) {
    case Event::Released: reason = "released"; break;
    case Event::LinkLost: reason = "link_lost"; break;
    case Event::Restarted: reason = "feather_restarted"; break;
    default: break;
  }
  const int length = snprintf(reportBuffer, sizeof(reportBuffer),
    "# NOTE %s midi=%d reason=%s event=%lu\n",
    pendingNote == Event::On ? "ON" : "OFF", TiltNote::midiNote,
    reason, (unsigned long)noteChanges);
  if (length <= 0 || length >= int(sizeof(reportBuffer))) return;
  reportLength = length;
  reportOffset = 0;
  pendingNote = Event::None;
}

void printStatus() {
  if (!Serial || reportOffset < reportLength) return;
  int length = snprintf(reportBuffer, sizeof(reportBuffer), "# RECEIVER mode=HEADLESS radio=%u selftest=%u link=%s mac=%s channel=%u packets=%lu hz=%.1f missed=%lu invalid=%lu old=%lu queue_drops=%lu foreign=%lu age_ms=%lu note=%s armed=%u\n",
    radioReady, packetTestPassed, live() ? "LIVE" : (haveSample ? "LOST" : "WAITING"),
    WiFi.macAddress().c_str(), sensorlink::CHANNEL, (unsigned long)accepted, receiveHz,
    (unsigned long)missed, (unsigned long)__atomic_load_n(&invalid, __ATOMIC_RELAXED), (unsigned long)old,
    (unsigned long)__atomic_load_n(&queueDrops, __ATOMIC_RELAXED),
    (unsigned long)__atomic_load_n(&foreign, __ATOMIC_RELAXED),
    (unsigned long)(haveSample ? millis() - latest.receivedMs : 0),
    tiltNote.active ? "ON" : "OFF", tiltNote.armed);
  if (length <= 0 || length >= int(sizeof(reportBuffer))) return;
  reportLength = length;
  reportOffset = 0;
  if (live()) length = snprintf(reportBuffer + reportLength, sizeof(reportBuffer) - reportLength,
    "# AXES %.5f,%.5f,%.5f,%.5f,%.5f,%.5f sequence=%lu session=%lu roll_deg=%.1f\n",
    latest.packet.axes[0], latest.packet.axes[1], latest.packet.axes[2],
    latest.packet.axes[3], latest.packet.axes[4], latest.packet.axes[5],
    (unsigned long)latest.packet.sequence, (unsigned long)latest.packet.session, rollDegrees);
  else length = 0;
  if (length > 0 && size_t(length) < sizeof(reportBuffer) - reportLength) reportLength += length;
}

void setup() {
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0);
#if !ARDUINO_USB_MODE && ARDUINO_USB_CDC_ON_BOOT
  Serial.enableReboot(false);
#endif
  packetTestPassed = sensorlink::selfTest();
  incoming = xQueueCreate(32, sizeof(Received));
  if (packetTestPassed && incoming && WiFi.mode(WIFI_STA)) {
    WiFi.setSleep(false);
    radioReady = esp_wifi_set_channel(sensorlink::CHANNEL, WIFI_SECOND_CHAN_NONE) == ESP_OK &&
      esp_now_init() == ESP_OK && esp_now_register_recv_cb(onReceive) == ESP_OK;
  }
  lastRateMs = millis();
  printStatus();
}

void loop() {
  flushReport();
  Received row;
  for (unsigned count = 0; incoming && count < 32 && xQueueReceive(incoming, &row, 0) == pdTRUE; ++count) {
    sensorlink::Packet packet;
    if (!sensorlink::decode(reinterpret_cast<uint8_t *>(&row.packet), sizeof(row.packet), packet)) {
      __atomic_fetch_add(&invalid, 1u, __ATOMIC_RELAXED);
      continue;
    }
    if (haveSample && packet.session == latest.packet.session) {
      // Unsigned subtraction handles sequence wrap. A new boot has its own baseline.
      const uint32_t step = packet.sequence - latest.packet.sequence;
      if (step == 0 || step >= 0x80000000u) { ++old; continue; }
      missed += step - 1;
    }
    latest = row;
    haveSample = true;
    ++accepted;
    // An old queued sample can be counted for diagnostics but cannot play a note.
    if (millis() - row.receivedMs < sensorlink::STALE_MS) {
      rollDegrees = atan2f(packet.axes[1], packet.axes[2]) * 57.2957795f;
      rememberNoteEvent(tiltNote.sample(rollDegrees, row.receivedMs, packet.session));
    }
  }
  const uint32_t now = millis();
  rememberNoteEvent(tiltNote.expire(now));
  printNoteEvent();
  if (now - lastRateMs >= 1000) {
    receiveHz = (accepted - lastRateCount) * 1000.0f / (now - lastRateMs);
    lastRateCount = accepted;
    lastRateMs = now;
  }
  if (Serial.available()) {
    const char command = Serial.read();
    if (command == 'd' || command == 'h') printStatus();
  }
  if (now - lastReportMs >= 2000) { lastReportMs = now; printStatus(); }
  delay(1);
}
