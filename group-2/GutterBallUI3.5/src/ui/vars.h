#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_A_LEVEL = 0,
    FLOW_GLOBAL_VARIABLE_A_LEVEL_VALUE = 1,
    FLOW_GLOBAL_VARIABLE_B_LEVEL = 2,
    FLOW_GLOBAL_VARIABLE_B_LEVEL_VALUE = 3,
    FLOW_GLOBAL_VARIABLE_C_LEVEL = 4,
    FLOW_GLOBAL_VARIABLE_C_LEVEL_VALUE = 5,
    FLOW_GLOBAL_VARIABLE_A_RATIO = 6,
    FLOW_GLOBAL_VARIABLE_B_RATIO = 7,
    FLOW_GLOBAL_VARIABLE_C_RATIO = 8,
    FLOW_GLOBAL_VARIABLE_A_MOD_INDEX = 9,
    FLOW_GLOBAL_VARIABLE_B_MOD_INDEX = 10,
    FLOW_GLOBAL_VARIABLE_C_MOD_INDEX = 11,
    FLOW_GLOBAL_VARIABLE_A_FEEDBACK = 12,
    FLOW_GLOBAL_VARIABLE_B_FEEDBACK = 13,
    FLOW_GLOBAL_VARIABLE_C_FEEDBACK = 14,
    FLOW_GLOBAL_VARIABLE_A_MOD_INDEX_VALUE = 15,
    FLOW_GLOBAL_VARIABLE_B_MOD_INDEX_VALUE = 16,
    FLOW_GLOBAL_VARIABLE_C_MOD_INDEX_VALUE = 17,
    FLOW_GLOBAL_VARIABLE_A_FEEDBACK_VALUE = 18,
    FLOW_GLOBAL_VARIABLE_B_FEEDBACK_VALUE = 19,
    FLOW_GLOBAL_VARIABLE_C_FEEDBACK_VALUE = 20,
    FLOW_GLOBAL_VARIABLE_A_FILTER_TYPE = 21,
    FLOW_GLOBAL_VARIABLE_B_FILTER_TYPE = 22,
    FLOW_GLOBAL_VARIABLE_C_FILTER_TYPE = 23,
    FLOW_GLOBAL_VARIABLE_A_RELATIVE_CUTOFF = 24,
    FLOW_GLOBAL_VARIABLE_B_RELATIVE_CUTOFF = 25,
    FLOW_GLOBAL_VARIABLE_C_RELATIVE_CUTOFF = 26,
    FLOW_GLOBAL_VARIABLE_FE_AMOUNT = 27,
    FLOW_GLOBAL_VARIABLE_FE_DECAY = 28,
    FLOW_GLOBAL_VARIABLE_GLOBAL_CUTOFF = 29,
    FLOW_GLOBAL_VARIABLE_GLOBAL_RESONANCE = 30,
    FLOW_GLOBAL_VARIABLE_A_RELATIVE_CUTOFF_VALUE = 31,
    FLOW_GLOBAL_VARIABLE_B_RELATIVE_CUTOFF_VALUE = 32,
    FLOW_GLOBAL_VARIABLE_C_RELATIVE_CUTOFF_VALUE = 33,
    FLOW_GLOBAL_VARIABLE_FE_AMOUNT_VALUE = 34,
    FLOW_GLOBAL_VARIABLE_FE_DECAY_VALUE = 35,
    FLOW_GLOBAL_VARIABLE_GLOBAL_CUTOFF_VALUE = 36,
    FLOW_GLOBAL_VARIABLE_GLOBAL_RESONANCE_VALUE = 37,
    FLOW_GLOBAL_VARIABLE_VIBRATO_DEPTH = 38,
    FLOW_GLOBAL_VARIABLE_VIBRATO_RATE = 39,
    FLOW_GLOBAL_VARIABLE_DETUNE = 40,
    FLOW_GLOBAL_VARIABLE_CHORUS = 41,
    FLOW_GLOBAL_VARIABLE_ECHO = 42,
    FLOW_GLOBAL_VARIABLE_REVERB = 43,
    FLOW_GLOBAL_VARIABLE_VIBRATO_DEPTH_VALUE = 44,
    FLOW_GLOBAL_VARIABLE_VIBRATO_RATE_VALUE = 45,
    FLOW_GLOBAL_VARIABLE_DETUNE_VALUE = 46,
    FLOW_GLOBAL_VARIABLE_CHORUS_VALUE = 47,
    FLOW_GLOBAL_VARIABLE_ECHO_VALUE = 48,
    FLOW_GLOBAL_VARIABLE_REVERB_VALUE = 49,
    FLOW_GLOBAL_VARIABLE_PERFORMANCE_MODE = 50,
    FLOW_GLOBAL_VARIABLE_RELATIVE_PITCH = 51,
    FLOW_GLOBAL_VARIABLE_RELATIVE_PITCH_VALUE = 52,
    FLOW_GLOBAL_VARIABLE_SCALE = 53,
    FLOW_GLOBAL_VARIABLE_STARTING_NOTE = 54,
    FLOW_GLOBAL_VARIABLE_ARP_RANGE_MIN = 55,
    FLOW_GLOBAL_VARIABLE_ARP_RANGE_MIN_VALUE = 56,
    FLOW_GLOBAL_VARIABLE_ARP_RANGE_MAX = 57,
    FLOW_GLOBAL_VARIABLE_ARP_RANGE_MAX_VALUE = 58,
    FLOW_GLOBAL_VARIABLE_ARP_PATTERN = 59,
    FLOW_GLOBAL_VARIABLE_STARTING_NOTE_VALUE = 60
};

// Native global variables

extern int32_t get_var_a_level();
extern void set_var_a_level(int32_t value);
extern const char *get_var_a_level_value();
extern void set_var_a_level_value(const char *value);
extern int32_t get_var_b_level();
extern void set_var_b_level(int32_t value);
extern const char *get_var_b_level_value();
extern void set_var_b_level_value(const char *value);
extern int32_t get_var_c_level();
extern void set_var_c_level(int32_t value);
extern const char *get_var_c_level_value();
extern void set_var_c_level_value(const char *value);
extern int32_t get_var_a_ratio();
extern void set_var_a_ratio(int32_t value);
extern int32_t get_var_b_ratio();
extern void set_var_b_ratio(int32_t value);
extern int32_t get_var_c_ratio();
extern void set_var_c_ratio(int32_t value);
extern int32_t get_var_a_mod_index();
extern void set_var_a_mod_index(int32_t value);
extern int32_t get_var_b_mod_index();
extern void set_var_b_mod_index(int32_t value);
extern int32_t get_var_c_mod_index();
extern void set_var_c_mod_index(int32_t value);
extern int32_t get_var_a_feedback();
extern void set_var_a_feedback(int32_t value);
extern int32_t get_var_b_feedback();
extern void set_var_b_feedback(int32_t value);
extern int32_t get_var_c_feedback();
extern void set_var_c_feedback(int32_t value);
extern const char *get_var_a_mod_index_value();
extern void set_var_a_mod_index_value(const char *value);
extern const char *get_var_b_mod_index_value();
extern void set_var_b_mod_index_value(const char *value);
extern const char *get_var_c_mod_index_value();
extern void set_var_c_mod_index_value(const char *value);
extern const char *get_var_a_feedback_value();
extern void set_var_a_feedback_value(const char *value);
extern const char *get_var_b_feedback_value();
extern void set_var_b_feedback_value(const char *value);
extern const char *get_var_c_feedback_value();
extern void set_var_c_feedback_value(const char *value);
extern int32_t get_var_a_filter_type();
extern void set_var_a_filter_type(int32_t value);
extern int32_t get_var_b_filter_type();
extern void set_var_b_filter_type(int32_t value);
extern int32_t get_var_c_filter_type();
extern void set_var_c_filter_type(int32_t value);
extern int32_t get_var_a_relative_cutoff();
extern void set_var_a_relative_cutoff(int32_t value);
extern int32_t get_var_b_relative_cutoff();
extern void set_var_b_relative_cutoff(int32_t value);
extern int32_t get_var_c_relative_cutoff();
extern void set_var_c_relative_cutoff(int32_t value);
extern int32_t get_var_fe_amount();
extern void set_var_fe_amount(int32_t value);
extern int32_t get_var_fe_decay();
extern void set_var_fe_decay(int32_t value);
extern int32_t get_var_global_cutoff();
extern void set_var_global_cutoff(int32_t value);
extern int32_t get_var_global_resonance();
extern void set_var_global_resonance(int32_t value);
extern const char *get_var_a_relative_cutoff_value();
extern void set_var_a_relative_cutoff_value(const char *value);
extern const char *get_var_b_relative_cutoff_value();
extern void set_var_b_relative_cutoff_value(const char *value);
extern const char *get_var_c_relative_cutoff_value();
extern void set_var_c_relative_cutoff_value(const char *value);
extern const char *get_var_fe_amount_value();
extern void set_var_fe_amount_value(const char *value);
extern const char *get_var_fe_decay_value();
extern void set_var_fe_decay_value(const char *value);
extern const char *get_var_global_cutoff_value();
extern void set_var_global_cutoff_value(const char *value);
extern const char *get_var_global_resonance_value();
extern void set_var_global_resonance_value(const char *value);
extern int32_t get_var_vibrato_depth();
extern void set_var_vibrato_depth(int32_t value);
extern int32_t get_var_vibrato_rate();
extern void set_var_vibrato_rate(int32_t value);
extern int32_t get_var_detune();
extern void set_var_detune(int32_t value);
extern int32_t get_var_chorus();
extern void set_var_chorus(int32_t value);
extern int32_t get_var_echo();
extern void set_var_echo(int32_t value);
extern int32_t get_var_reverb();
extern void set_var_reverb(int32_t value);
extern const char *get_var_vibrato_depth_value();
extern void set_var_vibrato_depth_value(const char *value);
extern const char *get_var_vibrato_rate_value();
extern void set_var_vibrato_rate_value(const char *value);
extern const char *get_var_detune_value();
extern void set_var_detune_value(const char *value);
extern const char *get_var_chorus_value();
extern void set_var_chorus_value(const char *value);
extern const char *get_var_echo_value();
extern void set_var_echo_value(const char *value);
extern const char *get_var_reverb_value();
extern void set_var_reverb_value(const char *value);
extern int32_t get_var_performance_mode();
extern void set_var_performance_mode(int32_t value);
extern int32_t get_var_relative_pitch();
extern void set_var_relative_pitch(int32_t value);
extern const char *get_var_relative_pitch_value();
extern void set_var_relative_pitch_value(const char *value);
extern int32_t get_var_scale();
extern void set_var_scale(int32_t value);
extern int32_t get_var_starting_note();
extern void set_var_starting_note(int32_t value);
extern int32_t get_var_arp_range_min();
extern void set_var_arp_range_min(int32_t value);
extern const char *get_var_arp_range_min_value();
extern void set_var_arp_range_min_value(const char *value);
extern int32_t get_var_arp_range_max();
extern void set_var_arp_range_max(int32_t value);
extern const char *get_var_arp_range_max_value();
extern void set_var_arp_range_max_value(const char *value);
extern int32_t get_var_arp_pattern();
extern void set_var_arp_pattern(int32_t value);
extern const char *get_var_starting_note_value();
extern void set_var_starting_note_value(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/