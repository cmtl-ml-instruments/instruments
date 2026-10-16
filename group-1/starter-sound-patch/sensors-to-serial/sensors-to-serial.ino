#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Goal: Get sound in Max!
// This code right now is exactly the sonar screen with some modularity.

const int TRIG = 15; // I2C SCL/Clock
const int ECHO = 16; // I2C SDA/Data

Adafruit_ILI9341 screen(10, 46, -1);   // this board's screen and pins


void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(45, OUTPUT);               // pin 45 is the screen's backlight:
  digitalWrite(45, HIGH);            // switch it on
  // SPI 10 = select control sig 11 - write data 12 clock/control 13 read data
  // clock, read, write, control-select
  SPI.begin(12, 13, 11, 10);
  screen.begin();
  screen.invertDisplay(true);        // this screen's colours come out inverted otherwise
  screen.fillScreen(ILI9341_BLACK);
  screen.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  screen.setTextSize(5);
  screen.setTextWrap(false);

  Serial.begin(115200);
  
}


void loop() {
  // cm from sensor to hand.
  int cm = sense_distance();
  display(cm);
  Serial.println(cm); // send to Max
  delay(60); 
}

int sense_distance() {
  // 1. Chirp: a 10-microsecond pulse on Trig makes the sensor send out a sound.
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // 2. Listen: Echo stays on for as long as the sound took to bounce back.
  //    Give up after 30,000 microseconds -- about five metres.
  long echoTime = pulseIn(ECHO, HIGH, 30000);

  // 3. Sound goes 1 cm out and back in about 58 microseconds.
  //    0 means nothing came back: too far away, or a loose wire.
  int cm = echoTime / 58;
  return cm;
}

void display(int cm) {
  // input: cm distance from sensor
  // out: display the number and a bar that grows as your hand moves away.
  screen.setCursor(20, 100);
  screen.print(cm);
  screen.print(" cm   ");
  // 0-100 cm becomes 0-200 pixels
  int bar = constrain(cm, 0, 100) * 2;
  screen.fillRect(20, 200, bar, 40, ILI9341_GREEN);
  screen.fillRect(20 + bar, 200, 200 - bar, 40, ILI9341_BLACK);
}


     
