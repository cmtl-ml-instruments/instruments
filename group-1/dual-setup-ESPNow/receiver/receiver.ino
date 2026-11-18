#include <esp_now.h>
#include <WiFi.h>
#include <Preferences.h>
#include "iris.h"

// Configuration
#define INPUTS  4        // numbers from the sensor (Mag Accel, Mag Gyro, Mag Alpha, Pos Y)
#define OUTPUTS 4        // numbers iris controls
#define POSES   3        // rows you will teach
#define SAVE    0        // BOOT button on the display board

/* TARGET POSES: {Duration, Density, Bandwidth, Pitch} */
float sounds[][4] = {
  {0.9, 0.1, 0.0, 0.3},  // 1. Hanging still
  {0.7, 0.9, 0.0, 0.5},  // 2. Sustained formant
  {0.1, 0.9, 0.9, 0.9}   // 3. Fast erratic spinning
};

// Global Objects
Preferences flash;
unsigned char saved[2048]; // Buffer to store the model in flash memory

// IRIS Configuration
unsigned char memory[IRIS_ARENA(INPUTS, 12, OUTPUTS, POSES)];
iris *k;

/* GLOBALS FOR TEAMMATE'S CALCULUS MATH */
unsigned long prevMillis = 0;
float prev_gx = 0, prev_gy = 0, prev_gz = 0;
float vx = 0, vy = 0, vz = 0; 
float px = 0, py = 0, pz = 0; 

// State tracker to prevent flooding the Serial Monitor with text
int last_taught = -1;

// The incoming data packet structure (MUST exactly match the sender)
typedef struct struct_message {
  float ax; float ay; float az;
  float gx; float gy; float gz;
} struct_message;
struct_message incomingData;

// Global flags and variables to safely transfer ESP-NOW data to the main loop
volatile bool newData = false;
float live_ax = 0, live_ay = 0, live_az = 0;
float live_gx = 0, live_gy = 0, live_gz = 0;

// ESP-NOW Callback
void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incoming, int len) {
  memcpy(&incomingData, incoming, sizeof(incomingData));
  live_ax = incomingData.ax; live_ay = incomingData.ay; live_az = incomingData.az;
  live_gx = incomingData.gx; live_gy = incomingData.gy; live_gz = incomingData.gz;
  newData = true;
}

// Math Helpers
float scale_val(float val, float out_low, float out_high) {
  if (val < 0.0) val = 0.0;
  if (val > 1.0) val = 1.0;
  return out_low + (val * (out_high - out_low));
}

float mag(float x, float y, float z) {
  return sqrt((x*x) + (y*y) + (z*z));
}

void send_scaled(const float *out) {
  float duration  = scale_val(out[0], 2, 3000);
  float density   = scale_val(out[1], 0, 200);
  float bandwidth = scale_val(out[2], 0, 80);
  float pitch     = scale_val(out[3], 12, 108);

  Serial.print(duration);  Serial.print(' ');
  Serial.print(density);   Serial.print(' ');
  Serial.print(bandwidth); Serial.print(' ');
  Serial.println(pitch);
}

void setup() {
  Serial.begin(115200);
  pinMode(SAVE, INPUT_PULLUP);
  
 // Serial.println("\n--- SYSTEM BOOTING ---");
  
  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
  //  Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  // Initialize Neural Network
  k = iris_init(memory, sizeof memory, INPUTS, 12, OUTPUTS, POSES, 1234);

  // flash storage, just in case board loses power
  flash.begin("iris");                                         
  size_t size = flash.getBytes("model", saved, sizeof saved);  
  if (size > 0) {
    iris_load(k, saved, size);    
  //  Serial.println("Found saved model in flash! Jumping directly to PLAY MODE.");                 
  } else {
    // Serial.println("No saved model found. Entering TEACH MODE.");
  }
  
  prevMillis = millis();
}

void loop() {
  if (newData) {
    newData = false; 

    unsigned long currentMillis = millis();
    float delta_t = (currentMillis - prevMillis) / 1000.0;
    if (delta_t <= 0.0) delta_t = 0.001; 

    float in[INPUTS];

    // in[0]: Linear acceleration magnitude
    in[0] = mag(live_ax, live_ay, live_az);

    // in[1]: Magnitude of angular velocity
    in[1] = mag(live_gx, live_gy, live_gz);

    // in[2]: Magnitude of angular acceleration (alpha = dw / dt)
    float dwx = live_gx - prev_gx;
    float dwy = live_gy - prev_gy;
    float dwz = live_gz - prev_gz;
    float alphax = dwx / delta_t;
    float alphay = dwy / delta_t;
    float alphaz = dwz / delta_t;
    in[2] = mag(alphax, alphay, alphaz);

    // in[3]: Linear position via double integration
    vx += delta_t * live_ax;
    vy += delta_t * live_ay;
    vz += delta_t * live_az;
    
    px += vx * delta_t;
    py += vy * delta_t;
    pz += vz * delta_t;
    
    in[3] = py; 

    prevMillis = currentMillis;
    prev_gx = live_gx;
    prev_gy = live_gy;
    prev_gz = live_gz;

    // Training Iris
    float out[OUTPUTS];
    int taught = iris_count(k);                    

    if (taught < POSES) {                          // TEACH MODE
      
      // Print instructions only once per pose
      if (taught != last_taught) {
        //Serial.println();
        //Serial.print("--- READY FOR POSE ");
        // Serial.print(taught + 1);
        // Serial.println(" ---");
        // Serial.println("Perform the physical gesture, then press BOOT to record...");
        last_taught = taught;
      }
      
      send_scaled(sounds[taught]);                 
      
      // Press BOOT button on the Display Board to save the pose
      if (digitalRead(SAVE) == LOW) {     
        // Serial.print(">> RECORDING POSE ");
        // Serial.print(taught + 1);
        // Serial.println("...");
                     
        iris_record(k, in, sounds[taught]);        
        while (digitalRead(SAVE) == LOW) delay(10); // Wait until you let go
        
        // Serial.println(">> Pose saved!");

        if (taught + 1 == POSES) {                 
          // Serial.println(">> All poses recorded! TRAINING NEURAL NETWORK...");
          iris_train(k);                           
          size_t size = iris_save(k, saved, sizeof saved);
          flash.putBytes("model", saved, size);    
          // Serial.println(">> Training complete & saved to flash! ENTERING PLAY MODE.");
        }
      }
    } else {                                       // PLAY MODE
      iris_predict(k, in, out);                    
      send_scaled(out);
      
      if (digitalRead(SAVE) == LOW) {              // FORGET MODE
        // Serial.println("\n>> Hold BOOT for 3 seconds to FORGET model...");
        delay(3000);
        if (digitalRead(SAVE) == LOW) {            
          // Serial.println(">> ERASING MODEL...");
          iris_clear(k);
          flash.clear();
          last_taught = -1; // Reset tracker so it prints instructions again
          // Serial.println(">> Model erased. Rebooting into TEACH MODE.");
          while (digitalRead(SAVE) == LOW) delay(10);
        } else {
          // Serial.println(">> Erase canceled.");
        }
      }
    }
  }
}