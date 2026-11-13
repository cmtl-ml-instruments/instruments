//CDC On boot : Enabled
//PSRAM : OPI PSRAM

#include <Wire.h>
#include <ST77922.h>
#include <ST77922_Touch.h>
#include <lvgl.h>
#include "src/ui/ui.h"
#include "src/ui/screens.h"
#include "src/ui/actions.h"
#include <SPI.h>
#include <AMY-Arduino.h>
#include <ES8311.h>
#include <Preferences.h>
#include "src/ui/vars.h"
#include <Adafruit_LSM6DSOX.h>
#include <LittleFS.h>

#define IRIS_MAX_OUT 32   //iris allows 16 outputs by default; we learn 18, so raise the limit (must come before the #include)
#include "iris.h"

#define LCD_BL_PIN   41   // Screen backlight

//I2C Pins (touch screen, shared with ES8311 codec)
#define I2C_SDA      38
#define I2C_SCL      39

//Audio Codec Pins
#define I2S_MCK      17
#define I2S_BCK      18
#define I2S_WS       21
#define I2S_DOUT     15

#define LCD_ROTATION_FLIP 0

//How many landscape rows LVGL draws at once (480 x 40 x 2 bytes = ~38 KB in fast internal RAM)
#define DRAW_BUF_LINES 40

uint16_t screenW, screenH;
uint16_t panelW, panelH;
uint16_t *panelBuf = nullptr;

enum ParamId { //An enum where each value represents a parameter
  //Mix page
  P_A_LEVEL,
  P_B_LEVEL,
  P_C_LEVEL,
  //Sources page
  P_A_MOD_INDEX,
  P_B_MOD_INDEX,
  P_C_MOD_INDEX,
  P_A_FEEDBACK,
  P_B_FEEDBACK,
  P_C_FEEDBACK,
  //Filters page
  P_GLOBAL_CUTOFF,
  P_GLOBAL_RESONANCE,
  P_A_RELATIVE_CUTOFF,
  P_B_RELATIVE_CUTOFF,
  P_C_RELATIVE_CUTOFF,
  P_FE_AMOUNT,
  P_FE_DECAY,
  //FX page
  P_VIBRATO_DEPTH,
  P_VIBRATO_RATE,
  P_DETUNE,
  P_CHORUS,
  P_ECHO,
  P_REVERB,
  NUM_PARAMS
};

struct Param {
  int osc;              //Which oscillator in the synth's voice
  const char* amyCode;  //AMY's letter for this parameter (nullptr = not sent to AMY yet)
  int32_t value;        //Current slider value
  float scale;          //AMY recieves value/scale
  const char* labelf;   //How label is formatted
};

//One row per entry in ParamId, in the SAME ORDER.
//  osc  amyCode  start value  scale    label format
Param params[] = {
  //Mix page: 0-100 -> 0.00-1.00
  {0, "a",     0,    100.0f, "%.2f"    },   //A level
  {3, "a",     0,    100.0f, "%.2f"    },   //B level
  {6, "a",     0,    100.0f, "%.2f"    },   //C level
  //Sources page: mod index 0-100 -> 0.0-10.0 (adjust scale by ear once it's connected to AMY)
  {2, "a",     0,    10.0f,  "%.1f"    },   //A mod index
  {5, "a",     0,    10.0f,  "%.1f"    },   //B mod index
  {8, "a",     0,    10.0f,  "%.1f"    },   //C mod index
  //Sources page: feedback 0-100 -> 0.00-1.00 (AMY's feedback range is 0-1)
  {0, "b",     0,    100.0f, "%.2f"    },   //A feedback
  {3, "b",     0,    100.0f, "%.2f"    },   //B feedback
  {6, "b",     0,    100.0f, "%.2f"    },   //C feedback
  //Filters page (set each slider's min/max in EEZ to the range in the comment)
  {0, nullptr, 684,  1.0f,   "%.0f"      },   //Global cutoff:     100 to 8000       -> Hz
  {0, nullptr, 7,    10.0f,  "%.1f"      },   //Global resonance:  0 to 100          -> 0.0-10.0
  {0, nullptr, 0,    10.0f,  "%+.1f"     },   //A relative cutoff: -30 to 30         -> -3.0 to +3.0 octaves
  {0, nullptr, 0,    10.0f,  "%+.1f"     },   //B relative cutoff: -30 to 30
  {0, nullptr, 0,    10.0f,  "%+.1f"     },   //C relative cutoff: -30 to 30
  {0, nullptr, 0,    100.0f, "%.2f"      },   //Filter env amount: 0 to 100          -> 0.00-1.00
  {0, nullptr, 300,  1.0f,   "%.0f"      },   //Filter env decay:  10 to 2000        -> ms
  //FX page (set each slider's min/max in EEZ to the range in the comment)
  {0, nullptr, 0,    1.0f,   "%.0f"      },   //Vibrato depth:     0 to 100          -> cents
  {0, nullptr, 50,   10.0f,  "%.1f"      },   //Vibrato rate:      5 to 100          -> 0.5-10.0 Hz
  {0, nullptr, 0,    1.0f,   "%.0f"      },   //Detune:            0 to 50           -> cents
  {0, nullptr, 0,    100.0f, "%.2f"      },   //Chorus mix:        0 to 100          -> 0.00-1.00
  {0, nullptr, 0,    100.0f, "%.2f"      },   //Echo mix:          0 to 100          -> 0.00-1.00
  {0, nullptr, 0,    100.0f, "%.2f"      },   //Reverb mix:        0 to 100          -> 0.00-1.00
};

char labelBufs[NUM_PARAMS][24];   //One 24-character text buffer per parameter

void updateFilterCutoffs(); //defined in FILTERS section
void sendResonance(); //defined in FILTERS section
void sendFilterEnvelope(); //defined in FILTERS section
void sendFx(int id); //defined in FX section

void sendParam(int id) {
  //The cutoff sliders don't go to AMY directly: each pair's cutoff is worked out from the global
  //cutoff and that pair's relative cutoff, so any of those four sliders updates all three filters.
  if (id == P_GLOBAL_CUTOFF || id == P_A_RELATIVE_CUTOFF ||
      id == P_B_RELATIVE_CUTOFF || id == P_C_RELATIVE_CUTOFF || id == P_FE_AMOUNT) {
    updateFilterCutoffs();
    return;
  }

  if (id == P_GLOBAL_RESONANCE) {
    sendResonance();
    return;
  }

  if (id == P_FE_DECAY) {
    sendFilterEnvelope();
    return;
  }

  if (id >= P_VIBRATO_DEPTH) {
    sendFx(id);
    return;
  }

  const Param& p = params[id];
  if (!p.amyCode) return;   //no AMY letter yet: the slider and label still work, AMY just isn't told
  char msg[32];
  snprintf(msg, sizeof(msg), "v%d%s%.3f", p.osc, p.amyCode, p.value / p.scale);
  if (strcmp(p.amyCode, "a") == 0 && p.osc % 3 != 0) { //strcamp comparers two strings and returns 0 when they are ==
    strcat(msg, ",,0,0"); //adds ",,0,0" at the end of msgs not sent to ALGO osc. This makes the messasges something like v2a3.500,,0,0
                          //so that it doesn't mess with the other components of amplitude
  }
  Serial.println(msg);
  amy_add_message(msg);
}

void sendAllParams() {
  for (int i = 0; i < NUM_PARAMS; i++) sendParam(i);
}

#define EEZ_PARAM(name, id)                                                 \
  int32_t get_var_##name() { return params[id].value; }                     \
  void set_var_##name(int32_t v) { params[id].value = v; sendParam(id); }

#define EEZ_LABEL(name, id)                                  \
  const char* get_var_##name() {                             \
    snprintf(labelBufs[id], sizeof(labelBufs[id]),           \
             params[id].labelf,                              \
             params[id].value / params[id].scale);           \
    return labelBufs[id];                                    \
  }

// ============================================================================
// Ratios: the Sources page dropdowns report a position in their list (0, 1, 2...),
// so this table turns that position into the actual ratio.
// ============================================================================

//Must list the same values, in the same order, as the dropdown options in EEZ.
static const float RATIOS[] = { 0.5f, 1.0f, 1.41f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 9.0f };
static constexpr int NUM_RATIOS = sizeof(RATIOS) / sizeof(RATIOS[0]);

#define RATIO_START 1                   //position each dropdown starts on (1 = ratio 1)
static int32_t ratioSel[3] = { RATIO_START, RATIO_START, RATIO_START };   //pairs A, B, C
static const int PITCH_OFFSETS[] = { -12, -7, 0, 7, 12 };
static const int NUM_PITCH_OFFSETS = 5;
#define PITCH_OFFSET_START 2
static int32_t pitchOffsetSel[3] = { PITCH_OFFSET_START, PITCH_OFFSET_START, PITCH_OFFSET_START };

void sendRatio(int pair) {
  float cents = params[P_DETUNE].value / params[P_DETUNE].scale;
  float sign = (pair == 1) ? 1.0f : (pair == 2) ? -1.0f : 0.0f; //A stays at 0, B detunes up from A, C detunes down from A
  float semitones = sign * cents / 100.0f + PITCH_OFFSETS[pitchOffsetSel[pair]];
  float factor = powf(2.0, semitones / 12.0f);
  char msg[24];
  snprintf(msg, sizeof msg, "v%dI%.4f", pair * 3 + 1, factor); //pair A (0) has carrier in osc 1, B (1) has carrier in osc 4, C (2) has carrier in osc 7
  amy_add_message(msg);
  snprintf(msg, sizeof msg, "v%dI%.4f", pair * 3 + 2, RATIOS[ratioSel[pair]] * factor); //modulator
  amy_add_message(msg);
}

void sendAllRatios() {
  for (int i = 0; i < 3; i++) sendRatio(i);
}

//Like EEZ_PARAM, but for a dropdown: stores the position (kept inside the list) and sends the ratio
#define EEZ_RATIO(name, pair)                                               \
  int32_t get_var_##name() { return ratioSel[pair]; }                       \
  void set_var_##name(int32_t v) {                                          \
    ratioSel[pair] = constrain(v, 0, NUM_RATIOS - 1);                       \
    sendRatio(pair);                                                        \
  }

#define EEZ_PITCH_OFFSET(name, pair)                                        \
  int32_t get_var_##name() { return pitchOffsetSel[pair]; }                 \
  void set_var_##name(int32_t v) {                                          \
    pitchOffsetSel[pair] = constrain(v, 0, NUM_PITCH_OFFSETS - 1);          \
    sendRatio(pair);                                                        \
    updateFilterCutoffs();                                                  \
  }

// ============================================================================
// Filters: each pair's cutoff = global cutoff x 2^(relative cutoff in octaves),
// and each pair's filter type comes from its dropdown.
// ============================================================================

#define CUTOFF_MIN_HZ     50.0f      //keeps a low global cutoff + negative offset from going too low
#define CUTOFF_MAX_HZ     15000.0f   //and a high one + positive offset from going too high
#define CUTOFF_LOW_HZ     100.0f    //cutoff at the bottom of the slider
#define CUTOFF_HIGH_HZ    8000.0f   //cutoff at the top
#define CUTOFF_SLIDER_MAX 1000
#define FE_MAX_OCTAVES    4.0f
#define KEY_TRACKING 0.75f
#define KEY_TRACKING_REFERENCE 60
float currentNote = KEY_TRACKING_REFERENCE;
float pairCutoffHz[3];             //the cutoff each pair actually gets, A B C

//Recalculates all three pairs' cutoffs. Runs whenever the global or a relative cutoff changes.

float sliderToCutoff(int32_t pos) {
  return CUTOFF_LOW_HZ * powf(CUTOFF_HIGH_HZ / CUTOFF_LOW_HZ, pos / (float)CUTOFF_SLIDER_MAX);
}

void updateFilterCutoffs() {
  float global = sliderToCutoff(params[P_GLOBAL_CUTOFF].value);
  const ParamId rel[3] = { P_A_RELATIVE_CUTOFF, P_B_RELATIVE_CUTOFF, P_C_RELATIVE_CUTOFF };
  for (int i = 0; i < 3; i++) {
    float pairNote = currentNote + PITCH_OFFSETS[pitchOffsetSel[i]];
    float keyOctaves = KEY_TRACKING * (pairNote - KEY_TRACKING_REFERENCE) / 12.0f;
    float octaves = params[rel[i]].value / params[rel[i]].scale;
    float feOctaves = params[P_FE_AMOUNT].value / params[P_FE_AMOUNT].scale * FE_MAX_OCTAVES;
    pairCutoffHz[i] = constrain(global * powf(2.0f, octaves + keyOctaves), CUTOFF_MIN_HZ, CUTOFF_MAX_HZ);
    char msg[32];
    snprintf(msg, sizeof msg, "v%dF%.1f,,,,%.2f", i * 3, pairCutoffHz[i], feOctaves);
    // Serial.println(msg); //debug
    amy_add_message(msg);
  }
}

void sendResonance() {
  float q = params[P_GLOBAL_RESONANCE].value / params[P_GLOBAL_RESONANCE].scale; //applies the scale defined in the parameters array to the value
  for (int i = 0; i < 3; i++) {
    char msg[24];
    snprintf(msg, sizeof msg, "v%dR%.2f", i * 3, q);
    amy_add_message(msg);
  }
}

void sendFilterEnvelope() {
  int decayMs = params[P_FE_DECAY].value;
  for (int i = 0; i < 3; i++) {
    char msg[32];
    snprintf(msg, sizeof msg, "v%dB0,1,%d,0,0,0", i* 3, decayMs);
    Serial.println(msg);
    amy_add_message(msg);
  }
}

//Dropdown position = AMY's filter type (G): 0 low-pass, 1 band-pass, 2 high-pass (sendFilterType() adds 1 for proper AMY formatting)
//as long as the dropdown options are in that order in EEZ.
#define NUM_FILTER_TYPES  3
#define FILTER_TYPE_START 0   //low-pass, same as the G1 the sketch already sends
static const char *FILTER_TYPE_NAMES[NUM_FILTER_TYPES] = { "Low-pass", "Band-pass", "High-pass" };
static int32_t filterType[3] = { FILTER_TYPE_START, FILTER_TYPE_START, FILTER_TYPE_START };   //A B C

void sendFilterType(int pair) {
  char msg[16];
  snprintf(msg, sizeof msg, "v%dG%d", pair * 3, (int)filterType[pair] + 1);
  amy_add_message(msg);
}

void sendAllFilterTypes() {
  for (int i = 0; i < 3; i++) sendFilterType(i);
}

//Like EEZ_RATIO: stores the dropdown position (kept inside the list) and sends it
#define EEZ_FILTER_TYPE(name, pair)                                         \
  int32_t get_var_##name() { return filterType[pair]; }                     \
  void set_var_##name(int32_t v) {                                          \
    filterType[pair] = constrain(v, 0, NUM_FILTER_TYPES - 1);               \
    sendFilterType(pair);                                                   \
  }

// ============================================================================
// FX: Vibrato (LFO on osc9), detune, and AMY's global FX (reverb, chorus, echo)
// ============================================================================

#define ECHO_DELAY_MS     300
#define ECHO_MAX_DELAY_MS 1000 //longest echo AMY sets aside memory for
#define ECHO_FEEDBACK     0.4f

void sendFx(int id) {
  float v = params[id].value / params[id].scale;
  char msg[40];
  switch (id) { //switch executes the code block under the case that matches the input, and then continues executing the following code blocks until a return or break statement
    case P_VIBRATO_DEPTH:
      for (int i = 0; i < 3; i++) {
        snprintf(msg, sizeof msg, "v%df,,,,,%.4f", i * 3, v / 1200.0f);
        amy_add_message(msg);
      }
      return; //leaves the whole function
    case P_VIBRATO_RATE:
      snprintf(msg, sizeof msg, "v9f%.2f", v);
      break; //leaves the switch block but executes the last line of the function
    case P_DETUNE:
      sendAllRatios();
      return;
    case P_CHORUS:
      snprintf(msg, sizeof msg, "k%.2f", v);
      break;
    case P_ECHO:
      snprintf(msg, sizeof msg, "M%.2f,%d,%d,%.2f,0", v, ECHO_DELAY_MS, ECHO_MAX_DELAY_MS, ECHO_FEEDBACK);
      break;
    case P_REVERB:
      snprintf(msg, sizeof msg, "h%.2f", v);
      break;
    default: //safety for if the code changes later
      return;
  }
  amy_add_message(msg);
}


// ============================================================================
// Pitch: performance mode, starting note, relative pitch, scale, and the arpeggiator settings.
// The dropdowns report a POSITION, so each list below must match its dropdown's options in EEZ,
// in the same order.
// ============================================================================

//Performance mode dropdown: options in this order
#define PERF_ARPEGGIATE 0
#define PERF_QUANTIZED  1
#define PERF_CONTINUOUS 2
static int32_t performanceMode = PERF_ARPEGGIATE;   //the current behavior: notes step on their own

//Scale dropdown: options in this order. Each scale is its notes in semitones above the root.
struct Scale { const char *name; int count; int steps[12]; };
static const Scale SCALES[] = {
  { "Pentatonic", 5,  { 0, 2, 4, 7, 9 } },
  { "Major",      7,  { 0, 2, 4, 5, 7, 9, 11 } },
  { "Minor",      7,  { 0, 2, 3, 5, 7, 8, 10 } },
  { "Chromatic",  12, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} },
};
static constexpr int NUM_SCALES = sizeof(SCALES) / sizeof(SCALES[0]);
static int32_t scaleSel = 0;

//Arp pattern dropdown: options in this order
static const char *ARP_PATTERNS[] = { "Up", "Down", "Up-Down", "Down-Up", "Random", "Random walk", "Converge", "Thumb" };
static constexpr int NUM_ARP_PATTERNS = sizeof(ARP_PATTERNS) / sizeof(ARP_PATTERNS[0]);
static int32_t arpPattern = 0;

//Starting note. If it's a SLIDER whose values are MIDI note numbers, leave the offset at 0.
//If it's a DROPDOWN (or roller) listing one note per semitone, set the offset to the MIDI number
//of its FIRST option, e.g. 36 if the list starts at C2. Then note = position + offset.
#define STARTING_NOTE_OFFSET 0
static int32_t startingNoteRaw = 60 - STARTING_NOTE_OFFSET;   //starts on C4

//Relative pitch: symmetrical slider, -240 to 240 in EEZ -> -24.0 to +24.0 semitones
#define RELATIVE_PITCH_SCALE 10.0f
static int32_t relativePitch = 0;

//Arp range: range slider, -24 to 24 in EEZ: semitones RELATIVE to the starting note,
//like the relative pitch slider. So changing the starting note moves the whole range with it.
static int32_t arpRangeMin = -12;   //one octave below the starting note
static int32_t arpRangeMax =  12;   //one octave above

//Arp speed: slider, 60 to 200 BPM
#define ARP_SPEED_MIN 60
#define ARP_SPEED_MAX 200
static int32_t arpSpeedBpm = 120;
static char arpSpeedBuf[8];

#define NOTE_LOWEST  24
#define NOTE_HIGHEST 108

static const char *NOTE_NAMES[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

//60 -> "C4", 61 -> "C#4": the remainder after /12 is the note, and /12 - 1 is the octave
void noteName(int n, char *buf, size_t len) {
  snprintf(buf, len, "%s%d", NOTE_NAMES[((n % 12) + 12) % 12], n / 12 - 1);
}

//MIDI note (with decimals) -> Hz. 69 is A4 = 440 Hz, and every 12 semitones doubles the frequency.
float noteToHz(float note) {
  return 440.0f * powf(2.0f, (note - 69.0f) / 12.0f);
}

int startingNote() {
  return startingNoteRaw + STARTING_NOTE_OFFSET;
}

//Starting note + relative pitch, as a MIDI note with decimals (used as-is in Continuous mode)
float targetNote() {
  float n = startingNote() + relativePitch / RELATIVE_PITCH_SCALE;
  return constrain(n, (float)NOTE_LOWEST, (float)NOTE_HIGHEST);
}

//The scale note closest to `note`. The starting note is the scale's root (its "home" note).
int nearestScaleNote(float note) {
  const Scale &sc = SCALES[scaleSel];
  int root = startingNote();
  int best = root;
  float bestDist = 1e9f;
  for (int oct = -6; oct <= 6; oct++) {
    for (int k = 0; k < sc.count; k++) {
      int candidate = root + 12 * oct + sc.steps[k];
      float dist = fabsf(candidate - note);
      if (dist < bestDist) { bestDist = dist; best = candidate; }
    }
  }
  return best;
}

//The actual note an arp range knob points at: starting note + its offset, kept between C1 and C8
int arpRangeNote(int32_t offset) {
  return constrain(startingNote() + (int)offset, NOTE_LOWEST, NOTE_HIGHEST);
}

static char relPitchBuf[16], arpMinBuf[8], arpMaxBuf[8];

//Reads BOTH knobs of the arp range slider straight from LVGL whenever it moves. It's added after
//EEZ's own handler, so it runs last and stores the right value for each knob, even if EEZ's
//generated code mixes them up. EEZ's next ui_tick() then draws the knobs from these values.
static void arp_range_cb(lv_event_t *e) {
  lv_obj_t *slider = lv_event_get_target(e);
  int32_t lo = lv_slider_get_left_value(slider);   //left knob
  int32_t hi = lv_slider_get_value(slider);        //right knob
  if (hi <= lo) hi = lo + 1;                       //keep them at least one note apart
  arpRangeMin = lo;
  arpRangeMax = hi;
}

//Attaches arp_range_cb once, as soon as the Pitch page (and so the slider) exists
static void hookArpRange() {
  static bool hooked = false;
  if (hooked || !objects.arp_range_slider) return;
  lv_obj_add_event_cb(objects.arp_range_slider, arp_range_cb, LV_EVENT_VALUE_CHANGED, NULL);
  hooked = true;
}

//Sets the arp speed slider's range to 60-200 BPM once it exists
//(named arp_speed_slider in EEZ)
static void setupArpSpeed() {
  static bool done = false;
  if (done || !objects.arp_speed_slider) return;
  lv_slider_set_range(objects.arp_speed_slider, ARP_SPEED_MIN, ARP_SPEED_MAX);
  done = true;
}

//Shows or hides one widget. Skips it if its page hasn't been built yet.
void showIf(lv_obj_t *obj, bool show) {
  if (!obj) return;
  if (show) lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
  else      lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

//Shows only the Pitch page controls that matter for the current performance mode.
//Called whenever the mode changes, at startup, and on every page change (in case the Pitch
//page was just built).
void updatePitchUI() {
  hookArpRange();   //once the Pitch page exists, take over reading the arp range knobs
  setupArpSpeed();  //and set the arp speed slider's range

  bool arp       = (performanceMode == PERF_ARPEGGIATE);
  bool usesScale = (performanceMode != PERF_CONTINUOUS);   //Quantized and Arpeggiate

  //Relative pitch: Continuous and Quantized
  showIf(objects.relative_pitch_slider,      !arp);
  showIf(objects.relative_pitch_label,       !arp);
  showIf(objects.relative_pitch_value_label, !arp);

  //Arp range and pattern: Arpeggiate only
  showIf(objects.arp_range_slider,          arp);
  showIf(objects.arp_range_label,           arp);
  showIf(objects.arp_range_min_value_label, arp);
  showIf(objects.arp_range_max_value_label, arp);
  showIf(objects.arp_pattern_dropdown,      arp);
  showIf(objects.arp_pattern_label,         arp);
  showIf(objects.arp_speed_slider,          arp);   //arp speed slider
  showIf(objects.arp_speed_label,           arp);
  showIf(objects.arp_speed_value_label,     arp);

  //Scale: Quantized and Arpeggiate (Continuous doesn't snap to notes)
  showIf(objects.scale_dropdown, usesScale);
  showIf(objects.scale_label,    usesScale);
}

// ============================================================================
// Play Modes:
// ============================================================================

#define PITCH_INTERVAL_MS 10

static int32_t lastMode = -1;       //the mode loop() played last time to notice a change
static int quantizedNote = -1;          //Quantized: the current note
static int continuousBaseNote = 60;       //Continuous: the note that was last played, bend is measured
static float lastBend = 0;          //Continuous: the bend last sent in octaves
static float lastTrackedNote = 0;   //Continuous: the pitch cutoffs were last updated for

void sendPitchBend(float octaves) { //Bends the pitch that was playing rather than starting a new note
  char msg[16];
  snprintf(msg, sizeof msg, "s%.4f", octaves);
  amy_add_message(msg);
  lastBend = octaves;
}

//For the quantized mode, plays a new pitch whenever pitch is snapped to a new note
void playQuantized(bool entering) {
  int note = nearestScaleNote(targetNote());
  if (entering || note != quantizedNote) {
    quantizedNote = note;
    updateSynthSound(note);
  }
}

void playContinuous(bool entering) {
  float target = targetNote();
  if (entering) {
    continuousBaseNote = (int)roundf(target);
    sendPitchBend(0);
    updateSynthSound(continuousBaseNote);
    lastTrackedNote = continuousBaseNote;
  }

  float bend = (target - continuousBaseNote) / 12.0f;
  if (fabsf(bend - lastBend) > 0.0005f) { //fabsf finds the absolute value of a float and returns a float
    sendPitchBend(bend);
  }

  if (fabsf(target - lastTrackedNote) > 0.1f) {
    currentNote = target;
    updateFilterCutoffs();
    lastTrackedNote = target;
  }
}

// ============================================================================
// Arpeggiator:
// ============================================================================

#define MAX_ARP_NOTES 64
static int arpNotes[MAX_ARP_NOTES];
static int arpCount = 0;
static int arpStep = 0;
static int arpWalk = 0;

bool inScale(int note) {
  const Scale &sc = SCALES[scaleSel]; //&sc makes a reference to SCALES[scaleSel] rather than a copy of it
  int degree = ((note - startingNote()) % 12 + 12) % 12; //finds the note's position within its octave
  for (int k = 0; k < sc.count; k++) { //sc.count is the number of notes in the scale
    if (sc.steps[k] == degree) { //checks each scale degree and returns true if the given note is in the scale
      return true;
    }
  }
  return false; //returns false otherwise
}

void buildArpNotes() {
  int low = arpRangeNote(arpRangeMin);
  int high = arpRangeNote(arpRangeMax);
  arpCount = 0;
  for (int n = low; n <= high && arpCount < MAX_ARP_NOTES; n++) {
    if (inScale(n)) {
      arpNotes[arpCount++] = n;
    }
  }
}

int nextArpNote() {
  buildArpNotes();
  if (arpCount == 0) {
    return startingNote();
  }
  int n = arpCount;
  int idx; //index
  switch (arpPattern) { //each pattern is a different rule for choosing the nextArpNote() index
    case 0: //up
      idx = arpStep % n;
      break;
    case 1: //down
      idx = n - 1 - arpStep % n;
      break;
    case 2: //Up-Down
    case 3: { //Down-UP
      int cycle = (n > 1) ? 2 * (n - 1) : 1; //up and down, without repeating ends
      int s = arpStep % cycle;
      idx = (s < n) ? s : cycle - s;
      if (arpPattern == 3) {
        idx = n - 1 - idx; //Down-Up is flipped
      }
      break;
    }
    case 4: //random
      idx = random(n);
      break;
    case 5: //Random walk
      arpWalk += random(2) ? 1 : -1;
      if (arpWalk < 0) {
        arpWalk = (n > 1) ? 1 : 0;
      }
      if (arpWalk >= n) {
        arpWalk = (n > 1) ? n - 2 : 0;
      }
      idx = arpWalk;
      break;
    case 6: { //Converge: lowest, highest, second lowest, secont highest, etc.
      int s = arpStep % n;
      idx = (s % 2 == 0) ? s / 2 : n - 1 - s / 2;
      break;
    }
    case 7: { //Thumb: the lowest note plays after every note
      if (n == 1) {
        idx = 0;
        break;
      }
      int s = arpStep % (2 * (n - 1));
      idx = (s % 2 == 0) ? 0 : 1 + s / 2;
      break;
    }
    default: //just in case
      idx = 0;
  }
  arpStep++;
  return arpNotes[idx];
}

// ============================================================================
// NAV BAR: a row of page buttons along the bottom, on LVGL's top layer (every page)
// ============================================================================

// One button per page. When you add a page in EEZ Studio, add a row here:
//   { "Button text", SCREEN_ID_... }   (the SCREEN_ID_ name comes from src/ui/screens.h)
struct NavItem { const char *label; enum ScreensEnum page; };
static const NavItem NAV_ITEMS[] = {
  { "Mix",         SCREEN_ID_MIX         },
  { "Sources",     SCREEN_ID_SOURCES     },
  { "Filters",     SCREEN_ID_FILTERS     },
  { "Motion & FX", SCREEN_ID_MOTION___FX },
  { "Pitch",       SCREEN_ID_PITCH       },
  //Presets isn't here: it has its own button in the top-right corner (TOP BAR section)
};
static constexpr int NAV_COUNT = sizeof(NAV_ITEMS) / sizeof(NAV_ITEMS[0]);

#define NAV_HEIGHT       30   // pixels; keep the bottom 30 px of every EEZ page empty
#define NAV_HIDE_ON_PAGE 0    // 0 = shown on every page, or a SCREEN_ID_... to hide it on that page

static lv_obj_t *navBar = nullptr;
static lv_obj_t *navBtns[NAV_COUNT];

// Highlight the current page's button, and hide the bar on NAV_HIDE_ON_PAGE.
void navUpdate(enum ScreensEnum id) {
  if (!navBar) return;
  for (int i = 0; i < NAV_COUNT; i++) {
    if (NAV_ITEMS[i].page == id) lv_obj_add_state(navBtns[i], LV_STATE_CHECKED);
    else                         lv_obj_clear_state(navBtns[i], LV_STATE_CHECKED);
  }
  if (id == NAV_HIDE_ON_PAGE) lv_obj_add_flag(navBar, LV_OBJ_FLAG_HIDDEN);
  else                        lv_obj_clear_flag(navBar, LV_OBJ_FLAG_HIDDEN);
}

void hookDropdowns();                 // defined in the DROPDOWNS section below
void topBarUpdate(enum ScreensEnum id);  // defined in the TOP BAR section below
void presetsUIHook();                  // defined in the PRESETS section below

// Change page AND update the nav bar. Use this instead of loadScreen().
void goToPage(enum ScreensEnum id) {
  loadScreen(id);
  navUpdate(id);
  topBarUpdate(id);     // hide Record/Undo/status on pages where they don't belong
  updatePitchUI();      // Pitch page: show the current mode's controls (the page may have just been built)
  hookDropdowns();      // catch dropdowns on pages EEZ builds only when first opened
  presetsUIHook();      // set up the Presets page the first time it exists
}

// Every nav button calls this; user_data says which row of NAV_ITEMS it is.
static void nav_btn_cb(lv_event_t *e) {
  int i = (int)(intptr_t)lv_event_get_user_data(e);
  goToPage(NAV_ITEMS[i].page);
}

// Builds the bar. Called once in setup(), after ui_init().
void navCreate() {
  navBar = lv_obj_create(lv_layer_top());
  lv_obj_set_size(navBar, LV_PCT(100), NAV_HEIGHT);
  lv_obj_align(navBar, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_clear_flag(navBar, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(navBar, lv_color_hex(0x202020), 0);
  lv_obj_set_style_border_width(navBar, 0, 0);
  lv_obj_set_style_radius(navBar, 0, 0);
  lv_obj_set_style_pad_all(navBar, 4, 0);
  lv_obj_set_style_pad_column(navBar, 4, 0);
  lv_obj_set_flex_flow(navBar, LV_FLEX_FLOW_ROW);

  for (int i = 0; i < NAV_COUNT; i++) {
    lv_obj_t *btn = lv_btn_create(navBar);
    lv_obj_set_flex_grow(btn, 1);
    lv_obj_set_height(btn, LV_PCT(100));
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x404040), 0);
    lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_CHECKED);
    lv_obj_add_event_cb(btn, nav_btn_cb, LV_EVENT_CLICKED, (void *)(intptr_t)i);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, NAV_ITEMS[i].label);
    lv_obj_center(lbl);
    navBtns[i] = btn;
  }
}

// ============================================================================
// Volume: a vertical master-volume slider on the right edge, on LVGL's top layer (every page)
// ============================================================================
// Sets AMY's global volume (wire code V). The codec stays at a fixed level, set in setup().
// Only the knob can be grabbed (not the track), so a hand holding the device's edge won't bump it.

#define VOLUME_START   0    // volume at power-on, 0-100
#define VOLUME_PANEL_W 52    // pixels; keep the right 56 px of every EEZ page empty
#define AMY_VOLUME_MAX 2.0f // AMY volume at the top of the slider (AMY's default is 1.0, max about 10)
#define CODEC_VOLUME   75   // fixed codec output level, 0-100

bool codecReady = false;     // set in setup() once the codec answers
bool amyReady   = false;     // set in setup() once AMY has started
static int32_t   masterVolume = VOLUME_START;
static lv_obj_t *volLabel     = nullptr;

//Slider 0-100 -> AMY volume 0 to AMY_VOLUME_MAX
void sendVolume() {
  if (!amyReady) return;
  char msg[16];
  snprintf(msg, sizeof msg, "V%.2f", masterVolume / 100.0f * AMY_VOLUME_MAX);
  amy_add_message(msg);
}

static void volume_cb(lv_event_t *e) {
  lv_obj_t *slider = lv_event_get_target(e);
  masterVolume = lv_slider_get_value(slider);
  sendVolume();
  lv_label_set_text_fmt(volLabel, "%d", (int)masterVolume);
}

// Builds the panel. Called once in setup(), after ui_init().
void volumeCreate() {
  lv_color_t accent = lv_palette_main(LV_PALETTE_BLUE);

  // Backdrop panel: from below the top strip (y = 56) to just above the nav bar
  lv_obj_t *panel = lv_obj_create(lv_layer_top());
  lv_obj_set_size(panel, VOLUME_PANEL_W, 320 - 60 - NAV_HEIGHT + 1);
  lv_obj_align(panel, LV_ALIGN_TOP_RIGHT, -4, 56);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(panel, lv_color_hex(0x1A1A1A), 0);
  lv_obj_set_style_border_color(panel, accent, 0);
  lv_obj_set_style_border_width(panel, 1, 0);
  lv_obj_set_style_radius(panel, 10, 0);
  lv_obj_set_style_pad_all(panel, 6, 0);
  lv_obj_set_style_pad_row(panel, 6, 0);
  lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);          // icon, slider, value: top to bottom
  lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  // Speaker icon at the top
  lv_obj_t *icon = lv_label_create(panel);
  lv_label_set_text(icon, LV_SYMBOL_VOLUME_MAX);
  lv_obj_set_style_text_color(icon, accent, 0);

  // The slider: taller than wide, so LVGL makes it vertical. flex_grow fills the leftover height.
  lv_obj_t *slider = lv_slider_create(panel);
  lv_obj_set_width(slider, 14);
  lv_obj_set_flex_grow(slider, 1);
  lv_slider_set_range(slider, 0, 100);
  lv_slider_set_value(slider, masterVolume, LV_ANIM_OFF);
  lv_obj_set_style_bg_color(slider, lv_color_hex(0x404040), LV_PART_MAIN);       // empty track
  lv_obj_set_style_bg_color(slider, accent, LV_PART_INDICATOR);                  // filled part
  lv_obj_set_style_bg_color(slider, accent, LV_PART_KNOB);
  lv_obj_set_style_pad_all(slider, 6, LV_PART_KNOB);                             // bigger knob to grab
  lv_obj_add_flag(slider, LV_OBJ_FLAG_ADV_HITTEST);                              // knob only, not the track
  lv_obj_add_event_cb(slider, volume_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // Value at the bottom
  volLabel = lv_label_create(panel);
  lv_obj_set_style_text_color(volLabel, lv_color_white(), 0);
  lv_label_set_text_fmt(volLabel, "%d", (int)masterVolume);
}

// ============================================================================
// TOP BAR: Record and Undo buttons, a status label, and the Presets button, on LVGL's top layer
// (every page except Presets)
// ============================================================================
// UI only for now: the buttons call onRecord() / onUndo(), which just report that they were
// pressed. When iris is added, its code goes inside those two functions.

void irisRecord();       //defined in the IRIS section
void irisUndo();         //defined in the IRIS section
void irisToggleMode();   //defined in the IRIS section

static lv_obj_t *recBtn = nullptr, *undoBtn = nullptr, *statusLbl = nullptr, *presetsBtn = nullptr;
static lv_obj_t *modeBtn = nullptr;   //TEACH / PLAY button; statusLbl is the text inside it

#define TOPBAR_HIDE_ON_PAGE SCREEN_ID_PRESETS   //the whole top bar is hidden on this page

//Shows Record, Undo, status and the Presets button on every page except TOPBAR_HIDE_ON_PAGE.
//(On the Presets page, the nav bar gets you back.) Called on every page change.
void topBarUpdate(enum ScreensEnum id) {
  lv_obj_t *parts[4] = { recBtn, undoBtn, modeBtn, presetsBtn };
  for (int i = 0; i < 4; i++) {
    if (!parts[i]) continue;   //not created yet
    if (id == TOPBAR_HIDE_ON_PAGE) lv_obj_add_flag(parts[i], LV_OBJ_FLAG_HIDDEN);
    else                           lv_obj_clear_flag(parts[i], LV_OBJ_FLAG_HIDDEN);
  }
}

//Shows text in the status label (top-left, every page)
void setStatus(const char *text) {
  if (statusLbl) lv_label_set_text(statusLbl, text);
}

//Record a take (current gesture + the learned sliders' values in params[])
void onRecord() {
  Serial.println("[UI] Record pressed");
  irisRecord();
}

//Delete the most recent take
void onUndo() {
  Serial.println("[UI] Undo pressed");
  irisUndo();
}

static void rec_cb(lv_event_t *e)     { onRecord(); }
static void undo_cb(lv_event_t *e)    { onUndo(); }
static void mode_cb(lv_event_t *e)    { irisToggleMode(); }
static void presets_cb(lv_event_t *e) { goToPage(SCREEN_ID_PRESETS); }

//Builds the buttons and label. Called once in setup(), after ui_init().
void topBarCreate() {
  recBtn = lv_btn_create(lv_layer_top());
  lv_obj_set_size(recBtn, 90, 40);
  lv_obj_align(recBtn, LV_ALIGN_TOP_LEFT, 10, 10);
  lv_obj_set_style_bg_color(recBtn, lv_palette_main(LV_PALETTE_RED), 0);
  lv_obj_add_event_cb(recBtn, rec_cb, LV_EVENT_RELEASED, NULL);   //on finger lift, so the tap doesn't jolt the pose
  lv_obj_t *recLbl = lv_label_create(recBtn);
  lv_label_set_text(recLbl, "Record");
  lv_obj_center(recLbl);

  undoBtn = lv_btn_create(lv_layer_top());
  lv_obj_set_size(undoBtn, 80, 40);
  lv_obj_align_to(undoBtn, recBtn, LV_ALIGN_OUT_RIGHT_MID, 8, 0);
  lv_obj_add_event_cb(undoBtn, undo_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_t *undoLbl = lv_label_create(undoBtn);
  lv_label_set_text(undoLbl, "Undo");
  lv_obj_center(undoLbl);

  //Mode button: shows TEACH or PLAY and the number of poses; tap to switch
  modeBtn = lv_btn_create(lv_layer_top());
  lv_obj_set_size(modeBtn, 150, 40);
  lv_obj_align_to(modeBtn, undoBtn, LV_ALIGN_OUT_RIGHT_MID, 8, 0);
  lv_obj_set_style_bg_color(modeBtn, lv_color_hex(0x404040), 0);   //grey: TEACH
  lv_obj_add_event_cb(modeBtn, mode_cb, LV_EVENT_CLICKED, NULL);
  statusLbl = lv_label_create(modeBtn);   //the text inside the button
  lv_label_set_text(statusLbl, "TEACH");
  lv_obj_center(statusLbl);

  //Presets button: top-right corner, kept apart from the sound-design pages in the nav bar
  presetsBtn = lv_btn_create(lv_layer_top());
  lv_obj_set_size(presetsBtn, 100, 40);
  lv_obj_align(presetsBtn, LV_ALIGN_TOP_RIGHT, -10, 10);
  lv_obj_add_event_cb(presetsBtn, presets_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_t *presetsLbl = lv_label_create(presetsBtn);
  lv_label_set_text(presetsLbl, "Presets");
  lv_obj_center(presetsLbl);
}

// ============================================================================
// DROPDOWNS: an open dropdown list is drawn on the page, which sits UNDER the overlay
// (nav bar, volume, Record/Undo). Every time a dropdown opens, LVGL puts its list back on the
// page, so this moves the list onto LVGL's system layer (above the overlay) right after it opens.
// ============================================================================

#define MAX_DROPDOWNS 32
static lv_obj_t *hookedDropdowns[MAX_DROPDOWNS];
static int hookedCount = 0;

//Runs after LVGL has handled the dropdown's own events, so the list is already open and placed.
static void dropdown_open_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code != LV_EVENT_RELEASED && code != LV_EVENT_CLICKED && code != LV_EVENT_READY) return;
  lv_obj_t *list = lv_dropdown_get_list(lv_event_get_target(e));
  if (list && !lv_obj_has_flag(list, LV_OBJ_FLAG_HIDDEN) && lv_obj_get_parent(list) != lv_layer_sys()) {
    lv_obj_set_parent(list, lv_layer_sys());   //same spot on screen, now above the overlay
  }
}

static bool isHooked(lv_obj_t *dd) {
  for (int i = 0; i < hookedCount; i++) if (hookedDropdowns[i] == dd) return true;
  return false;
}

//Looks through obj and everything inside it, and hooks every dropdown it hasn't hooked yet
static void hookDropdownsIn(lv_obj_t *obj) {
  if (lv_obj_check_type(obj, &lv_dropdown_class) && !isHooked(obj) && hookedCount < MAX_DROPDOWNS) {
    lv_obj_add_event_cb(obj, dropdown_open_cb, LV_EVENT_ALL, NULL);
    hookedDropdowns[hookedCount++] = obj;
  }
  uint32_t n = lv_obj_get_child_cnt(obj);
  for (uint32_t i = 0; i < n; i++) hookDropdownsIn(lv_obj_get_child(obj, i));
}

//Checks every page that exists. Called in setup() after ui_init(), and again on every page change
//in case EEZ only builds a page when it's first opened.
void hookDropdowns() {
  int before = hookedCount;
  lv_disp_t *disp = lv_disp_get_default();
  for (uint32_t i = 0; i < disp->screen_cnt; i++) hookDropdownsIn(disp->screens[i]);
  if (hookedCount != before) Serial.printf("[UI] Dropdowns hooked: %d\n", hookedCount);
}

// ============================================================================
// PRESETS: a scrolling list of saved sounds, with Save (asks for a name), Load, Edit (rename)
// and Delete (asks first). Presets are kept in flash, so they survive power-off.
// ============================================================================

void irisSaveToPreset(int i);                              //defined in the IRIS section
void irisLoadFromPreset(int i);                            //defined in the IRIS section
void irisDeletePresetFile(int removed, int countBefore);   //defined in the IRIS section

#define MAX_PRESETS     16
#define PRESET_NAME_LEN 24   //including the end-of-text character, so names are up to 23 letters

//Everything one preset remembers: its name and every setting on the sound pages.
//(Not the volume: that's a listening level, not part of the sound.)
struct Preset {
  char    name[PRESET_NAME_LEN];
  int32_t values[NUM_PARAMS];          //every slider in params[]
  int32_t ratio[3], filterTypes[3], pitchOffsets[3];    //Sources and Filters dropdowns
  int32_t perfMode, scale, startNote, relPitch, arpMin, arpMax, arpPat, arpSpeed;   //Pitch page
};

static Preset presets[MAX_PRESETS];
static int    presetCount = 0;
static int    presetSel   = -1;        //which preset is selected in the list, -1 = none
static Preferences presetStore;

//Note: functions here take a preset's NUMBER, not a Preset. The Arduino IDE adds a declaration of
//every function at the top of the sketch, above this struct, where "Preset" doesn't exist yet,
//so a function with a Preset parameter wouldn't compile.

//Copy the current settings into preset number i.
//(Takes a number, not a Preset: see the note under "struct Preset" above.)
void snapshotTo(int i) {
  Preset &p = presets[i];
  for (int k = 0; k < NUM_PARAMS; k++) p.values[k] = params[k].value;
  for (int k = 0; k < 3; k++) { p.ratio[k] = ratioSel[k]; p.filterTypes[k] = filterType[k]; p.pitchOffsets[k] = pitchOffsetSel[k]; }
  p.perfMode = performanceMode;  p.scale = scaleSel;     p.startNote = startingNoteRaw;
  p.relPitch = relativePitch;    p.arpMin = arpRangeMin; p.arpMax = arpRangeMax;
  p.arpPat   = arpPattern;     p.arpSpeed = arpSpeedBpm;
}

//Put preset number i's settings back. The sliders and labels follow on EEZ's next ui_tick();
//AMY is told here.
void applyPreset(int i) {
  const Preset &p = presets[i];
  for (int k = 0; k < NUM_PARAMS; k++) params[k].value = p.values[k];
  for (int k = 0; k < 3; k++) { ratioSel[k] = p.ratio[k]; filterType[k] = p.filterTypes[k]; pitchOffsetSel[k] = constrain(p.pitchOffsets[k], 0, NUM_PITCH_OFFSETS - 1); }
  performanceMode = p.perfMode;  scaleSel = p.scale;     startingNoteRaw = p.startNote;
  relativePitch   = p.relPitch;  arpRangeMin = p.arpMin; arpRangeMax = p.arpMax;
  arpPattern      = p.arpPat;    arpSpeedBpm = constrain(p.arpSpeed, ARP_SPEED_MIN, ARP_SPEED_MAX);
  sendAllParams();
  sendAllRatios();
  sendAllFilterTypes();
  updatePitchUI();   //show the right Pitch page controls for the loaded mode
  irisLoadFromPreset(i);   //and the iris poses it was saved with
}

// ---- Flash storage (one entry per preset: "p0", "p1", ...) ----

void savePresetsToFlash() {
  presetStore.begin("presets", false);
  presetStore.putInt("count", presetCount);
  for (int i = 0; i < presetCount; i++) {
    char key[8];
    snprintf(key, sizeof key, "p%d", i);
    presetStore.putBytes(key, &presets[i], sizeof(Preset));
  }
  presetStore.end();
}

//Skips any stored preset whose size doesn't match: that happens after params[] gains a slider,
//since old presets don't have a value for it.
void loadPresetsFromFlash() {
  presetStore.begin("presets", true);
  int n = presetStore.getInt("count", 0);
  presetCount = 0;
  for (int i = 0; i < n && i < MAX_PRESETS; i++) {
    char key[8];
    snprintf(key, sizeof key, "p%d", i);
    if (presetStore.getBytesLength(key) == sizeof(Preset)) {
      presetStore.getBytes(key, &presets[presetCount], sizeof(Preset));
      presets[presetCount].name[PRESET_NAME_LEN - 1] = '\0';   //always end the name safely
      presetCount++;
    }
  }
  presetStore.end();
  Serial.printf("[PRESETS] Loaded %d preset(s) from flash\n", presetCount);
}

// ---- The list ----

//Grey out Load, Edit and Delete unless a preset is selected
static void setEnabled(lv_obj_t *btn, bool on) {
  if (!btn) return;
  if (on) lv_obj_clear_state(btn, LV_STATE_DISABLED);
  else    lv_obj_add_state(btn, LV_STATE_DISABLED);
}
void updatePresetButtons() {
  bool sel = (presetSel >= 0 && presetSel < presetCount);
  setEnabled(objects.load_button,   sel);
  setEnabled(objects.edit_button,   sel);
  setEnabled(objects.delete_button, sel);
}

//Tapping an entry selects it (highlighted in blue). Only the highlight changes here: the list
//isn't rebuilt, because that would delete the very button whose tap is being handled.
static void preset_item_cb(lv_event_t *e) {
  presetSel = (int)(intptr_t)lv_event_get_user_data(e);
  lv_obj_t *list = objects.preset_container;
  uint32_t n = lv_obj_get_child_cnt(list);
  for (uint32_t i = 0; i < n; i++) {
    if ((int)i == presetSel) lv_obj_add_state(lv_obj_get_child(list, i), LV_STATE_CHECKED);
    else                     lv_obj_clear_state(lv_obj_get_child(list, i), LV_STATE_CHECKED);
  }
  updatePresetButtons();
}

//Empties the list and makes one button per preset
void rebuildPresetList() {
  lv_obj_t *list = objects.preset_container;
  if (!list) return;
  lv_obj_clean(list);
  for (int i = 0; i < presetCount; i++) {
    lv_obj_t *btn = lv_btn_create(list);
    lv_obj_set_size(btn, LV_PCT(100), 40);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x404040), 0);                          //normal
    lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_BLUE), LV_STATE_CHECKED); //selected
    if (i == presetSel) lv_obj_add_state(btn, LV_STATE_CHECKED);
    lv_obj_add_event_cb(btn, preset_item_cb, LV_EVENT_CLICKED, (void *)(intptr_t)i);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, presets[i].name);
    lv_obj_align(lbl, LV_ALIGN_LEFT_MID, 0, 0);
  }
  updatePresetButtons();
}

// ---- Pop-ups: a simple message, the delete confirmation, and the name keyboard ----

static void close_msgbox_cb(lv_event_t *e) {
  lv_msgbox_close_async(lv_event_get_current_target(e));
}

//A message with an OK button. With no parent, LVGL makes it modal on the top layer, above the overlay.
void showMessage(const char *title, const char *text) {
  static const char *btns[] = { "OK", "" };
  lv_obj_t *m = lv_msgbox_create(NULL, title, text, btns, false);
  lv_obj_center(m);
  lv_obj_add_event_cb(m, close_msgbox_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

void deletePreset(int i) {
  if (i < 0 || i >= presetCount) return;
  for (int k = i; k < presetCount - 1; k++) presets[k] = presets[k + 1];   //close the gap
  irisDeletePresetFile(i, presetCount);                                    //and shift the iris files to match
  presetCount--;
  presetSel = -1;
  savePresetsToFlash();
  rebuildPresetList();
}

static void delete_confirm_cb(lv_event_t *e) {
  lv_obj_t *m = lv_event_get_current_target(e);
  const char *pressed = lv_msgbox_get_active_btn_text(m);
  if (pressed && strcmp(pressed, "Delete") == 0) deletePreset(presetSel);
  lv_msgbox_close_async(m);
}

static lv_obj_t *namePopup = nullptr, *nameTextarea = nullptr;
static int renameIndex = -1;   //-1 = naming a new preset, otherwise renaming this one

static void closeNamePopup() {
  if (!namePopup) return;
  lv_obj_del_async(namePopup);   //"async": deleted after this tap is finished being handled
  namePopup = nameTextarea = nullptr;
}

static void name_keyboard_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CANCEL) { closeNamePopup(); return; }
  if (code != LV_EVENT_READY) return;

  char name[PRESET_NAME_LEN];
  strncpy(name, lv_textarea_get_text(nameTextarea), PRESET_NAME_LEN - 1);
  name[PRESET_NAME_LEN - 1] = '\0';
  if (name[0] == '\0') snprintf(name, sizeof name, "Preset %d", presetCount + 1);   //nothing typed

  if (renameIndex < 0) {                       //new preset: today's settings, under this name
    snapshotTo(presetCount);
    irisSaveToPreset(presetCount);             //and the iris poses
    strcpy(presets[presetCount].name, name);
    presetSel = presetCount;
    presetCount++;
  } else {                                     //rename only: the settings stay as they were
    strcpy(presets[renameIndex].name, name);
  }
  savePresetsToFlash();
  rebuildPresetList();
  closeNamePopup();
}

//Full-screen pop-up on the system layer, so it covers the nav bar and volume panel too
void openNamePopup(const char *startText, int rename) {
  if (namePopup) return;
  renameIndex = rename;

  namePopup = lv_obj_create(lv_layer_sys());
  lv_obj_set_size(namePopup, LV_PCT(100), LV_PCT(100));
  lv_obj_clear_flag(namePopup, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(namePopup, lv_color_hex(0x101010), 0);
  lv_obj_set_style_border_width(namePopup, 0, 0);
  lv_obj_set_style_radius(namePopup, 0, 0);
  lv_obj_set_style_pad_all(namePopup, 8, 0);

  lv_obj_t *title = lv_label_create(namePopup);
  lv_label_set_text(title, rename < 0 ? "Name your preset" : "Rename preset");
  lv_obj_set_style_text_color(title, lv_color_white(), 0);
  lv_obj_align(title, LV_ALIGN_TOP_LEFT, 0, 0);

  nameTextarea = lv_textarea_create(namePopup);
  lv_textarea_set_one_line(nameTextarea, true);
  lv_textarea_set_max_length(nameTextarea, PRESET_NAME_LEN - 1);
  lv_textarea_set_placeholder_text(nameTextarea, "Preset name");
  lv_textarea_set_text(nameTextarea, startText);
  lv_obj_set_width(nameTextarea, LV_PCT(100));
  lv_obj_align(nameTextarea, LV_ALIGN_TOP_MID, 0, 26);
  lv_obj_add_state(nameTextarea, LV_STATE_FOCUSED);   //shows the blinking cursor

  lv_obj_t *kb = lv_keyboard_create(namePopup);
  lv_obj_set_size(kb, LV_PCT(100), LV_PCT(65));
  lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_keyboard_set_textarea(kb, nameTextarea);         //key presses type into the text box
  lv_obj_add_event_cb(kb, name_keyboard_cb, LV_EVENT_ALL, NULL);
}

static void save_preset_cb(lv_event_t *e) {
  if (presetCount >= MAX_PRESETS) {
    showMessage("Presets full", "Delete a preset to make room for a new one.");
    return;
  }
  openNamePopup("", -1);
}
static void load_preset_cb(lv_event_t *e) {
  if (presetSel < 0) return;
  applyPreset(presetSel);
  Serial.printf("[PRESETS] Loaded \"%s\"\n", presets[presetSel].name);
}
static void edit_preset_cb(lv_event_t *e) {
  if (presetSel < 0) return;
  openNamePopup(presets[presetSel].name, presetSel);
}
static void delete_preset_cb(lv_event_t *e) {
  if (presetSel < 0) return;
  static const char *btns[] = { "Delete", "Cancel", "" };
  char text[64];
  snprintf(text, sizeof text, "Delete \"%s\"? This can't be undone.", presets[presetSel].name);
  lv_obj_t *m = lv_msgbox_create(NULL, "Delete preset", text, btns, false);
  lv_obj_center(m);
  lv_obj_add_event_cb(m, delete_confirm_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

//Sets up the Presets page once it exists: list layout, button callbacks, and the list itself.
//Called in setup() and on every page change, in case EEZ only builds the page when it's opened.
void presetsUIHook() {
  static bool hooked = false;
  if (hooked || !objects.preset_container) return;

  lv_obj_t *list = objects.preset_container;
  lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);    //entries stack top to bottom
  lv_obj_set_style_pad_row(list, 4, 0);
  lv_obj_set_scroll_dir(list, LV_DIR_VER);            //scrolls up and down once it's full

  if (objects.save_button)   lv_obj_add_event_cb(objects.save_button,   save_preset_cb,   LV_EVENT_CLICKED, NULL);
  if (objects.load_button)   lv_obj_add_event_cb(objects.load_button,   load_preset_cb,   LV_EVENT_CLICKED, NULL);
  if (objects.edit_button)   lv_obj_add_event_cb(objects.edit_button,   edit_preset_cb,   LV_EVENT_CLICKED, NULL);
  if (objects.delete_button) lv_obj_add_event_cb(objects.delete_button, delete_preset_cb, LV_EVENT_CLICKED, NULL);

  rebuildPresetList();   //also greys out Load, Edit and Delete, since nothing is selected yet
  hooked = true;
}

// ============================================================================
// EEZ UI to Variable Connection
// ============================================================================

extern "C" {
  // Sliders: EEZ integer variable name, and which params[] row it controls
  EEZ_PARAM(a_level, P_A_LEVEL)
  EEZ_PARAM(b_level, P_B_LEVEL)
  EEZ_PARAM(c_level, P_C_LEVEL)

  // Value labels: EEZ string variable name, and which params[] row it shows
  EEZ_LABEL(a_level_value, P_A_LEVEL)
  EEZ_LABEL(b_level_value, P_B_LEVEL)
  EEZ_LABEL(c_level_value, P_C_LEVEL)

  // Sources page sliders
  EEZ_PARAM(a_mod_index, P_A_MOD_INDEX)
  EEZ_PARAM(b_mod_index, P_B_MOD_INDEX)
  EEZ_PARAM(c_mod_index, P_C_MOD_INDEX)
  EEZ_PARAM(a_feedback,  P_A_FEEDBACK)
  EEZ_PARAM(b_feedback,  P_B_FEEDBACK)
  EEZ_PARAM(c_feedback,  P_C_FEEDBACK)

  // Sources page value labels
  EEZ_LABEL(a_mod_index_value, P_A_MOD_INDEX)
  EEZ_LABEL(b_mod_index_value, P_B_MOD_INDEX)
  EEZ_LABEL(c_mod_index_value, P_C_MOD_INDEX)
  EEZ_LABEL(a_feedback_value,  P_A_FEEDBACK)
  EEZ_LABEL(b_feedback_value,  P_B_FEEDBACK)
  EEZ_LABEL(c_feedback_value,  P_C_FEEDBACK)

  // Sources page ratio dropdowns (pair 0 = A, 1 = B, 2 = C)
  EEZ_RATIO(a_ratio, 0)
  EEZ_RATIO(b_ratio, 1)
  EEZ_RATIO(c_ratio, 2)

  //Pitch offset dropdowns
  EEZ_PITCH_OFFSET(pitch_offset_a, 0)
  EEZ_PITCH_OFFSET(pitch_offset_b, 1)
  EEZ_PITCH_OFFSET(pitch_offset_c, 2)

  // Filters page sliders
  EEZ_PARAM(global_cutoff,     P_GLOBAL_CUTOFF)

  //Global cutoff label: shows the actual frequency as scaled by sliderToCutoff()
  const char *get_var_global_cutoff_value() {
    snprintf(labelBufs[P_GLOBAL_CUTOFF], sizeof labelBufs[P_GLOBAL_CUTOFF], "%.0f",
             sliderToCutoff(params[P_GLOBAL_CUTOFF].value));
    return labelBufs[P_GLOBAL_CUTOFF];
  }

  EEZ_PARAM(global_resonance,  P_GLOBAL_RESONANCE)
  EEZ_PARAM(a_relative_cutoff, P_A_RELATIVE_CUTOFF)
  EEZ_PARAM(b_relative_cutoff, P_B_RELATIVE_CUTOFF)
  EEZ_PARAM(c_relative_cutoff, P_C_RELATIVE_CUTOFF)
  EEZ_PARAM(fe_amount,         P_FE_AMOUNT)
  EEZ_PARAM(fe_decay,          P_FE_DECAY)

  // EEZ_LABEL(global_cutoff_value,     P_GLOBAL_CUTOFF)
  EEZ_LABEL(global_resonance_value,  P_GLOBAL_RESONANCE)
  EEZ_LABEL(a_relative_cutoff_value, P_A_RELATIVE_CUTOFF)
  EEZ_LABEL(b_relative_cutoff_value, P_B_RELATIVE_CUTOFF)
  EEZ_LABEL(c_relative_cutoff_value, P_C_RELATIVE_CUTOFF)
  EEZ_LABEL(fe_amount_value,         P_FE_AMOUNT)
  EEZ_LABEL(fe_decay_value,          P_FE_DECAY)

  // Filters page type dropdowns (pair 0 = A, 1 = B, 2 = C)
  EEZ_FILTER_TYPE(a_filter_type, 0)
  EEZ_FILTER_TYPE(b_filter_type, 1)
  EEZ_FILTER_TYPE(c_filter_type, 2)

  // FX page sliders
  EEZ_PARAM(vibrato_depth, P_VIBRATO_DEPTH)
  EEZ_PARAM(vibrato_rate,  P_VIBRATO_RATE)
  EEZ_PARAM(detune,        P_DETUNE)
  EEZ_PARAM(chorus,        P_CHORUS)
  EEZ_PARAM(echo,          P_ECHO)
  EEZ_PARAM(reverb,        P_REVERB)

  // FX page value labels
  EEZ_LABEL(vibrato_depth_value, P_VIBRATO_DEPTH)
  EEZ_LABEL(vibrato_rate_value,  P_VIBRATO_RATE)
  EEZ_LABEL(detune_value,        P_DETUNE)
  EEZ_LABEL(chorus_value,        P_CHORUS)
  EEZ_LABEL(echo_value,          P_ECHO)
  EEZ_LABEL(reverb_value,        P_REVERB)

  // Pitch page: performance mode, scale and arp pattern dropdowns (positions, kept inside each list)
  int32_t get_var_performance_mode() { return performanceMode; }
  void set_var_performance_mode(int32_t v) {
    performanceMode = constrain(v, 0, 2);   //Arpeggiate, Quantized or Continuous
    Serial.printf("Performance mode = %d\n", (int)performanceMode);
    updatePitchUI();   //show this mode's controls, hide the others
  }
  int32_t get_var_scale() { return scaleSel; }
  void set_var_scale(int32_t v) {
    scaleSel = constrain(v, 0, NUM_SCALES - 1);
    Serial.printf("Scale = %s\n", SCALES[scaleSel].name);
  }
  int32_t get_var_arp_pattern() { return arpPattern; }
  void set_var_arp_pattern(int32_t v) {
    arpPattern = constrain(v, 0, NUM_ARP_PATTERNS - 1);
    arpStep = 0; //start new pattern from the first note
    Serial.printf("Arp pattern = %s\n", ARP_PATTERNS[arpPattern]);
  }

  // Pitch page: starting note and relative pitch
  int32_t get_var_starting_note() { return startingNoteRaw; }
  void set_var_starting_note(int32_t v) { startingNoteRaw = v; }
  //Starting note label: the starting note's name and octave, e.g. "C4"
  const char *get_var_starting_note_value() {
    static char buf[8];
    noteName(startingNote(), buf, sizeof buf);
    return buf;
  }
  int32_t get_var_relative_pitch() { return relativePitch; }
  void set_var_relative_pitch(int32_t v) { relativePitch = v; }

  //Relative pitch label: the pitch actually played. Frequency + "Hz" in Continuous mode,
  //note name + octave (e.g. "E4") otherwise.
  const char *get_var_relative_pitch_value() {
    if (performanceMode == PERF_CONTINUOUS) {
      snprintf(relPitchBuf, sizeof relPitchBuf, "%.1f\nHz", noteToHz(targetNote()));   //e.g. "329.6", then "Hz" below
    } else {
      noteName(nearestScaleNote(targetNote()), relPitchBuf, sizeof relPitchBuf);
    }
    return relPitchBuf;
  }

  // Pitch page: arp range slider (left knob = min, right knob = max), kept at least 1 note apart
  int32_t get_var_arp_range_min() { return arpRangeMin; }
  int32_t get_var_arp_range_max() { return arpRangeMax; }
  void set_var_arp_range_min(int32_t v) { arpRangeMin = min(v, arpRangeMax - 1); }
  void set_var_arp_range_max(int32_t v) { arpRangeMax = max(v, arpRangeMin + 1); }
  //Labels show the actual notes: starting note + each knob's offset
  const char *get_var_arp_range_min_value() { noteName(arpRangeNote(arpRangeMin), arpMinBuf, sizeof arpMinBuf); return arpMinBuf; }
  const char *get_var_arp_range_max_value() { noteName(arpRangeNote(arpRangeMax), arpMaxBuf, sizeof arpMaxBuf); return arpMaxBuf; }

  // Pitch page: arp speed slider, kept between 60 and 200 BPM
  int32_t get_var_arp_speed() { return arpSpeedBpm; }
  void set_var_arp_speed(int32_t v) { arpSpeedBpm = constrain(v, ARP_SPEED_MIN, ARP_SPEED_MAX); }
  const char *get_var_arp_speed_value() {
    snprintf(arpSpeedBuf, sizeof arpSpeedBuf, "%d", (int)arpSpeedBpm);
    return arpSpeedBuf;
  }

  //For each new slider: add a ParamId entry and a params[] row, then a pair like this:
  //EEZ_PARAM(my_slider_variable,       P_MY_PARAM)
  //EEZ_LABEL(my_slider_variable_value, P_MY_PARAM)
}

// ============================================================================
// Display and Touchscreen
// ============================================================================

ST77922 mylcd = ST77922();
ST77922_TOUCH touch_st77922;

void my_display_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  const uint16_t *src = (const uint16_t *)color_p;

  for (int ly = area->y1; ly <= area->y2; ly++) {       // ly, lx = landscape position (what LVGL drew)
    for (int lx = area->x1; lx <= area->x2; lx++) {
      uint16_t c = *src++;
#if !LV_COLOR_16_SWAP
      c = (c >> 8) | (c << 8);                           // the panel wants each pixel's bytes swapped
#endif
#if LCD_ROTATION_FLIP
      int px = (panelW - 1) - ly;                        // px, py = portrait position on the panel
      int py = lx;
#else
      int px = ly;
      int py = (panelH - 1) - lx;
#endif
      panelBuf[py * panelW + px] = c;
    }
  }

  // Only send once the whole redraw is finished: full frame, full width, the same
  // Fill_Colors(0, 0, width, height, ...) call Freenove's examples use, which the panel handles fine.
  if (lv_disp_flush_is_last(disp_drv)) {
    mylcd.Fill_Colors(0, 0, panelW, panelH, panelBuf);
  }

  lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch_st77922.Get_Touch() &&
      (touch_st77922.touch.x[0] > 0 || touch_st77922.touch.y[0] > 0)) {
    data->point.x = constrain(touch_st77922.touch.x[0], 0, screenW - 1);
    data->point.y = constrain(touch_st77922.touch.y[0], 0, screenH - 1);

    data->state = LV_INDEV_STATE_PR;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }

  // Freenove's example clears every point after reading it
  for (int i = 0; i < touch_st77922.max_points; i++) {
    touch_st77922.touch.x[i] = 0;
    touch_st77922.touch.y[i] = 0;
  }
}

// ============================================================================
// IMU: LMS6DSOX accelerometer and gyroscope information, smoothed for IRIS training
// ============================================================================
// #define IMU_ADDRESS         0x6A  //I2C has all devices on the same two wires (SDA and SCL, pins 38 and 39). So this is the IMU controller's specific "address"
// #define IMU_INTERVAL_MS     10    //Read IMU data 100 times per second
// #define TILT_SMOOTHING      0.1f  //Value from 0-1. A lower value is smoother but slower to follow
// #define ACTIVITY_SMOOTHING  0.02f //averages motion over about half a second since accelerometer data can be much more shaky

// Adafruit_LSM6DSOX sox;
// bool imuReady = false;

// float tiltX = 0;
// float tiltY = 0;
// float tiltZ = 0;

// float activity = 0;

// void readImu() {
//   sensors_event_t accel; //sensors_event_t is a struct containing int32_t of sensor_id (who did the reading), type (what kind of reading), timestamp (when it was read)
//   sensors_event_t gyro;
//   sensors_event_t temp;

//   sox.getEvent(&accel, &gyro, &temp); //writes the results directly to the location of the three variables

//   float ax = accel.acceleration.x / 9.81f;
//   float ay = accel.acceleration.y / 9.81f;
//   float az = accel.acceleration.z / 9.81f;

//   tiltX += TILT_SMOOTHING * (ax - tiltX);
//   tiltY += TILT_SMOOTHING * (ay - tiltY);
//   tiltZ += TILT_SMOOTHING * (az - tiltZ);

//   float gx = gyro.gyro.x;
//   float gy = gyro.gyro.y;
//   float gz = gyro.gyro.z;
//   float spin = sqrtf(gx * gx + gy * gy + gz * gz);
//   activity += ACTIVITY_SMOOTHING * (spin - activity);
// }


// ============================================================================
// Iris: Maps poses/motion to synth parameters.
// Teach mode: When the record button is pressed and IRIS is training
// Play mode: Whenever IRIS is not training. Allows the user to play the instrument.
// ============================================================================

#define IRIS_INPUTS       4     //tiltX, tiltY, tiltZ, activity
#define IRIS_HIDDEN       32    //allocated size of iris
#define IRIS_MAX_POSES    16    //most recordings it can hold
#define IRIS_INTERVAL_MS  20    //how often Play updates (50 times per second)
#define ACTIVITY_MAX      5.0f  //rad/s of smoothed spin that counts as full activity (IRIS compares poses by how far apart they are and since tilts lie between -1 and 1, a vigorous shake value of 10 would over power the tilts, so this caps the activity amount)

struct Learned { int param; int32_t *var; int32_t lo; int32_t hi; };
static const Learned LEARNED[] = {
  { P_A_LEVEL,           nullptr, 0,   100 },
  { P_B_LEVEL,           nullptr, 0,   100 },
  { P_C_LEVEL,           nullptr, 0,   100 },
  { P_A_MOD_INDEX,       nullptr, 0,   80  },
  { P_B_MOD_INDEX,       nullptr, 0,   80  },
  { P_C_MOD_INDEX,       nullptr, 0,   80  },
  { P_A_FEEDBACK,        nullptr, 0,   100 },
  { P_B_FEEDBACK,        nullptr, 0,   100 },
  { P_C_FEEDBACK,        nullptr, 0,   100 },
  { P_GLOBAL_CUTOFF,     nullptr, 0,   1000 },
  { P_GLOBAL_RESONANCE,  nullptr, 0,   100 },
  { P_FE_AMOUNT,         nullptr, 0,   100 },
  { P_FE_DECAY,          nullptr, 10,  2000 },
  { P_VIBRATO_DEPTH,     nullptr, 0,   100 },
  { P_VIBRATO_RATE,      nullptr, 5,   100 },
  { P_DETUNE,            nullptr, 0,   50  },
  { -1, &relativePitch, -240, 240 },                     //relative pitch (Pitch page)
  { -1, &arpSpeedBpm,   ARP_SPEED_MIN, ARP_SPEED_MAX },  //arp speed
};

static constexpr int IRIS_OUTPUTS = sizeof(LEARNED) / sizeof(LEARNED[0]);

static unsigned char irisMemory[IRIS_ARENA(IRIS_INPUTS, IRIS_HIDDEN, IRIS_OUTPUTS, IRIS_MAX_POSES)];
static iris *irisModel = nullptr;
static bool irisPlaying = false; // false = Teach, true = Play
static bool fsReady = false;     // true once LittleFS has started (needed for poses in presets)

static float recIn[IRIS_MAX_POSES][IRIS_INPUTS];
static float recOut[IRIS_MAX_POSES][IRIS_OUTPUTS];
static int32_t recCount = 0;
static Preferences irisStore;

//Working memory for iris's fast closed-form trainer (iris_train_elm), which solves in milliseconds
//where iris_train would freeze the screen for many seconds
#define IRIS_LAM0 5.1e-4f   //iris.h's recommended ridge for 32 hidden units
static unsigned char irisScratch[IRIS_ELM_SCRATCH(IRIS_HIDDEN, IRIS_OUTPUTS)];

//A learned parameter's current slider value (for training)
int32_t learnedGet(int i) {
  const Learned &L = LEARNED[i]; //& returns physical memory location in this case
  return L.var ? *L.var : params[L.param].value;
}

//Sets a learned parameter's slider position
void learnedSet(int i, int32_t v) {
  const Learned &L = LEARNED[i];
  if (L.var) {
    *L.var = v;
  } else {
    params[L.param].value = v;
    sendParam(L.param);
  }
}

void irisInputs(float *in) {
  in[0] = tiltX;
  in[1] = tiltY;
  in[2] = tiltZ;
  in[3] = constrain(activity / ACTIVITY_MAX, 0.0f, 1.0f);
}

void irisRetrain() {
  if (!irisModel) return;   //iris_init failed (see irisBegin)
  iris_clear(irisModel);
  for (int i = 0; i < recCount; i++) {
    iris_record(irisModel, recIn[i], recOut[i]);
  }

  if (recCount > 0) {
    int r = iris_train_elm(irisModel, IRIS_LAM0, irisScratch, sizeof irisScratch);
    if (r < 0) Serial.println("[IRIS] training refused");
  }
  Serial.printf("[IRIS] retrained: %d poses stored, iris has %d\n", (int)recCount, iris_count(irisModel)); //DEBUG

  //For storing iris presets (from Preferences Library)
  irisStore.begin("iris", false);
  irisStore.putInt("count", recCount);
  irisStore.putInt("outputs", IRIS_OUTPUTS);   //so a changed LEARNED[] table is detected
  irisStore.putBytes("in", recIn, sizeof recIn);
  irisStore.putBytes("out", recOut, sizeof recOut);
  irisStore.end();
}

//Sets the visible status next to the record button
void irisShowStatus() {
  char buf[24];
  snprintf(buf, sizeof buf, "%s (%d)", irisPlaying ? "PLAY" : "TEACH", (int)recCount);
  setStatus(buf);
  if (modeBtn) {
    lv_obj_set_style_bg_color(modeBtn,
      irisPlaying ? lv_palette_main(LV_PALETTE_GREEN) : lv_color_hex(0x404040), 0);
  }
}

void irisBegin() {
  irisModel = iris_init(irisMemory, sizeof irisMemory, IRIS_INPUTS, IRIS_HIDDEN, IRIS_OUTPUTS, IRIS_MAX_POSES, 1234);
  if (!irisModel) Serial.println("[IRIS] iris_init failed: check IRIS_MAX_OUT / IRIS_MAX_IN / IRIS_MAX_HID");
  irisStore.begin("iris", true);
  recCount = constrain(irisStore.getInt("count", 0), 0, IRIS_MAX_POSES);
  if (irisStore.getInt("outputs", 0) != IRIS_OUTPUTS) recCount = 0;   //made with a different table: start fresh
  if (recCount > 0) {
    irisStore.getBytes("in", recIn, sizeof recIn);
    irisStore.getBytes("out", recOut, sizeof recOut);
  }
  irisStore.end();
  irisRetrain();
  irisShowStatus();
}

void irisRecord() {
  if (irisPlaying) {
    showMessage("Playing", "Tap PLAY to switch to TEACH before recording.");
    return;
  }
  if (recCount >= IRIS_MAX_POSES) {
    showMessage("Poses full", "Press Undo to make room.");
    return;
  }
  irisInputs(recIn[recCount]);
  for (int i = 0; i < IRIS_OUTPUTS; i++) {
    const Learned &L = LEARNED[i];
    recOut[recCount][i] = (learnedGet(i) - L.lo) / (float)(L.hi - L.lo);   //slider -> 0 to 1
  }
  recCount++;
  irisRetrain();
  irisShowStatus();
}

void irisUndo() {
  if (recCount == 0) return;
  recCount--;
  if (recCount == 0) irisPlaying = false;   //nothing left to play from
  irisRetrain();
  irisShowStatus();
}

void irisToggleMode() {
  if (!irisPlaying && recCount == 0) {
    showMessage("No poses yet", "Record at least one pose before playing.");
    return;
  }
  irisPlaying = !irisPlaying;
  irisShowStatus();
}

//Play mode: iris turns the ball's pose into slider values. Called from loop() on a timer.
void irisUpdate() {
  if (!irisModel || !irisPlaying || recCount == 0) return;
  float in[IRIS_INPUTS], out[IRIS_OUTPUTS] = {0};
  irisInputs(in);
  iris_predict(irisModel, in, out);
  static unsigned long lastPrint = 0; //DEBUG: shows iris's raw predictions once a second
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    Serial.printf("[IRIS] in %.2f %.2f %.2f %.2f -> out %.2f %.2f %.2f %.2f\n",
                  in[0], in[1], in[2], in[3], out[0], out[1], out[2], out[3]);
  }
  for (int i = 0; i < IRIS_OUTPUTS; i++) {
    const Learned &L = LEARNED[i];
    if (!isfinite(out[i])) continue;                          //SAFETY: skip a prediction that isn't a real number (NaN)
    float t = constrain(out[i], 0.0f, 1.0f);
    int32_t v = L.lo + (int32_t)roundf(t * (L.hi - L.lo));   //0 to 1 -> slider
    v = constrain(v, L.lo, L.hi);                            //SAFETY: never outside the slider's range
    if (v != learnedGet(i)) learnedSet(i, v);                //only send what changed
  }
}

//Iris poses in presets: one file per preset, /iris_p0.bin, /iris_p1.bin, ...
//These do nothing if LittleFS isn't available (needs a partition scheme with SPIFFS).
void irisPresetPath(int i, char *buf, size_t len) {
  snprintf(buf, len, "/iris_p%d.bin", i);
}

void irisSaveToPreset(int i) {
  if (!fsReady) return;
  char path[20];
  irisPresetPath(i, path, sizeof path);
  File f = LittleFS.open(path, "w");
  if (!f) { Serial.printf("[IRIS] Could not write %s\n", path); return; }
  int32_t header[3] = { IRIS_INPUTS, IRIS_OUTPUTS, recCount };
  f.write((uint8_t *)header, sizeof header);
  f.write((uint8_t *)recIn,  sizeof(float) * IRIS_INPUTS  * recCount);
  f.write((uint8_t *)recOut, sizeof(float) * IRIS_OUTPUTS * recCount);
  f.close();
}

void irisLoadFromPreset(int i) {
  if (!fsReady) return;   //no files: keep the current poses
  char path[20];
  irisPresetPath(i, path, sizeof path);
  recCount = 0;   //if the file is missing or doesn't match, the preset has no poses
  File f = LittleFS.open(path, "r");
  if (f) {
    int32_t header[3];
    if (f.read((uint8_t *)header, sizeof header) == sizeof header &&
        header[0] == IRIS_INPUTS && header[1] == IRIS_OUTPUTS) {
      int32_t n = constrain(header[2], 0, IRIS_MAX_POSES);
      f.read((uint8_t *)recIn,  sizeof(float) * IRIS_INPUTS  * n);
      f.read((uint8_t *)recOut, sizeof(float) * IRIS_OUTPUTS * n);
      recCount = n;
    }
    f.close();
  }
  if (recCount == 0) irisPlaying = false;   //nothing to play from
  irisRetrain();
  irisShowStatus();
}

void irisDeletePresetFile(int removed, int countBefore) {
  if (!fsReady) return;
  char from[20], to[20];
  irisPresetPath(removed, to, sizeof to);
  LittleFS.remove(to);
  for (int k = removed + 1; k < countBefore; k++) {
    irisPresetPath(k, from, sizeof from);
    irisPresetPath(k - 1, to, sizeof to);
    LittleFS.rename(from, to);
  }
}


// ============================================================================
// Update synth state:
// ============================================================================       
bool synthPlaying = false;

void updateSynthSound(int note) {
  currentNote = note;
  updateFilterCutoffs();
  char msg[96];
  snprintf(msg, sizeof(msg), "v0n%dl1", note);  amy_add_message(msg);
  snprintf(msg, sizeof(msg), "v3n%dl1", note);  amy_add_message(msg);
  snprintf(msg, sizeof(msg), "v6n%dl1", note);  amy_add_message(msg);
  synthPlaying = true;
}

void setup() {
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0); //Makes it so the computer never waits to read Serial output
  delay(1000);

  pinMode(LCD_BL_PIN, OUTPUT);
  digitalWrite(LCD_BL_PIN, HIGH);

  mylcd.Init();
  mylcd.Set_Rotation(0);
  mylcd.Clear(0x0000);
  panelW = mylcd.Get_Width();
  panelH = mylcd.Get_Height();
  screenW = panelH;
  screenH = panelW;
  Serial.printf("Panel: %d x %d, LVGL screen: %d x %d\n", panelW, panelH, screenW, screenH);

  panelBuf = (uint16_t *)heap_caps_calloc((size_t)panelW * panelH, sizeof(uint16_t), MALLOC_CAP_SPIRAM);
  if (!panelBuf) {
    Serial.println("Could not allocate panel buffer in PSRAM (Tools > PSRAM > OPI PSRAM)");
    while (true) delay(1000);
  }

  Wire.begin(I2C_SDA, I2C_SCL, 400000);

  touch_st77922.init();
  touch_st77922.Set_Rotation(3);

  lv_init();

  static lv_disp_draw_buf_t draw_buf;
  size_t bufPixels = (size_t)screenW * DRAW_BUF_LINES;
  lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(bufPixels * sizeof(lv_color_t),
                                                    MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  if (!buf1) {
    Serial.println("[WARN] Draw buffer in PSRAM instead of internal RAM");
    buf1 = (lv_color_t *)heap_caps_malloc(bufPixels * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
  }
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, bufPixels);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenW;
  disp_drv.ver_res = screenH;
  disp_drv.flush_cb = my_display_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();

  navCreate();                // NAV BAR: page buttons along the bottom, on every page
  navUpdate(SCREEN_ID_MIX);   // ui_init() opens the first page (Mix), so highlight its button
  volumeCreate();             // VOLUME: master volume slider on the right edge, on every page
  topBarCreate();             // TOP BAR: Record, Undo and status label, on every page but Presets
  topBarUpdate(SCREEN_ID_MIX);   // start on Mix, so make sure they're showing
  hookDropdowns();            // DROPDOWNS: open lists appear above the overlay
  updatePitchUI();            // PITCH: start with the right controls showing for the starting mode
  fsReady = LittleFS.begin(true);   // FILES: for iris poses in presets (needs a partition scheme with SPIFFS)
  if (!fsReady) Serial.println("[WARN] LittleFS not available: presets won't save iris poses");
  loadPresetsFromFlash();     // PRESETS: read the saved presets...
  presetsUIHook();            // ...and fill the list (if the Presets page already exists)


  // ES8311 Codec Init
  if (es8311.begin(Wire, I2C_SDA, I2C_SCL, 400000)) {
    codecReady = true;
    es8311.setVolume(CODEC_VOLUME);
    Serial.println("[OK] ES8311 Audio Codec ready at 44.1 kHz");
  } else {
    Serial.println("[WARN] ES8311 Codec not responding; will continue synthesis.");
  }

  // LSM6DSOX Sensor Init
  Serial.println("Initializing LSM6DSOX sensor (0x6A)...");
  if (sox.begin_I2C(IMU_ADDRESS, &Wire)) {
    imuReady = true;
    sox.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
    sox.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS);
    sox.setAccelDataRate(LSM6DS_RATE_104_HZ);
    sox.setGyroDataRate(LSM6DS_RATE_104_HZ);
    Serial.println("[OK] LSM6DSOX Sensor ready (104 Hz sample rate)!");
  } else {
    Serial.println("[FAIL] Could not find LSM6DSOX at 0x6A!");
  }

  // AMY Synth Engine Init
  amy_config_t amy_config = amy_default_config();
  amy_config.features.default_synths = 0;
  amy_config.platform.multithread = 1;
  amy_config.platform.multicore = 1;
  amy_config.audio = AMY_AUDIO_IS_I2S;

  amy_config.i2s_mclk = I2S_MCK;
  amy_config.i2s_bclk = I2S_BCK;
  amy_config.i2s_lrc  = I2S_WS;
  amy_config.i2s_dout = I2S_DOUT;
  amy_config.i2s_din  = -1;

  amy_start(amy_config);
  Serial.println("[OK] AMY Engine running!");
  amyReady = true;
  sendVolume();   //start at the volume slider's position

  // amy_add_message("V0.5");               // AMY volume 1.0, ignoring the slider
  // amy_add_message("v20w0f440a1l1");    // osc 20: sine wave, 440 Hz, amplitude 1, start it

  //FM Pair A
  amy_add_message("v2w0I2a1,,0,0"); //modulator
  amy_add_message("v1w0I1a1,,0,0"); //carrier
  amy_add_message("v0w8o1O,,,,2,1"); //ALGO (the actual output osc)

  //FM Pair B
  amy_add_message("v5w0I2a1,,0,0");
  amy_add_message("v4w0I1a1,,0,0");
  amy_add_message("v3w8o1O,,,,5,4");

  //FM Pair C
  amy_add_message("v8w0I2a1,,0,0");
  amy_add_message("v7w0I1a1,,0,0");
  amy_add_message("v6w8o1O,,,,8,7");

  amy_add_message("v9w0f5a1"); //osc 9: a sine wave LFO to control vibrato, 5hz, amplitude 1
  amy_add_message("v0L9"); //each pair's ALGO osc takes osc 9 as its mod source
  amy_add_message("v3L9");
  amy_add_message("v6L9");

  sendAllParams();
  sendAllRatios();
  sendAllFilterTypes();

  irisBegin();   //IRIS: load the recordings from last time

  delay(10);
}

void loop() {
  lv_timer_handler();
  ui_tick();

  bool entering = (performanceMode != lastMode);
  if (entering) {
    if (lastMode == PERF_CONTINUOUS) {
      sendPitchBend(0);
    }
    lastMode = performanceMode;
  }

  static unsigned long lastNoteChangeTime = 0;
  if (performanceMode == PERF_ARPEGGIATE && millis() - lastNoteChangeTime >= 60000UL / arpSpeedBpm) {
    lastNoteChangeTime = millis();
    updateSynthSound(nextArpNote());
  }

  static unsigned long lastPitchCheck = 0;
  if (performanceMode != PERF_ARPEGGIATE && (entering || millis() - lastPitchCheck >= PITCH_INTERVAL_MS)) {
    lastPitchCheck = millis();
    if (performanceMode == PERF_QUANTIZED) {
      playQuantized(entering);
    } else {
      playContinuous(entering);
    }
  }

  //IMU
  static unsigned long lastImuRead = 0;
  if (imuReady && millis() - lastImuRead >= IMU_INTERVAL_MS) {
    lastImuRead = millis();
    readImu();
  }

  static unsigned long lastImuPrint = 0;
  if (imuReady && millis() - lastImuPrint >= 200) {
    lastImuPrint = millis();
    Serial.printf("tilt %.2f %.2f %.2f   activity %.2f\n", tiltX, tiltY, tiltZ, activity);
  }

  //IRIS: in Play mode, turn the ball's pose into slider values
  static unsigned long lastIris = 0;
  if (millis() - lastIris >= IRIS_INTERVAL_MS) {
    lastIris = millis();
    irisUpdate();
  }

  delay(1);
}
