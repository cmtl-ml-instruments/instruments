## Purpose
Connect ESP-32 and Max 
  - I might write this in Pd later to make it more accessible.

## Setup (order matters)

1. Open [`sensors-to-serial.ino`](sensors-to-serial/sensors-to-serial.ino)
2. Board: ESP32-S3 2.8'' LCD
  - Connect with **Tools → Board → esp32 → ESP32S3 Dev Module**
3. **Tools → USB CDC On Boot → Enabled**
  - Do not open the Serial Monitor, or it won't send to Max.
4. Upload
5. Open Max Patch. Press the toggle to start.
