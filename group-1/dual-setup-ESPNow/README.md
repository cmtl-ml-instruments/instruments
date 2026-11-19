Note that the sender is the AdaFruit ESP32 Feather, and the Receiver is a 2.8 inch ESP32 Display Board with MAC Address 14:C1:9F:D0:32:70.  
This script splits functionality between the sender and receiver, where the sender takes in input values from the sensors on the chain, and sends those values to the receiver via ESPNow.  
The Receiver then performs necessary computation, scaling, and training logic, preparing data to be sent to MAX. 

Connector Script Debugging
- USB firmly inserted
- USB CDC on Boot Enabled
- Board:
	- Sender: ESP32-S3 Feather No PSRAM
	- Receiver: ESP32S3 Dev Module
- Serial Monitor/Plotter NOT enabled unless testing
- Gyroscopes on the handle (MUX 7) and the end (MUX 0) of the instrument connected via Stemma QT to the multiplexer. Multiplexer connects to the feather by STEMMA. Receiver connects via USB to computer. Computer runs granular-synth.maxproj.
- Gyroscopes has flasing green light that is sustained!
- If you get the error that serial connection failed, hold BOOT 3 seconds then, while holding, press RESET.
	- If make sure the green light is still on. If not, disconnect and reconnect USB.
- Max toggle should be off while uploading. Turn it on after. 
