#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MIX = 1,
    SCREEN_ID_SOURCES = 2,
    SCREEN_ID_FILTERS = 3,
    SCREEN_ID_MOTION___FX = 4,
    SCREEN_ID_PITCH = 5,
    SCREEN_ID_PRESETS = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *mix;
    lv_obj_t *sources;
    lv_obj_t *filters;
    lv_obj_t *motion___fx;
    lv_obj_t *pitch;
    lv_obj_t *presets;
    lv_obj_t *a_level_slider;
    lv_obj_t *b_level_slider;
    lv_obj_t *c_level_slider;
    lv_obj_t *a_level_label;
    lv_obj_t *b_level_label;
    lv_obj_t *c_level_label;
    lv_obj_t *a_level_value_label;
    lv_obj_t *b_level_value_label;
    lv_obj_t *c_level_value_label;
    lv_obj_t *a_ratio_dropdown;
    lv_obj_t *b_ratio_dropdown;
    lv_obj_t *c_ratio_dropdown;
    lv_obj_t *ratio_label;
    lv_obj_t *a_ratio_label;
    lv_obj_t *b_ratio_label;
    lv_obj_t *c_ratio_label;
    lv_obj_t *a_mod_index_slider;
    lv_obj_t *a_feedback_slider;
    lv_obj_t *b_mod_index_slider;
    lv_obj_t *b_feedback_slider;
    lv_obj_t *c_mod_index_slider;
    lv_obj_t *c_feedback_slider;
    lv_obj_t *mod_index_label;
    lv_obj_t *feedback_label;
    lv_obj_t *a_mod_index_value_label;
    lv_obj_t *b_mod_index_value_label;
    lv_obj_t *c_mod_index_value_label;
    lv_obj_t *a_feedback_value_label;
    lv_obj_t *b_feedback_value_label;
    lv_obj_t *c_feedback_value_label;
    lv_obj_t *a_filter_type_dropdown;
    lv_obj_t *filter_type_label;
    lv_obj_t *a_ratio_label_1;
    lv_obj_t *b_ratio_label_1;
    lv_obj_t *c_ratio_label_1;
    lv_obj_t *b_filter_type_dropdown;
    lv_obj_t *c_filter_type_dropdown;
    lv_obj_t *a_relative_cutoff_slider;
    lv_obj_t *b_relative_cutoff_slider;
    lv_obj_t *c_relative_cutoff_slider;
    lv_obj_t *relative_cutoff_label;
    lv_obj_t *fe_amount_slider;
    lv_obj_t *fe_decay_slider;
    lv_obj_t *fe_amount_label;
    lv_obj_t *fe_decay_label;
    lv_obj_t *filter_envelope_label;
    lv_obj_t *global_filter_cutoff_slider;
    lv_obj_t *filter_global_label;
    lv_obj_t *global_cutoff_label;
    lv_obj_t *global_filter_resonance_slider;
    lv_obj_t *global_resonance_label;
    lv_obj_t *a_relative_cutoff_value_label;
    lv_obj_t *b_relative_cutoff_value_label;
    lv_obj_t *c_relative_cutoff_value_label;
    lv_obj_t *fe_amount_value_label;
    lv_obj_t *fe_decay_value_label;
    lv_obj_t *global_cutoff_value_label;
    lv_obj_t *global_resonance_value_label;
    lv_obj_t *motion_label;
    lv_obj_t *fx_label;
    lv_obj_t *vibrato_depth_slider;
    lv_obj_t *vibrato_depth_value_label;
    lv_obj_t *vibrato_rate_slider;
    lv_obj_t *vibrato_rate_value_label;
    lv_obj_t *detune_slider;
    lv_obj_t *detune_value_label;
    lv_obj_t *chorus_slider;
    lv_obj_t *chorus_value_label;
    lv_obj_t *echo_slider;
    lv_obj_t *echo_value_label;
    lv_obj_t *reverb_slider;
    lv_obj_t *reverb_value_label;
    lv_obj_t *performance_mode_dropdown;
    lv_obj_t *performance_mode_label;
    lv_obj_t *relative_pitch_slider;
    lv_obj_t *relative_pitch_label;
    lv_obj_t *relative_pitch_value_label;
    lv_obj_t *scale_dropdown;
    lv_obj_t *scale_label;
    lv_obj_t *starting_note_slider;
    lv_obj_t *starting_note_label;
    lv_obj_t *starting_note_value_label;
    lv_obj_t *arp_range_slider;
    lv_obj_t *arp_range_label;
    lv_obj_t *arp_range_min_value_label;
    lv_obj_t *arp_range_max_value_label;
    lv_obj_t *arp_pattern_label;
    lv_obj_t *arp_pattern_dropdown;
    lv_obj_t *save_button;
    lv_obj_t *save_button_label;
    lv_obj_t *delete_button;
    lv_obj_t *delete_button_label;
    lv_obj_t *edit_button;
    lv_obj_t *edit_button_label;
    lv_obj_t *load_button;
    lv_obj_t *load_button_label;
    lv_obj_t *preset_container;
} objects_t;

extern objects_t objects;

void create_screen_mix();
void tick_screen_mix();

void create_screen_sources();
void tick_screen_sources();

void create_screen_filters();
void tick_screen_filters();

void create_screen_motion___fx();
void tick_screen_motion___fx();

void create_screen_pitch();
void tick_screen_pitch();

void create_screen_presets();
void tick_screen_presets();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/