# ESP32-S3 Gestural Instrument

| Sketch | Hardware | What it does |
| --- | --- | --- |
| [InstrumentDisplay](firmware/InstrumentDisplay/InstrumentDisplay.ino) | 3.5-inch ST77922 board with ES8311 and local LSM6DSOX | Maps motion to AMY sound and draws the dashboard. |
| [FeatherTransmitter](firmware/FeatherTransmitter/README.md) | Adafruit ESP32-S3 Feather No PSRAM with LSM6DSOX | Sends six-axis samples via ESP-NOW and reports measurements over USB. |
| [WirelessNoteReceiver](firmware/WirelessNoteReceiver/README.md) | Temporary 2.8-inch ESP32-S3 | Receives motion and logs note events over USB. |
| [UDA1334AudioTest](tests/UDA1334AudioTest/README.md) | 3.5-inch board wired to an external UDA1334 | Checks the external audio path with a test tone. |

## Build

Install the ESP32 board package in Arduino IDE. The project was built with
Arduino-ESP32 3.3.11. Each sketch's folder and `.ino` file share a name.

For the two wireless sketches, copy the
[InstrumentSensorLink](libraries/InstrumentSensorLink) folder into the
`libraries` folder of your Arduino sketchbook before opening the sketch.
Arduino CLI can use the library in place with `--libraries ./libraries`.
The board settings and CLI commands are in each wireless sketch's README.

For the 3.5-inch instrument, use ESP32S3 Dev Module, OPI PSRAM, 16 MB flash,
and USB CDC On Boot enabled. Install AMY Synthesizer, Adafruit LSM6DS,
Adafruit Unified Sensor, and TFT_eSPI in the Arduino sketchbook.
See the [instrument hardware and motion mapping](docs/InstrumentHardware.md).

## Where to look next

- `firmware/InstrumentDisplay/GestureControl.h` contains calibration and motion-to-note mapping.
- `firmware/WirelessNoteReceiver/TiltNote.h` contains the C4 thresholds, hold time, and link-loss release.
- `libraries/InstrumentSensorLink/src/SensorPacket.h` defines the shared wire format and units.
- `tools/` contains the PowerShell serial recorder and board checks. See the [gesture recording guide](docs/GestureRecording.md).
- `recordings/` holds bench captures referenced by the guides and [weekly notebook](notebooks/weekly_notebook_2026-10-30.md).

Create local builds under `build/` or a temporary directory. The source tree
contains the files needed to rebuild the firmware.
