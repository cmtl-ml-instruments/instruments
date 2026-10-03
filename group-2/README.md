# ESP32-S3 Gestural Synthesizer

An expressive gestural electronic musical instrument built on the **ESP32-S3** microcontroller. The system combines the **AMY dual-core synthesis engine**, an **LSM6DSOX 6-DoF IMU** running an Exponential Moving Average (EMA) tremor filter, an onboard **Everest Semi ES8311 I2S audio codec**, and a **3.5" ST77922 (480x320) IPS display**.

---

## File Directory & Purpose

| File | Type | Purpose & Description | Status |
| :--- | :--- | :--- | :--- |
| [`sketch_oct1b.ino`](./sketch_oct1b.ino) | **Main Firmware** | Central application loop. Reads the LSM6DSOX sensor at 104 Hz, applies EMA filtering, computes tilt roll/pitch and gyro rates, maps motion to musical scale degrees, sends real-time parameter deltas to the AMY synth engine at 40 Hz, and renders the 480x320 dashboard. | **Required** |
| [`ES8311.h`](./ES8311.h) | **C++ Header** | Class declaration for the Everest Semi ES8311 audio DAC/codec. Defines register addresses, volume controls, mute/unmute functions, and power amplifier pin definitions. | **Required** |
| [`ES8311.cpp`](./ES8311.cpp) | **C++ Source** | Codec implementation using Arduino `Wire`. Configures the ES8311 clock dividers for **44.1 kHz** sample rate with an **11.2896 MHz MCLK**, sets 32-bit I2S slot mode, and pulls `PA_ENABLE` (GPIO 1) LOW to power the onboard speaker/headphone amplifier. | **Required** |
| [`ST77922.h`](./ST77922.h) | **C++ Header** | Low-level driver header for the Sitronix ST77922 480x320 QSPI display controller. | **Required** |
| [`ST77922.cpp`](./ST77922.cpp) | **C++ Source** | Low-level QSPI bus driver. Initializes the display hardware registers and pushes 16-bit RGB565 framebuffer sprite data via fast DMA transfers. | **Required** |

---

## Hardware Pinout Configuration

### 1. I2S Audio Bus (ES8311 Codec & Power Amp)
| Pin | ESP32-S3 GPIO | Function | Description |
| :--- | :--- | :--- | :--- |
| **MCLK** | `GPIO 17` | Master Clock | 11.2896 MHz ($256 \times 44.1\text{ kHz}$) reference clock |
| **BCLK** | `GPIO 18` | Bit Clock | Serial data bit clock (64 clocks per frame) |
| **WS / LRC** | `GPIO 21` | Word Select | Left / Right audio channel framing at 44.1 kHz |
| **DOUT** | `GPIO 15` | Data Out | I2S 32-bit stereo audio data stream sent to DAC |
| **PA_EN** | `GPIO 1` | Amp Enable | Onboard audio amplifier power (Active LOW: `LOW` = On) |

### 2. I2C Bus (Shared Sensors & Audio Control)
| Pin | ESP32-S3 GPIO | Device(s) Connected | Bus Speed |
| :--- | :--- | :--- | :--- |
| **SDA** | `GPIO 38` | ES8311 (`0x18`) & LSM6DSOX (`0x6A`) | 400 kHz (Fast Mode) |
| **SCL** | `GPIO 39` | ES8311 (`0x18`) & LSM6DSOX (`0x6A`) | 400 kHz (Fast Mode) |

### 3. Display (ST77922 3.5" LCD)
| Signal | ESP32-S3 Pin | Function |
| :--- | :--- | :--- |
| **QSPI Bus** | `GPIO 9, 10, 11, 12, 13, 14` | High-speed Quad-SPI display interface |
| **Backlight** | `GPIO 41` | LCD Backlight control (Active HIGH) |

---

## Gestural Mapping Architecture

```
   [ LSM6DSOX IMU ] (104 Hz)
          │
          ▼
   [ EMA Filter (alpha = 0.18) ]  ─── Removes hand tremors & mechanical bounce
          │
   ┌──────┴───────────────────────────────┐
   ▼                                      ▼
[ Tilt Roll (-35° to +35°) ]       [ Tilt Pitch (-40° to +40°) ]
   │                                      │
   ▼                                      ├─► [ Octave Shift ] (> +22° = +1, < -22° = -1)
[ Musical Scale Degree ]                  └─► [ Filter Cutoff ] (350 Hz to 4500 Hz sweep)
(22-note span: C3 to C6)
          │
          ├───────────────────────────────┐
          ▼                               ▼
   [ AMY Synth Engine ]            [ ST77922 Display ]
   • Dual-core FreeRTOS            • Active Note Banner
   • 44.1 kHz I2S DMA              • Visual Keyboard Ribbon
   • Legato voice updates (40 Hz)  • Live Sensor Bar Gauges
```

### Motion-to-Sound Mapping Summary
- **Roll (Tilt Left $\leftrightarrow$ Right):** Selects notes across a 2-octave C Major scale (`C3` through `C6`). Holding the board level plays center `C4`.
- **Pitch (Tilt Forward $\leftrightarrow$ Backward):** 
  - Tilting forward past $+22^\circ$ shifts the entire scale **up 1 octave**.
  - Tilting backward past $-22^\circ$ shifts the scale **down 1 octave**.
  - Continuous pitch angle dynamically sweeps the AMY low-pass filter cutoff from $350\text{ Hz}$ (deep/muffled) to $4500\text{ Hz}$ (bright lead).
- **Gyroscope Rate (Rotational Energy):** Subtle hand rotation applies acoustic vibrato ($\pm 1.5$ semitones pitch bend).
- **Acceleration Energy:** Controls dynamic velocity and synth loudness ($45\% \to 100\%$).

---

## Signal Processing Details
Raw MEMS accelerometer readings suffer from natural muscle tremors and micro-shocks when handling the unit. The sketch applies an **Exponential Moving Average (EMA)** filter to all 6 axes:

$$S_t = \alpha \cdot X_t + (1 - \alpha) \cdot S_{t-1}$$

With $\alpha = 0.18$, high-frequency jitter is eliminated while preserving a response latency of under $20\text{ ms}$.

---

## Arduino IDE Build Configuration

When compiling this project in the Arduino IDE:
1. **Board:** `ESP32S3 Dev Module`
2. **PSRAM:** `OPI PSRAM` (Required for the 480x320 16-bit framebuffer sprite)
3. **Flash Size:** `16MB (128Mb)`
4. **Partition Scheme:** `16M Flash (3MB APP / 9.9MB FAT)` or Default
5. **Required Libraries:**
   - `AMY Synthesizer` (v1.2+)
   - `Adafruit_LSM6DS` & `Adafruit_Sensor`
   - `TFT_eSPI`
