#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Goal: Get sound in Max!

int x = 0;

void setup() {
  // SPI 10 = select control sig 11 - write data 12 clock/control 13 read data
  // clock, read, wurite, control-select
  SPI.begin(12, 13, 11, 10);
  Serial.begin(9600);
  
}


void loop() {
  Serial.println(x);
  x = (x+1) % 600;
  delay(20);

}


// const int TRIG = 15; // I2C Clock
// const int ECHO = 16; // I2C Data

// Adafruit_ILI9341 screen(10, 46, -1);   // this board's screen and pins

// void setup() {
//   pinMode(TRIG, OUTPUT);
//   pinMode(ECHO, INPUT);

//   pinMode(45, OUTPUT);               // pin 45 is the screen's backlight:
//   digitalWrite(45, HIGH);            // switch it on
//   SPI.begin(12, 13, 11, 10);         // the wires between the chip and the screen
//   screen.begin();
//   screen.invertDisplay(true);        // this screen's colours come out inverted otherwise
//   screen.fillScreen(ILI9341_BLACK);
//   screen.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
//   screen.setTextSize(5);
//   screen.setTextWrap(false);

//   Serial.begin(115200);
// }

// void loop() {
//   // 1. Chirp: a 10-microsecond pulse on Trig makes the sensor send out a sound.
//   digitalWrite(TRIG, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG, LOW);

//   // 2. Listen: Echo stays on for as long as the sound took to bounce back.
//   //    Give up after 30,000 microseconds -- about five metres.
//   long echoTime = pulseIn(ECHO, HIGH, 30000);

//   // 3. Sound goes 1 cm out and back in about 58 microseconds.
//   //    0 means nothing came back: too far away, or a loose wire.
//   int cm = echoTime / 58;

//   // 4. Show it: the number, and a bar that grows as your hand moves away.
//   screen.setCursor(20, 100);
//   screen.print(cm);
//   screen.print(" cm   ");

//   int bar = constrain(cm, 0, 100) * 2;               // 0-100 cm becomes 0-200 pixels
//   screen.fillRect(20, 200, bar, 40, ILI9341_GREEN);
//   screen.fillRect(20 + bar, 200, 200 - bar, 40, ILI9341_BLACK);

//   Serial.println(cm);   // Tools -> Serial Plotter draws this as a moving line
//   delay(60);       
