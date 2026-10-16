## Purpose
Connect ESP-32 and Max 
  - I might write this in Pd later to make it more accessible.

## Setup (order matters)

1. Open [`sensors-to-serial.ino`](sensors-to-serial/sensors-to-serial.ino)
2. Made for ESP32-S3 2.8'' LCD board
  - Connect with **Tools → Board → esp32 → ESP32S3 Dev Module**
3. **Tools → USB CDC On Boot → Enabled** is necessary for Serial to transmit to computer.
  - Do not open the Serial Monitor, or it won't send to Max.
4. Upload
5. Open [`serial-to-synthesis.maxproj`](serial-to-synthesis/serial-to-synthesis.maxproj). Press the toggle to start.

- Note, maybe we all need to clone the repo now in order to download these files. I don't think you can download an entire directory in github website.

## Troubleshooting
- Check that USB is firmly inserted. Then close and reopen serial with the toggle
- Check that USB CDC On Boot is Enabled
- Check that the port is correct using print. It should match the arduino port. in Tools > Port.
