#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <esp_now.h>
#include <WiFi.h>

// --- HARDWARE SETUP ---
// PCA9548 MUX (0 through 7). It's numbered on the board, change code here to match which port it's plugged into on the MUX
#define HANDLE_MUX_PORT 7
#define END_MUX_PORT    0

// The default address is 0x6A. The one with the solder blob is 0x6B.
#define HANDLE_IMU_ADDR 0x6A 
#define END_IMU_ADDR    0x6B 

// The standard I2C address for the Adafruit PCA9548A MUX
#define MUX_ADDR 0x70

// We want the HANDLE IMU to read the acceleration values and the END IMU to read the gyroscope values

Adafruit_LSM6DSOX imu_handle;
Adafruit_LSM6DSOX imu_end;

// MAC ADDRESS for 2.8 inch Display: 14:C1:9F:D0:32:70
// uint8_t receiverAddress[] = {0x14, 0xC1, 0x9F, 0xD0, 0x32, 0x70}; sam's board
uint8_t receiverAddress[] = {0x44, 0x1B, 0xF6, 0xCF, 0x6F, 0x68};  // talal board


typedef struct struct_message {
  float ax; float ay; float az;
  float gx; float gy; float gz;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status) {
  // Callback left blank to save CPU cycles
}

// Helper function to tell the MUX which port to open
void tcaselect(uint8_t port) {
  if (port > 7) return;
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << port);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);

  // Power on the Feather's STEMMA QT port and init I2C
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);                         
  Wire.begin(3, 4);                              
  delay(50); // Give the MUX and both IMUs time to power up                                     
  
  // 1. Initialize the Handle IMU
  tcaselect(HANDLE_MUX_PORT);
  if (!imu_handle.begin_I2C(HANDLE_IMU_ADDR, &Wire)) { 
    Serial.println("No IMU found for the Handle: check the cable, port, and solder address");
    while(1) delay(10);
  }
  imu_handle.setAccelRange(LSM6DS_ACCEL_RANGE_16_G); 

  // 2. Initialize the End IMU
  tcaselect(END_MUX_PORT);
  if (!imu_end.begin_I2C(END_IMU_ADDR, &Wire)) { 
    Serial.println("No IMU found for the End: check the cable, port, and solder address");
    while(1) delay(10);
  }
  imu_end.setAccelRange(LSM6DS_ACCEL_RANGE_16_G);

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // 1. Read Acceleration from the Handle
  tcaselect(HANDLE_MUX_PORT);
  sensors_event_t accel_h, gyro_h, temp_h;
  imu_handle.getEvent(&accel_h, &gyro_h, &temp_h);

  // 2. Read Gyroscope from the End
  tcaselect(END_MUX_PORT);
  sensors_event_t accel_e, gyro_e, temp_e;
  imu_end.getEvent(&accel_e, &gyro_e, &temp_e);

  // Pack Acceleration from Handle (m/s^2)
  myData.ax = accel_h.acceleration.x;
  myData.ay = accel_h.acceleration.y;
  myData.az = accel_h.acceleration.z;
  
  // Pack Gyro from End (Convert rad/s to degrees/sec)
  myData.gx = gyro_e.gyro.x * 57.2958;
  myData.gy = gyro_e.gyro.y * 57.2958;
  myData.gz = gyro_e.gyro.z * 57.2958;

  // Send the combined data packet to the display board
  esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));

  delay(10);
}
