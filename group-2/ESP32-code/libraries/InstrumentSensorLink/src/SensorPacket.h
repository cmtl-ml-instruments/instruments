#pragma once
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <string.h>

// Shared by both boards. Version 1 sends a fixed 44-byte little-endian packet
// with IEEE-754 floats. Change the version if the layout or units change.
namespace sensorlink {
constexpr uint8_t CHANNEL = 1;
constexpr uint32_t MAGIC = 0x314D5549; // "IUM1" on the wire
constexpr uint32_t STALE_MS = 500;
struct Packet {
  uint32_t magic = MAGIC;
  uint16_t version = 1;
  uint16_t bytes = 44;
  uint32_t session = 0; // Random boot identifier; sequence may restart on reboot.
  uint32_t sequence = 0; // Counts acquired samples so the receiver can detect gaps.
  uint32_t sampleUs = 0; // Sender clock, for sample spacing within this session.
  float axes[6] = {}; // ax, ay, az (m/s^2), gx, gy, gz (rad/s)
};
static_assert(sizeof(Packet) == 44, "Unexpected sensor wire format");

inline bool decode(const uint8_t *data, size_t length, Packet &packet) {
  if (!data || length != sizeof(Packet)) return false;
  memcpy(&packet, data, sizeof(Packet));
  if (packet.magic != MAGIC || packet.version != 1 || packet.bytes != sizeof(Packet)) return false;
  for (unsigned i = 0; i < 6; ++i) {
    // Gyro sensitivity is 17.5 mdps/LSB; full int16 headroom is ~10.008 rad/s.
    if (!isfinite(packet.axes[i]) || fabsf(packet.axes[i]) > (i < 3 ? 39.3f : 10.02f)) return false;
  }
  return true;
}

inline bool selfTest() {
  Packet input, output;
  input.axes[2] = 9.80665f;
  if (!decode(reinterpret_cast<uint8_t *>(&input), sizeof(input), output) ||
      output.axes[2] != input.axes[2]) return false;
  if (decode(reinterpret_cast<uint8_t *>(&input), sizeof(input) - 1, output)) return false;
  input.version = 2;
  if (decode(reinterpret_cast<uint8_t *>(&input), sizeof(input), output)) return false;
  input.version = 1;
  input.axes[0] = NAN;
  if (decode(reinterpret_cast<uint8_t *>(&input), sizeof(input), output)) return false;
  input.axes[0] = 40.0f;
  return !decode(reinterpret_cast<uint8_t *>(&input), sizeof(input), output);
}
}
