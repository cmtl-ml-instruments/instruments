#include <Wire.h>
#include <Adafruit_LSM6DSOX.h>
#include <Preferences.h>
#include "iris.h"

// Board: Adafruit ESP32-S3 NO PSRAM
// MAPPING
// 1. handle linear acceleration -> inversely to duration: ms, 2-3000 
// 2. end angular velocity -> exponentially to density: grain/s, 1-200
// 3. end angular accel -> proportionally to bandwidth: midi 0-80
// 4. handle linear height -> proportionally to pitch: midi, 12-108 (C0-C8)
// 1-3 can be exponential, 4 linear. In between states will help solidify that.

#define INPUTS  4        // numbers from the sensor
#define OUTPUTS 4        // numbers iris controls
#define SAVE    0        // the BOOT button

/* TARGET POSES: */
float sounds[][4] = {
  // {Duration, Density, Bandwidth, Pitch}
  {1, 0, 0, 0.3},  // 1. Hanging still, low position -> Silence
  {0.1661, 0.9, 0, 0.5},  // 2. steady, fast spinning,  medium position -> Sustained formant
  {0.003, 1, 0.9, 0.9}   // 3. erratic fast spinning, high position -> sparse noise.
};
const int POSES = sizeof sounds / sizeof sounds[0];

unsigned char memory[IRIS_ARENA(INPUTS, 12, OUTPUTS, POSES)];  // iris lives here
unsigned char saved[sizeof memory];                             // its copy for flash
iris *k;
Preferences flash;
Adafruit_LSM6DSOX imu;

/* GLOBALS FOR DELTA MATH */
unsigned long prevMillis = 0;
float prev_gx = 0, prev_gy = 0, prev_gz = 0;
float vx = 0, vy = 0, vz = 0; // Linear velocity
float px = 0, py = 0, pz = 0; // Linear position

// Scaling function for Max Patch
float scale_val(float val, float out_low, float out_high) {
  return out_low + (val * (out_high - out_low));
}
// Vector magnitude
float mag(float x, float y, float z) {
  return sqrt((x*x) + (y*y) + (z*z));
}

void send_scaled(const float *out) {
  // Question for Kyle: do inputs have to be 0-1 too?
  // Consider moving this back into max for the prototypability aspect. Or keep this here and use it at the end.
  float duration  = scale_val(out[0], 2, 3000);
  float density   = scale_val(out[1], 1, 200);
  float bandwidth = scale_val(out[2], 0, 80);
  float pitch     = scale_val(out[3], 12, 108);

  Serial.print(duration);  Serial.print(' '); // handle
  Serial.print(density);   Serial.print(' '); // end
  Serial.print(bandwidth); Serial.print(' '); // end
  Serial.println(pitch); // handle
}
// Need an SD card to save the state. Should training be part of the loop?
void setup() {
  Serial.begin(115200);
  pinMode(SAVE, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);                         // switch on the Feather's STEMMA QT port
  Wire.begin(3, 4);                              // the Feather's I2C pins
  delay(10);                                     // let the imu wake up
  if (!imu.begin_I2C(0x6A, &Wire)) Serial.println("no imu found: check the cable");
  imu.setAccelRange(LSM6DS_ACCEL_RANGE_16_G);    // a spinning chain needs the widest range

  k = iris_init(memory, sizeof memory, INPUTS, 12, OUTPUTS, POSES, 1234);

  flash.begin("iris");                                         // open the flash store
  size_t size = flash.getBytes("model", saved, sizeof saved);  // anything kept last time?
  if (size > 0) iris_load(k, saved, size);                     // then bring it back
  
  // Initialize millis
  prevMillis = millis();
}

void loop() {
  float in[INPUTS], out[OUTPUTS];
  // TODO: Move the calculations to a separate function
  // 1. Calculate delta_t from millis()
  unsigned long currentMillis = millis();
  // Convert milliseconds to seconds for accurate physics math
  float delta_t = (currentMillis - prevMillis) / 1000.0;

// once we get wifi, just read the values and send over to the other ESP32
  float ax, ay, az, gx, gy, gz;
  imu.readAcceleration(ax, ay, az);
  imu.readGyroscope(gx, gy, gz);

  // in[0]: Linear acceleration magnitude
  in[0] = mag(ax, ay, az);

  // in[1]: Magnitude of angular velocity
  in[1] = mag(gx, gy, gz);

  // in[2]: Magnitude of angular acceleration (alpha = dw / dt)
  float dwx = gx - prev_gx;
float dwy = gy - prev_gy;
  float dwz = gz - prev_gz;
  float alphax = dwx / delta_t;
  float alphay = dwy / delta_t;
  float alphaz = dwz / delta_t;
  in[2] = mag(alphax, alphay, alphaz);

  // in[3] - in[5]: Linear position via double integration (approximation)
  // 1. Velocity (v += delta_t * a)
  vx += delta_t * ax;
  vy += delta_t * ay;
  vz += delta_t * az;
  
  // 2. Position (x += v * delta_t)
  px += vx * delta_t;
  py += vy * delta_t;
  pz += vz * delta_t;
  
  // position might weigh heavily on the model compared to the other inputs right now.
  // think about it later.
  // in[3] = px; // x position
  // in[3] = py; // y position
  in[3] = pz; // z position

  // Save current values for the next loop's delta math
  prevMillis = currentMillis;
  prev_gx = gx;
  prev_gy = gy;
  prev_gz = gz;


  // Training Iris

  int taught = iris_count(k);                    // poses taught so far

  if (taught < POSES) {                          // TEACH
    send_scaled(sounds[taught]);                        // hear the sound you are teaching
    if (digitalRead(SAVE) == LOW) {              // SAVE pressed:
      iris_record(k, in, sounds[taught]);        //   this movement = this sound
      while (digitalRead(SAVE) == LOW) delay(10);   // wait until you let go
      if (taught + 1 == POSES) {                 //   that was the last row:
        iris_train(k);                           //     learn, once
        size_t size = iris_save(k, saved, sizeof saved);
        flash.putBytes("model", saved, size);    //     keep it in flash
      }
    }
  } else {                                       // PLAY, frozen
    iris_predict(k, in, out);                    // this movement -> these numbers
    send_scaled(out);
    if (digitalRead(SAVE) == LOW) {              // FORGET: SAVE held...
      delay(3000);
      if (digitalRead(SAVE) == LOW) {            // ...for three seconds
        iris_clear(k);
        flash.clear();
        while (digitalRead(SAVE) == LOW) delay(10);
      }
    }
  }
  delay(10); 
}
