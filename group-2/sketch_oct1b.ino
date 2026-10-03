#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "ST77922.h"
#include "ES8311.h"
#include <AMY-Arduino.h>

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
bool codecReady = false;

// --- Scale Definition (C Major / Pentatonic 2-Octave Span) ---
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
const float EMA_ALPHA = 0.18f; // Low-pass filter coefficient (smoothing out hand tremors & shock)

// --- Dynamic Instrument State ---
int activeNoteIndex = 7;     // Default center note: C4 (index 7)
int previousNoteIndex = -1;
int octaveShift = 0;         // -1, 0, +1 based on forward/backward tilt
float currentFilterCutoff = 2000.0f; // Hz (controlled by tilt pitch)
float currentVibrato = 0.0f;         // Depth controlled by gyro rate
float currentVelocity = 0.8f;        // Controlled by motion intensity
unsigned long lastSoundUpdateTime = 0;
bool synthPlaying = false;

// Convert MIDI Note to Base Frequency in Hz
float midiToFreq(int note) {
  return 440.0f * powf(2.0f, (note - 69.0f) / 12.0f);
}

void updateSynthSound(int note, float filterCutoff, float velocity, float pitchBendSemitones = 0.0f) {
  float baseFreq = midiToFreq(note);
  float finalFreq = baseFreq * powf(2.0f, pitchBendSemitones / 12.0f);

  // AMY voice update:
  // v0: voice 0, w0: Sine wave / warm synth, f: frequency, F: filter cutoff, a: amplitude, l: velocity
  char msg[96];
  snprintf(msg, sizeof(msg), "v0w0f%.1fF%.0fa0.85l%.2f", finalFreq, filterCutoff, velocity);
  amy_add_message(msg);
  synthPlaying = true;
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
    codecReady = true;
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
  amy_config.features.startup_bleep = 1;
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

  // Start with default note
  updateSynthSound(scaleNotes[activeNoteIndex], currentFilterCutoff, 0.8f, 0.0f);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  if (imuReady) {
    sox.getEvent(&accel, &gyro, &temp);

    // 1. Exponential Moving Average (EMA) Filter:
    // S_t = alpha * X_t + (1 - alpha) * S_{t-1}
    // Eliminates hand tremors and mechanical resonance while keeping instant response (<20ms)
    ema_ax = (EMA_ALPHA * accel.acceleration.x) + ((1.0f - EMA_ALPHA) * ema_ax);
    ema_ay = (EMA_ALPHA * accel.acceleration.y) + ((1.0f - EMA_ALPHA) * ema_ay);
    ema_az = (EMA_ALPHA * accel.acceleration.z) + ((1.0f - EMA_ALPHA) * ema_az);

    ema_gx = (EMA_ALPHA * gyro.gyro.x) + ((1.0f - EMA_ALPHA) * ema_gx);
    ema_gy = (EMA_ALPHA * gyro.gyro.y) + ((1.0f - EMA_ALPHA) * ema_gy);
    ema_gz = (EMA_ALPHA * gyro.gyro.z) + ((1.0f - EMA_ALPHA) * ema_gz);

    // 2. Compute Tilt Angles
    // Roll: Tilt Left <-> Right
    float tilt_roll = atan2f(ema_ay, ema_az) * (180.0f / PI);
    // Pitch: Tilt Forward <-> Backward
    float tilt_pitch = atan2f(-ema_ax, sqrtf(ema_ay * ema_ay + ema_az * ema_az)) * (180.0f / PI);

    // 3. Compute Gyro Rotation Rate & Acceleration Dynamics
    float gyro_rate = sqrtf(ema_gx * ema_gx + ema_gy * ema_gy + ema_gz * ema_gz); // rad/s
    float total_accel = sqrtf(ema_ax * ema_ax + ema_ay * ema_ay + ema_az * ema_az); // m/s^2
    float motion_energy = fabsf(total_accel - 9.8f);

    // 4. MAP ROLL (-35 deg to +35 deg) -> SCALE DEGREE / NOTE
    // Level = C4 (index 7). Tilting left goes down towards C3, tilting right goes up towards C5!
    float roll_clamped = constrain(tilt_roll, -35.0f, 35.0f);
    // Map -35..+35 to 0..(totalScaleNotes - 8)
    int base_note_index = map((long)(roll_clamped * 10), -350, 350, 2, totalScaleNotes - 3);

    // 5. MAP PITCH (Forward / Backward Tilt) -> OCTAVE & FILTER CUTOFF SWEEP
    // Tilt forward (> 20 deg): shift up 1 octave (+7 scale degrees)
    // Tilt backward (< -20 deg): shift down 1 octave (-7 scale degrees)
    if (tilt_pitch > 22.0f) {
      octaveShift = 1;
    } else if (tilt_pitch < -22.0f) {
      octaveShift = -1;
    } else {
      octaveShift = 0;
    }

    // Dynamic Filter Cutoff from pitch tilt:
    // -40 deg (back) = 350 Hz (warm/mellow), +40 deg (forward) = 4500 Hz (bright/piercing)
    currentFilterCutoff = map((long)constrain(tilt_pitch, -40.0f, 40.0f), -40, 40, 350, 4500);

    // Calculate final scale index
    activeNoteIndex = constrain(base_note_index + (octaveShift * 7), 0, totalScaleNotes - 1);

    // 6. MAP GYROSCOPE -> VIBRATO & PITCH BEND
    // Gentle hand wobble adds acoustic vibrato; fast rotational flick bends the pitch
    float vibratoBend = (ema_gx * 0.45f); // Pitch bend up to +/- 1.5 semitones
    currentVibrato = fabsf(vibratoBend);

    // Velocity / Amplitude from motion energy
    currentVelocity = constrain(0.55f + (motion_energy * 0.08f) + (gyro_rate * 0.1f), 0.45f, 1.0f);

    // 7. Update AMY Synthesizer Parameters (at 40 Hz rate for silky smooth legato)
    unsigned long now = millis();
    if (now - lastSoundUpdateTime >= 25) {
      lastSoundUpdateTime = now;
      int noteToPlay = scaleNotes[activeNoteIndex];
      updateSynthSound(noteToPlay, currentFilterCutoff, currentVelocity, vibratoBend);

      if (activeNoteIndex != previousNoteIndex) {
        Serial.printf("[GESTURE] Note: %s (%d) | Roll: %.1f deg | Pitch: %.1f deg | Cutoff: %.0f Hz\n",
                      noteNames[activeNoteIndex], scaleNotes[activeNoteIndex], tilt_roll, tilt_pitch, currentFilterCutoff);
        previousNoteIndex = activeNoteIndex;
      }
    }

    // --- 8. Render Rich Interactive Dashboard to LCD ---
    if (spriteReady) {
      canvas.fillSprite(TFT_BLACK);

      // Header Bar
      canvas.fillRect(0, 0, 480, 34, 0x0187); // Deep teal
      canvas.setTextColor(TFT_WHITE, 0x0187);
      canvas.drawString("GESTURAL SYNTH: IMU SCALE INFLUENCE", 12, 7, 4);
      canvas.fillCircle(458, 17, 6, TFT_GREEN);

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
      canvas.drawString("EMA Tremor Filter: Active", 20, 284, 2);

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
      canvas.drawString("Tilt Left/Right to Play Scale!", 255, 284, 2);

      // Push framebuffer to LCD
      mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)canvas.getPointer());
    }
  }

  delay(15);
}