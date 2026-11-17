#include <Wire.h>
#include <Arduino_LSM6DSOX.h>
#include "iris.h"

/* TARGET POSES: {Duration, Density, Bandwidth, Pitch} */
float sounds[][4] = {
  {0.9, 0.1, 0.0, 0.3},  // 1. Hanging still
  {0.7, 0.9, 0.0, 0.5},  // 2. Sustained formant
  {0.1, 0.9, 0.9, 0.9}   // 3. Fast erratic spinning
};
const int POSES = sizeof sounds / sizeof sounds[0];

// IRIS Configuration: 7 inputs (in[0] to in[6]), 12 hidden units, 4 outputs
unsigned char memory[IRIS_ARENA(7, 12, 4, POSES)];
iris *k;

/* GLOBALS FOR DELTA MATH */
unsigned long prevMillis = 0;
float prev_gx = 0, prev_gy = 0, prev_gz = 0;
float vx = 0, vy = 0, vz = 0; // Linear velocity
float px = 0, py = 0, pz = 0; // Linear position

// Scaling function for Max Patch
float scale_val(float val, float out_low, float out_high) {
  if (val < 0.0) val = 0.0;
  if (val > 1.0) val = 1.0;
  return out_low + (val * (out_high - out_low));
}

void send_scaled(const float *out) {
  float duration  = scale_val(out[0], 2, 3000);
  float density   = out[1]; // We will override this in the loop
  float bandwidth = scale_val(out[2], 0, 80);
  float pitch     = scale_val(out[3], 12, 108);

  Serial.print(duration);  Serial.print(' ');
  Serial.print(density);   Serial.print(' ');
  Serial.print(bandwidth); Serial.print(' ');
  Serial.println(pitch);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(16, 15);           
  IMU.begin();
  pinMode(0, INPUT_PULLUP);     

  // Init IRIS with 7 inputs instead of 3
  k = iris_init(memory, sizeof memory, 7, 12, 4, POSES, 1234);
  
  // Initialize millis
  prevMillis = millis();
}

void loop() {
  // 1. Calculate delta_t from millis()
  unsigned long currentMillis = millis();
  // Convert milliseconds to seconds for accurate physics math
  float delta_t = (currentMillis - prevMillis) / 1000.0; 
  
  // Prevent divide-by-zero on the very first loop
  if (delta_t <= 0.0) delta_t = 0.001; 

  float ax, ay, az, gx, gy, gz;
  IMU.readAcceleration(ax, ay, az);
  IMU.readGyroscope(gx, gy, gz);

  float in[7];

  // in[0]: Linear acceleration magnitude
  in[0] = sqrt((ax*ax) + (ay*ay) + (az*az));

  // in[1]: Magnitude of angular velocity
  in[1] = sqrt((gx*gx) + (gy*gy) + (gz*gz));

  // in[2]: Magnitude of angular acceleration (alpha = dw / dt)
  float dwx = gx - prev_gx;
  float dwy = gy - prev_gy;
  float dwz = gz - prev_gz;
  float alphax = dwx / delta_t;
  float alphay = dwy / delta_t;
  float alphaz = dwz / delta_t;
  in[2] = sqrt((alphax*alphax) + (alphay*alphay) + (alphaz*alphaz));

  // in[4] - in[6]: Linear position via double integration
  // 1. Velocity (v += delta_t * a)
  vx += delta_t * ax;
  vy += delta_t * ay;
  vz += delta_t * az;
  
  // 2. Position (x += v * delta_t)
  px += vx * delta_t;
  py += vy * delta_t;
  pz += vz * delta_t;
  
  in[4] = px; // x position
  in[5] = py; // y position
  in[6] = pz; // z position

  // Explicit Math for Density (Overrides IRIS using angular velocity magnitude)
  float calculated_density = (200.0 / 360.0) * in[1]; 
  if (calculated_density > 200.0) calculated_density = 200.0;

  float out[4];
  int n = iris_count(k);

  // Training & Playing Logic
  if (n < POSES) {
    float temp_out[4] = {sounds[n][0], calculated_density, sounds[n][2], sounds[n][3]};
    send_scaled(temp_out); 
    
    if (digitalRead(0) == LOW) {
      iris_record(k, in, sounds[n]);
      if (n == POSES - 1) {
        iris_train(k);
      }
      while (digitalRead(0) == LOW) delay(10); 
    }
  } else {
    iris_predict(k, in, out);
    out[1] = calculated_density; 
    send_scaled(out);
  }

  // Save current values for the next loop's delta math
  prevMillis = currentMillis;
  prev_gx = gx;
  prev_gy = gy;
  prev_gz = gz;
  
  delay(10); 
}