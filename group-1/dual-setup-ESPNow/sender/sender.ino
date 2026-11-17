// Adafruit ESP32 Feather

#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <esp_now.h>
#include <WiFi.h>

// Initialize Adafruit IMU
Adafruit_LSM6DSOX imu;

// MAC ADDRESS for 2.8 inch Display: 14:C1:9F:D0:32:70
uint8_t receiverAddress[] = {0x14, 0xC1, 0x9F, 0xD0, 0x32, 0x70};

// The data packet we will send over the air
typedef struct struct_message {
  float ax; float ay; float az;
  float gx; float gy; float gz;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Callback to let us know if the packet actually delivered (ESP32 Core 3.x syntax)
void OnDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status) {

}

void setup() {
  Serial.begin(115200);

  // Power on the Feather's STEMMA QT port and init I2C
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);                         
  Wire.begin(3, 4);                              
  delay(10);                                     
  
  if (!imu.begin_I2C(0x6A, &Wire)) { // check if feather and lsm6dsox connected
    Serial.println("No IMU found on Feather: check the cable");
    while(1) delay(10);
  }
  imu.setAccelRange(LSM6DS_ACCEL_RANGE_16_G); // expanding range for acceleration to be measured up to 16 * 9.8 as a high upper bound

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  
  // Register the 2.8" Display as a peer
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read the Adafruit IMU
  sensors_event_t accel, gyro, temp;
  imu.getEvent(&accel, &gyro, &temp);

  // Pack Acceleration (m/s^2)
  myData.ax = accel.acceleration.x;
  myData.ay = accel.acceleration.y;
  myData.az = accel.acceleration.z;
  
  // Pack Gyro (Convert rad/s to degrees/sec before sending)
  myData.gx = gyro.gyro.x * 57.2958;
  myData.gy = gyro.gyro.y * 57.2958;
  myData.gz = gyro.gyro.z * 57.2958;

  // Send the data packet to the display board
  esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));

  delay(10);
}