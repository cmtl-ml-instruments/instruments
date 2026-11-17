Note that the sender is the AdaFruit ESP32 Feather, and the Receiver is a 2.8 inch ESP32 Display Board with MAC Address 14:C1:9F:D0:32:70.
This script splits functionality between the sender and receiver, where the sender takes in input values from the sensors on the chain, and sends those values to the receiver via ESPNow.
The Receiver then performs necessary computation, scaling, and training logic, preparing data to be sent to MAX.
