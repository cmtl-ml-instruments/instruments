#pragma once
#include <stdint.h>

// Copied through a length-one queue: the display never reads mutable sensor
// state or holds up acquisition while transferring a framebuffer.
struct DisplayState {
  int noteIndex;
  int octave;
  float cutoff;
  float vibrato;
  float velocity;
  float roll;
  float pitch;
  float gyroRate;
  bool recording;
  uint8_t label;
  bool calibrating;
  uint16_t calibrationCount;
};
