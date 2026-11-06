// 3.5-inch instrument: read the local IMU and map motion to AMY synthesis.
// A separate task draws the latest dashboard snapshot.
#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "ST77922.h"
#include "ES8311.h"
#include <AMY-Arduino.h>
#include "GestureControl.h"
#include "DisplayState.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

// --- Hardware Pin Definitions ---
#define I2C_SDA      38
#define I2C_SCL      39
#define LCD_BL_PIN   41

// I2S Pins for Audio Codec
#define I2S_MCK_PIN  17
#define I2S_BCK_PIN  18
#define I2S_WS_PIN   21
#define I2S_DOUT_PIN 15

// Objects
Adafruit_LSM6DSOX sox;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);
ST77922 mylcd = ST77922();

bool spriteReady = false;
bool imuReady = false;
QueueHandle_t displayQueue = nullptr;

// --- C Major Scale: C3 through C6 ---
const int scaleNotes[] = { 
  48, 50, 52, 53, 55, 57, 59,  // C3, D3, E3, F3, G3, A3, B3
  60, 62, 64, 65, 67, 69, 71,  // C4, D4, E4, F4, G4, A4, B4
  72, 74, 76, 77, 79, 81, 83,  // C5, D5, E5, F5, G5, A5, B5
  84                           // C6
};
const char* noteNames[] = {
  "C3", "D3", "E3", "F3", "G3", "A3", "B3",
  "C4", "D4", "E4", "F4", "G4", "A4", "B4",
  "C5", "D5", "E5", "F5", "G5", "A5", "B5",
  "C6"
};
const int totalScaleNotes = sizeof(scaleNotes) / sizeof(scaleNotes[0]);

// --- Exponential Moving Average (EMA) Filter Variables ---
float ema_ax = 0.0f, ema_ay = 0.0f, ema_az = 9.8f;
float ema_gx = 0.0f, ema_gy = 0.0f, ema_gz = 0.0f;
// EMA time constant; alpha is adjusted to the actual elapsed sample time.
const float EMA_TAU_SECONDS = 0.048f;
gesture::Calibration calibration;
int baseNoteIndex = 10;
uint32_t lastSensorUs = 0;
uint32_t lastDisplayMs = 0;
bool recording = false;
uint8_t gestureLabel = 0; // 0=still, 1=flick, 2=shake, 3=tilt
uint32_t recordingSegment = 0;
uint32_t droppedRows = 0;
uint32_t lastRecordUs = 0;
char recordBuffer[240];
size_t recordLength = 0, recordOffset = 0;
const char *gestureLabels[] = {"still", "flick", "shake", "tilt"};
bool synthPlaying = false;

void muteSynth() {
  char message[] = "v0l0";
  amy_add_message(message);
  synthPlaying = false;
}

// Bound serial work per loop; a slow/disconnected host cannot block sampling.
void flushRecording() {
  if (recordOffset < recordLength && Serial) {
    int space = Serial.availableForWrite();
    if (space > 0) {
      size_t count = recordLength - recordOffset;
      if (count > static_cast<size_t>(space)) count = space;
      recordOffset += Serial.write(reinterpret_cast<const uint8_t *>(recordBuffer + recordOffset), count);
    }
  }
}

// USB commands manage calibration and labeled recording segments.
void handleCommands() {
  if (!Serial.available()) return;
  char command = Serial.read();
  if (command == 's') {
    // Finish any partial CSV row before printing diagnostic messages.
    recording = false;
    if (recordOffset < recordLength) {
      // The remainder is small and this explicit stop is outside sampling.
      Serial.write(reinterpret_cast<const uint8_t *>(recordBuffer + recordOffset), recordLength - recordOffset);
    }
    recordOffset = recordLength = 0;
    Serial.printf("# Recording stopped; dropped_rows=%lu\n", (unsigned long)droppedRows);
  } else if (recording) {
    // Freeze the label and calibration for the duration of each segment.
    return;
  } else if (command == 'd') {
    Serial.printf("# CAL count=%u/%u ready=%d collecting=%d rejected=%lu reason=%s std=%.4f norm_a=%.4f norm_g=%.4f\n",
      calibration.count, gesture::Calibration::required, calibration.ready, calibration.collecting,
      (unsigned long)calibration.rejectedWindows, calibration.reason, calibration.rejectedStd,
      calibration.gravityNorm, calibration.rotationNorm);
    Serial.printf("# RAW accel_m_s2=%.4f,%.4f,%.4f gyro_rad_s=%.4f,%.4f,%.4f\n",
      calibration.latest[0], calibration.latest[1], calibration.latest[2],
      calibration.latest[3], calibration.latest[4], calibration.latest[5]);
  } else if (command >= '0' && command <= '3') {
    gestureLabel = command - '0';
    Serial.printf("# Label: %s\n", gestureLabels[gestureLabel]);
  } else if (command == 'c' && imuReady) {
    calibration.begin();
    Serial.println("# Background gyro calibration: hold still when convenient; playing remains active.");
  } else if (command == 'r') {
    if (!calibration.ready || calibration.collecting) {
      Serial.println("# Finish calibration before recording.");
      return;
    }
    ++recordingSegment;
    droppedRows = 0;
    recordOffset = recordLength = 0;
    lastRecordUs = micros();
    Serial.println("# Mapping: fixed_sensor_tilt_v2; calibration corrects gyro bias only; roll/pitch columns are absolute sensor tilt.");
    Serial.printf("# Segment %lu; label=%s; gyro_bias_rad_s=%.6f,%.6f,%.6f; resting_reference_deg=%.3f,%.3f\n",
      (unsigned long)recordingSegment, gestureLabels[gestureLabel],
      calibration.gyroBias[0], calibration.gyroBias[1], calibration.gyroBias[2],
      calibration.rollZero, calibration.pitchZero);
    Serial.println("sample_us,segment,label,ax_m_s2,ay_m_s2,az_m_s2,gx_rad_s,gy_rad_s,gz_rad_s,roll_deg,pitch_deg");
    recording = true;
  } else if (command == 'h') {
    Serial.println("# c=calibrate; d=diagnostics; 0=still 1=flick 2=shake 3=tilt; r=record; s=stop. Stop before changing label.");
  }
}

// --- Dynamic Instrument State ---
int activeNoteIndex = 10;    // Original fixed mapping: level selects F4.
int previousNoteIndex = -1;
int octaveShift = 0;         // -1, 0, +1 based on forward/backward tilt
float currentFilterCutoff = 2000.0f; // Hz (controlled by tilt pitch)
float currentVibrato = 0.0f;         // Depth controlled by gyro rate
float currentVelocity = 0.8f;        // Controlled by motion intensity
unsigned long lastSoundUpdateTime = 0;

// Convert MIDI Note to Base Frequency in Hz
float midiToFreq(int note) {
  return 440.0f * powf(2.0f, (note - 69.0f) / 12.0f);
}

void updateSynthSound(int note, float filterCutoff, float velocity, float pitchBendSemitones = 0.0f) {
  float baseFreq = midiToFreq(note);
  float finalFreq = baseFreq * powf(2.0f, pitchBendSemitones / 12.0f);

  // AMY voice update:
  // A positive l is a note-on trigger, not a continuous volume control.
  // Start the oscillator once; change frequency/filter/gain without re-triggering.
  char msg[96];
  const float gain = 0.85f * constrain(velocity, 0.0f, 1.0f);
  if (!synthPlaying) {
    snprintf(msg, sizeof(msg), "v0w0f%.1fF%.0fa%.3fl1", finalFreq, filterCutoff, gain);
  } else {
    snprintf(msg, sizeof(msg), "v0f%.1fF%.0fa%.3f", finalFreq, filterCutoff, gain);
  }
  amy_add_message(msg);
  synthPlaying = true;
}

void renderDashboard(const DisplayState &state) {
  const int activeNoteIndex = state.noteIndex;
  const int octaveShift = state.octave;
  const float currentFilterCutoff = state.cutoff;
  const float currentVibrato = state.vibrato;
  const float currentVelocity = state.velocity;
  const float tilt_roll = state.roll;
  const float tilt_pitch = state.pitch;
  const float gyro_rate = state.gyroRate;
  const bool recording = state.recording;
  const uint8_t gestureLabel = state.label;
  canvas.fillSprite(TFT_BLACK);

  // Header Bar
  canvas.fillRect(0, 0, 480, 34, 0x0187); // Deep teal
  canvas.setTextColor(TFT_WHITE, 0x0187);
  canvas.drawString("GESTURAL SYNTH: IMU SCALE INFLUENCE", 12, 7, 4);
  canvas.fillCircle(458, 17, 6, state.calibrating ? TFT_ORANGE : (recording ? TFT_RED : TFT_GREEN));

  // Current Played Note Display (Giant Center Banner)
  canvas.fillRoundRect(10, 42, 460, 72, 8, 0x10A2); // Midnight navy card
  canvas.drawRoundRect(10, 42, 460, 72, 8, TFT_CYAN);
  canvas.setTextColor(TFT_LIGHTGREY, 0x10A2);
  canvas.drawString("ACTIVE SCALE NOTE", 22, 48, 2);

  // Note Name & Pitch
  canvas.setTextColor(TFT_YELLOW, 0x10A2);
  canvas.drawString(noteNames[activeNoteIndex], 22, 68, 6); // Large font
  canvas.setTextColor(TFT_WHITE, 0x10A2);
  canvas.drawString(String(midiToFreq(scaleNotes[activeNoteIndex]), 1) + " Hz", 120, 78, 4);

  // Octave Shift Indicator Badge
  String octStr = (octaveShift == 0) ? "OCT: BASE" : ((octaveShift > 0) ? "OCT: +1 (HIGH)" : "OCT: -1 (LOW)");
  uint16_t octColor = (octaveShift == 0) ? TFT_GREEN : ((octaveShift > 0) ? TFT_ORANGE : TFT_MAGENTA);
  canvas.setTextColor(octColor, 0x10A2);
  canvas.drawString(octStr, 330, 52, 2);

  // Filter Cutoff display
  canvas.setTextColor(TFT_CYAN, 0x10A2);
  canvas.drawString("Cutoff: " + String((int)currentFilterCutoff) + " Hz", 330, 80, 2);

  // Scale Ribbon Graphic (Piano keys / scale degrees along the horizontal axis)
  canvas.drawRoundRect(10, 122, 460, 44, 6, TFT_DARKGREY);
  int ribbonWidth = 452;
  int keyWidth = ribbonWidth / totalScaleNotes;
  for (int i = 0; i < totalScaleNotes; i++) {
    int kx = 14 + (i * keyWidth);
    bool isActive = (i == activeNoteIndex);
    uint16_t keyColor = isActive ? TFT_CYAN : (scaleNotes[i] % 12 == 0 ? 0x4A69 : 0x18E3);
    canvas.fillRect(kx, 126, keyWidth - 2, 36, keyColor);
    if (isActive) {
      canvas.drawRect(kx, 126, keyWidth - 2, 36, TFT_WHITE);
    }
  }

  // Left Card: Accelerometer & Tilt (Roll -> Pitch Degree, Pitch -> Filter Cutoff)
  canvas.drawRoundRect(10, 174, 225, 136, 6, TFT_DARKGREY);
  canvas.setTextColor(TFT_CYAN, TFT_BLACK);
  canvas.drawString("ACCEL / TILT ORIENTATION", 20, 182, 2);

  // Roll Gauge (Tilt Left <-> Right)
  canvas.setTextColor(TFT_WHITE, TFT_BLACK);
  canvas.drawString("Roll (Note): " + String(tilt_roll, 1) + " deg", 20, 204, 2);
  canvas.fillRect(20, 222, 205, 10, 0x2104);
  int rollBar = map((long)constrain(tilt_roll, -35.0f, 35.0f), -35, 35, 0, 205);
  canvas.fillRect(20, 222, rollBar, 10, TFT_YELLOW);

  // Pitch Gauge (Tilt Forward <-> Backward)
  canvas.drawString("Pitch (Filter): " + String(tilt_pitch, 1) + " deg", 20, 240, 2);
  canvas.fillRect(20, 258, 205, 10, 0x2104);
  int pitchBar = map((long)constrain(tilt_pitch, -40.0f, 40.0f), -40, 40, 0, 205);
  canvas.fillRect(20, 258, pitchBar, 10, TFT_CYAN);

  canvas.setTextColor(TFT_DARKGREY, TFT_BLACK);
  canvas.drawString(state.calibrating ? String("CAL: HOLD STILL ") + state.calibrationCount + "/156" : String("Calibrated / EMA active"), 20, 284, 2);

  // Right Card: Gyroscope & Dynamics (Rotation -> Vibrato & Resonance)
  canvas.drawRoundRect(245, 174, 225, 136, 6, TFT_DARKGREY);
  canvas.setTextColor(TFT_GREEN, TFT_BLACK);
  canvas.drawString("GYRO & DYNAMICS", 255, 182, 2);

  canvas.setTextColor(TFT_WHITE, TFT_BLACK);
  canvas.drawString("Gyro Rate: " + String(gyro_rate, 2) + " rad/s", 255, 204, 2);
  canvas.fillRect(255, 222, 205, 10, 0x2104);
  int gyroBar = constrain((int)(gyro_rate * 30.0f), 0, 205);
  canvas.fillRect(255, 222, gyroBar, 10, TFT_GREEN);

  canvas.drawString("Vibrato Bend: " + String(currentVibrato, 2) + " st", 255, 240, 2);
  canvas.drawString("Dynamics Vol: " + String((int)(currentVelocity * 100)) + "%", 255, 260, 2);

  canvas.setTextColor(TFT_ORANGE, TFT_BLACK);
  canvas.drawString(recording ? String("REC: ") + gestureLabels[gestureLabel] : String("Serial: c=calibrate h=help"), 255, 284, 2);

  // Push framebuffer to LCD
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)canvas.getPointer());
}

void displayTask(void *) {
  DisplayState frame;
  while (true) {
    if (xQueueReceive(displayQueue, &frame, portMAX_DELAY) == pdTRUE) {
      renderDashboard(frame);
    }
    vTaskDelay(1); // Leave idle time even if the display queue stays full.
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n=======================================================");
  Serial.println("  RASCube V2 / ESP32-S3 IMU Gestural Synthesizer Scale ");
  Serial.println("=======================================================");

  // 1. Force Backlight Pin HIGH
  pinMode(LCD_BL_PIN, OUTPUT);
  digitalWrite(LCD_BL_PIN, HIGH);

  // 2. Display Init
  Serial.println("Initializing ST77922 display over QSPI...");
  mylcd.Init();
  mylcd.Set_Rotation(1); // Landscape (480 x 320)
  mylcd.Clear(0x0000);

  if (canvas.createSprite(mylcd.Get_Width(), mylcd.Get_Height()) != nullptr) {
    canvas.setSwapBytes(true);
    spriteReady = true;
  }

  // 3. I2C Bus Init
  Wire.begin(I2C_SDA, I2C_SCL, 400000);

  // 4. ES8311 Codec Init
  if (es8311.begin(Wire, I2C_SDA, I2C_SCL, 400000)) {
    es8311.setVolume(88); // 88% volume
    Serial.println("[OK] ES8311 Audio Codec ready at 44.1 kHz");
  } else {
    Serial.println("[WARN] ES8311 Codec not responding; will continue synthesis.");
  }

  // 5. LSM6DSOX Sensor Init
  Serial.println("Initializing LSM6DSOX sensor (0x6A)...");
  if (sox.begin_I2C(0x6A, &Wire)) {
    imuReady = true;
    sox.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
    sox.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS);
    sox.setAccelDataRate(LSM6DS_RATE_104_HZ);
    sox.setGyroDataRate(LSM6DS_RATE_104_HZ);
    Serial.println("[OK] LSM6DSOX Sensor ready (104 Hz sample rate)!");
  } else {
    Serial.println("[FAIL] Could not find LSM6DSOX at 0x6A!");
  }

  // 6. AMY Synth Engine Init
  amy_config_t amy_config = amy_default_config();
  amy_config.features.startup_bleep = 0;
  amy_config.features.default_synths = 0;
  amy_config.platform.multithread = 1;
  amy_config.platform.multicore = 1;
  amy_config.audio = AMY_AUDIO_IS_I2S;

  amy_config.i2s_mclk = I2S_MCK_PIN;
  amy_config.i2s_bclk = I2S_BCK_PIN;
  amy_config.i2s_lrc  = I2S_WS_PIN;
  amy_config.i2s_dout = I2S_DOUT_PIN;
  amy_config.i2s_din  = -1;

  amy_start(amy_config);
  Serial.println("[OK] AMY Engine running!");

  // Estimate stationary gyro bias without re-centering the tilt controls.
  muteSynth();
  if (imuReady) calibration.begin();
  Serial.println("# Playing is active. Hold still when convenient for background gyro calibration.");
  Serial.println("# Send h for calibration and labeled recording commands.");
  if (spriteReady) {
    displayQueue = xQueueCreate(1, sizeof(DisplayState));
    if (displayQueue && xTaskCreatePinnedToCore(displayTask, "instrument_display",
        8192, nullptr, 1, nullptr, 0) != pdPASS) {
      vQueueDelete(displayQueue);
      displayQueue = nullptr;
    }
    if (!displayQueue) Serial.println("# Display task unavailable; sensor and audio continue.");
  }
}

void loop() {
  flushRecording();
  handleCommands();
  sensors_event_t accel, gyro, temp;
  const uint32_t sampleUs = micros();
  if (imuReady && static_cast<uint32_t>(sampleUs - lastSensorUs) >= 9616) {
    const float dt = lastSensorUs == 0 ? 0.009616f : (sampleUs - lastSensorUs) * 0.000001f;
    lastSensorUs = sampleUs; // Skip missed ticks; do not duplicate samples to catch up.
    if (!sox.getEvent(&accel, &gyro, &temp)) {
      if (!recording) Serial.println("# IMU read failed.");
      calibration.resetWindow();
      muteSynth();
      return;
    }
    const float raw[6] = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z,
                          gyro.gyro.x, gyro.gyro.y, gyro.gyro.z};
    for (int i=0; i<6; ++i) {
      if (!isfinite(raw[i])) { calibration.resetWindow(); muteSynth(); return; }
    }
    if (calibration.add(raw)) {
      // Bias correction must not re-center or reset an ongoing note/tilt.
      ema_gx = ema_gy = ema_gz = 0;
      Serial.println("# Calibration complete. Gyro bias corrected; fixed tilt mapping unchanged.");
    }
    const float EMA_ALPHA = 1.0f - expf(-dt / EMA_TAU_SECONDS);

    // 1. Exponential Moving Average (EMA) Filter:
    // S_t = alpha * X_t + (1 - alpha) * S_{t-1}
    // Smooths tremor; a 48 ms time constant trades response speed for stability.
    ema_ax = (EMA_ALPHA * accel.acceleration.x) + ((1.0f - EMA_ALPHA) * ema_ax);
    ema_ay = (EMA_ALPHA * accel.acceleration.y) + ((1.0f - EMA_ALPHA) * ema_ay);
    ema_az = (EMA_ALPHA * accel.acceleration.z) + ((1.0f - EMA_ALPHA) * ema_az);

    ema_gx = (EMA_ALPHA * (gyro.gyro.x - calibration.gyroBias[0])) + ((1.0f - EMA_ALPHA) * ema_gx);
    ema_gy = (EMA_ALPHA * (gyro.gyro.y - calibration.gyroBias[1])) + ((1.0f - EMA_ALPHA) * ema_gy);
    ema_gz = (EMA_ALPHA * (gyro.gyro.z - calibration.gyroBias[2])) + ((1.0f - EMA_ALPHA) * ema_gz);

    // 2. Compute Tilt Angles
    // Roll: Tilt Left <-> Right
    float tilt_roll = gesture::rollDegrees(ema_ay, ema_az);
    // Pitch: Tilt Forward <-> Backward
    float tilt_pitch = gesture::pitchDegrees(ema_ax, ema_ay, ema_az);

    // 3. Compute Gyro Rotation Rate & Acceleration Dynamics
    float gyro_rate = sqrtf(ema_gx * ema_gx + ema_gy * ema_gy + ema_gz * ema_gz); // rad/s
    float total_accel = sqrtf(ema_ax * ema_ax + ema_ay * ema_ay + ema_az * ema_az); // m/s^2
    float motion_energy = fabsf(total_accel - 9.8f);

    // 4. MAP ROLL (-35 deg to +35 deg) -> SCALE DEGREE / NOTE
    // Use the original absolute sensor axes, independent of resting posture.
    baseNoteIndex = gesture::updateNoteIndex(tilt_roll, baseNoteIndex);

    // 5. MAP PITCH (Forward / Backward Tilt) -> OCTAVE & FILTER CUTOFF SWEEP
    // Enter beyond the original +/-22 degrees; release inside +/-18 degrees.
    octaveShift = gesture::updateOctave(tilt_pitch, octaveShift);

    // Dynamic Filter Cutoff from pitch tilt:
    // -40 deg (back) = 350 Hz (warm/mellow), +40 deg (forward) = 4500 Hz (bright/piercing)
    currentFilterCutoff = 350.0f + ((constrain(tilt_pitch, -40.0f, 40.0f) + 40.0f) / 80.0f) * 4150.0f;

    // Calculate final scale index
    activeNoteIndex = constrain(baseNoteIndex + (octaveShift * 7), 0, totalScaleNotes - 1);

    // 6. MAP GYROSCOPE -> VIBRATO & PITCH BEND
    // Gentle hand wobble adds acoustic vibrato; fast rotational flick bends the pitch
    float vibratoBend = constrain(ema_gx * 0.45f, -1.5f, 1.5f);
    currentVibrato = fabsf(vibratoBend);

    // Velocity / Amplitude from motion energy
    currentVelocity = constrain(0.55f + (motion_energy * 0.08f) + (gyro_rate * 0.1f), 0.45f, 1.0f);

    // 7. Update AMY Synthesizer Parameters (at 40 Hz rate for silky smooth legato)
    unsigned long now = millis();
    if (now - lastSoundUpdateTime >= 25) {
      lastSoundUpdateTime = now;
      int noteToPlay = scaleNotes[activeNoteIndex];
      updateSynthSound(noteToPlay, currentFilterCutoff, currentVelocity, vibratoBend);

      if (!recording && activeNoteIndex != previousNoteIndex) {
        Serial.printf("[GESTURE] Note: %s (%d) | Roll: %.1f deg | Pitch: %.1f deg | Cutoff: %.0f Hz\n",
                      noteNames[activeNoteIndex], scaleNotes[activeNoteIndex], tilt_roll, tilt_pitch, currentFilterCutoff);
        previousNoteIndex = activeNoteIndex;
      }
    }

    if (recording && sampleUs - lastRecordUs >= 20000) {
      lastRecordUs += 20000;
      if (sampleUs - lastRecordUs >= 20000) lastRecordUs = sampleUs;
      if (recordOffset < recordLength) {
        ++droppedRows;
      } else {
        int length = snprintf(recordBuffer, sizeof(recordBuffer),
          "%lu,%lu,%s,%.3f,%.3f,%.3f,%.4f,%.4f,%.4f,%.2f,%.2f\n",
          (unsigned long)sampleUs, (unsigned long)recordingSegment, gestureLabels[gestureLabel],
          raw[0], raw[1], raw[2], raw[3], raw[4], raw[5], tilt_roll, tilt_pitch);
        if (length > 0 && static_cast<size_t>(length) < sizeof(recordBuffer)) {
          recordLength = length;
          recordOffset = 0;
        } else ++droppedRows;
      }
    }

    // Publish a snapshot without waiting for the display to finish drawing.
    if (displayQueue && now - lastDisplayMs >= (recording ? 100u : 40u)) {
      lastDisplayMs = now;
      DisplayState frame = {activeNoteIndex, octaveShift, currentFilterCutoff,
        currentVibrato, currentVelocity, tilt_roll, tilt_pitch, gyro_rate,
        recording, gestureLabel, calibration.collecting, calibration.count};
      xQueueOverwrite(displayQueue, &frame);
    }
  }

  delay(1);
}
