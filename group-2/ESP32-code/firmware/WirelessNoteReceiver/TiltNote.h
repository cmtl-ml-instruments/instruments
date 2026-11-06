#pragma once
#include <stdint.h>
#include <SensorPacket.h>

// One-note gate driven by the receiver's clock. Hold time filters brief motion
// spikes. A lost link or new transmitter session clears the note immediately.
struct TiltNote {
  enum class Event { None, On, Released, LinkLost, Restarted };
  static constexpr int midiNote = 60; // C4
  static constexpr float triggerDegrees = 22.0f;
  static constexpr float releaseDegrees = 12.0f;
  static constexpr uint32_t holdMs = 100;
  static constexpr uint32_t maxHoldGapMs = 40; // Restart a hold across a packet gap.

  bool active = false;
  bool armed = false;
  bool haveSample = false;
  bool holding = false;
  uint32_t holdStartedMs = 0;
  uint32_t lastSampleMs = 0;
  uint32_t session = 0;

  constexpr Event clear(Event reason) {
    const Event event = active ? reason : Event::None;
    active = armed = haveSample = holding = false;
    return event;
  }

  constexpr Event expire(uint32_t now) {
    if (haveSample && now - lastSampleMs >= sensorlink::STALE_MS) {
      return clear(Event::LinkLost);
    }
    return Event::None;
  }

  constexpr Event sample(float roll, uint32_t receivedMs, uint32_t bootSession) {
    Event event = expire(receivedMs);
    if (haveSample && session != bootSession) event = clear(Event::Restarted);
    if (haveSample && receivedMs - lastSampleMs > maxHoldGapMs) holding = false;
    haveSample = true;
    lastSampleMs = receivedMs;
    session = bootSession;

    // A brief crossing cannot arm, trigger, or release the note.
    const bool qualifies = !armed ? roll >= -releaseDegrees && roll <= releaseDegrees
                                 : active ? roll <= releaseDegrees : roll >= triggerDegrees;
    if (!qualifies) {
      holding = false;
      return event;
    }
    if (!holding) {
      holding = true;
      holdStartedMs = receivedMs;
      return event;
    }
    if (receivedMs - holdStartedMs < holdMs) return event;

    holding = false;
    if (!armed) {
      armed = true;
      return event;
    }
    active = !active;
    return active ? Event::On : Event::Released;
  }
};

constexpr bool checkTiltNote() {
  using Event = TiltNote::Event;
  TiltNote note;
  note.sample(30, 0, 1);
  for (uint32_t t = 10; t < 110; t += 25) note.sample(0, t, 1);
  if (note.armed || note.active) return false;
  note.sample(0, 110, 1);
  if (!note.armed) return false;

  note.sample(30, 120, 1);
  note.sample(17, 145, 1); // Brief excursion above +22°.
  note.sample(30, 160, 1);
  if (note.sample(30, 260, 1) != Event::None || note.active) return false;
  for (uint32_t t = 285; t < 360; t += 25) note.sample(30, t, 1);
  if (note.sample(30, 360, 1) != Event::On) return false;

  note.sample(0, 370, 1);
  if (note.sample(17, 395, 1) != Event::None || !note.active) return false;
  for (uint32_t t = 400; t < 500; t += 25) note.sample(12, t, 1);
  if (note.sample(12, 500, 1) != Event::Released) return false;

  for (uint32_t t = 510; t < 610; t += 25) note.sample(22, t, 1);
  return note.sample(22, 610, 1) == Event::On &&
         note.expire(1109) == Event::None && note.active &&
         note.expire(1110) == Event::LinkLost && !note.active && !note.armed &&
         note.expire(1120) == Event::None &&
         note.sample(30, 1130, 1) == Event::None && !note.armed;
}
static_assert(checkTiltNote(), "Tilt note must reject brief crossings and release on link loss");
