#pragma once
#include <math.h>
#include <stdint.h>

namespace gesture {
inline constexpr float clamp(float x, float lo, float hi) {
  return x < lo ? lo : (x > hi ? hi : x);
}
inline float angleDifference(float angle, float reference) {
  float difference = angle - reference;
  while (difference > 180.0f) difference -= 360.0f;
  while (difference < -180.0f) difference += 360.0f;
  return difference;
}
inline float rollDegrees(float y, float z) {
  return atan2f(y, z) * 57.2957795f;
}
inline float pitchDegrees(float x, float y, float z) {
  return atan2f(-x, sqrtf(y*y + z*z)) * 57.2957795f;
}

// Restore the original fixed -35..+35 degree -> indices 2..19 mapping.
// Calibration must not move this range to the board's boot/resting posture.
// A small 0.25 degree margin prevents chatter without a large dead zone.
inline constexpr int updateNoteIndex(float roll, int index) {
  if (roll <= -35.0f) return 2;
  if (roll >= 35.0f) return 19;
  const float position = 2.0f + (clamp(roll, -35.0f, 35.0f) + 35.0f) * (17.0f / 70.0f);
  const float margin = 0.25f * (17.0f / 70.0f);
  while (index < 19 && position >= index + 1.0f + margin) ++index;
  while (index > 2 && position < index - margin) --index;
  return index;
}
inline constexpr int updateOctave(float pitch, int octave) {
  if (pitch > 22.0f) return 1;
  if (pitch < -22.0f) return -1;
  if (octave == 1 && pitch < 18.0f) return 0;
  if (octave == -1 && pitch > -18.0f) return 0;
  return octave;
}

// Compile-time checks exercise actual mapping behavior, including the
// saturation/reversal cases that can otherwise make controls feel stuck.
static_assert(updateNoteIndex(0.0f, 2) == 10, "Level must restore the original note index");
static_assert(updateNoteIndex(0.0f, 19) == 10, "Return from either extreme must recover level");
static_assert(updateNoteIndex(2.0f, 10) == 10, "Hold inside the upward boundary");
static_assert(updateNoteIndex(2.4f, 10) == 11, "Small tilt must cross into the next note");
static_assert(updateNoteIndex(2.0f, 11) == 11, "Hold the new note within the hysteresis band");
static_assert(updateNoteIndex(1.7f, 11) == 10, "Return across the release boundary");
static_assert(updateNoteIndex(-2.4f, 10) == 9, "Small negative tilt must select the lower note");
static_assert(updateNoteIndex(-90.0f, 19) == 2, "Lower saturation must be bounded");
static_assert(updateNoteIndex(90.0f, 2) == 19, "Upper saturation must be bounded");
static_assert(updateOctave(23.0f, 0) == 1 && updateOctave(20.0f, 1) == 1 &&
              updateOctave(17.0f, 1) == 0, "Octave must enter, hold, then release");

// A complete stationary window is required; failed windows are discarded.
// Acceleration is retained (including gravity); only gyro bias is subtracted.
struct Calibration {
  static constexpr uint16_t required = 156;  // ~1.5 seconds at 104 Hz
  bool collecting = false;
  bool ready = false;
  uint16_t count = 0;
  float mean[6] = {};
  float m2[6] = {};
  float gyroBias[3] = {};
  float rollZero = 0, pitchZero = 0;
  float latest[6] = {};
  float gravityNorm = 0, rotationNorm = 0;
  float rejectedStd = 0;
  uint32_t rejectedWindows = 0;
  const char *reason = "not started";

  void resetWindow() {
    count = 0;
    for (int i=0; i<6; ++i) mean[i] = m2[i] = 0;
  }
  void begin() { collecting = true; rejectedWindows = 0; reason = "collecting"; resetWindow(); }
  bool add(const float values[6]) {
    for (int i=0; i<6; ++i) latest[i] = values[i];
    if (!collecting) return false;
    for (int i=0; i<6; ++i) {
      if (!isfinite(values[i])) { reason = "nonfinite sample"; ++rejectedWindows; resetWindow(); return false; }
    }
    const float gravity = sqrtf(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
    const float rotation = sqrtf(values[3]*values[3] + values[4]*values[4] + values[5]*values[5]);
    gravityNorm = gravity;
    rotationNorm = rotation;
    if (fabsf(gravity - 9.80665f) > 1.0f || rotation > 0.15f) {
      reason = fabsf(gravity - 9.80665f) > 1.0f ? "acceleration magnitude" : "rotation rate";
      ++rejectedWindows;
      resetWindow();
      return false;
    }
    ++count;
    for (int i=0; i<6; ++i) {
      float delta = values[i] - mean[i];
      mean[i] += delta / count;
      m2[i] += delta * (values[i] - mean[i]);
    }
    if (count < required) return false;
    for (int i=0; i<6; ++i) {
      const float maxVariance = i < 3 ? 0.04f : 0.0004f;
      if (m2[i] / (count - 1) > maxVariance) {
        reason = i < 3 ? "acceleration variance" : "gyro variance";
        rejectedStd = sqrtf(m2[i] / (count - 1));
        ++rejectedWindows;
        resetWindow();
        return false;
      }
    }
    for (int i=0; i<3; ++i) gyroBias[i] = mean[i+3];
    rollZero = rollDegrees(mean[1], mean[2]);
    pitchZero = pitchDegrees(mean[0], mean[1], mean[2]);
    collecting = false;
    ready = true;
    reason = "complete";
    return true;
  }
};
}
