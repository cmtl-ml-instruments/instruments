#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_mix_a_level_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_a_level(value);
        }
    }
}

static void event_handler_cb_mix_b_level_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_b_level(value);
        }
    }
}

static void event_handler_cb_mix_c_level_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_c_level(value);
        }
    }
}

static void event_handler_cb_sources_a_ratio_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_a_ratio(value);
        }
    }
}

static void event_handler_cb_sources_b_ratio_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_b_ratio(value);
        }
    }
}

static void event_handler_cb_sources_c_ratio_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_c_ratio(value);
        }
    }
}

static void event_handler_cb_sources_a_mod_index_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_a_mod_index(value);
        }
    }
}

static void event_handler_cb_sources_a_feedback_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_a_feedback(value);
        }
    }
}

static void event_handler_cb_sources_b_mod_index_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_b_mod_index(value);
        }
    }
}

static void event_handler_cb_sources_b_feedback_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_b_feedback(value);
        }
    }
}

static void event_handler_cb_sources_c_mod_index_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_c_mod_index(value);
        }
    }
}

static void event_handler_cb_sources_c_feedback_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_c_feedback(value);
        }
    }
}

static void event_handler_cb_filters_a_filter_type_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_a_filter_type(value);
        }
    }
}

static void event_handler_cb_filters_b_filter_type_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_b_filter_type(value);
        }
    }
}

static void event_handler_cb_filters_c_filter_type_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_c_filter_type(value);
        }
    }
}

static void event_handler_cb_filters_a_relative_cutoff_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_a_relative_cutoff(value);
        }
    }
}

static void event_handler_cb_filters_b_relative_cutoff_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_b_relative_cutoff(value);
        }
    }
}

static void event_handler_cb_filters_c_relative_cutoff_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_c_relative_cutoff(value);
        }
    }
}

static void event_handler_cb_filters_fe_amount_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_fe_amount(value);
        }
    }
}

static void event_handler_cb_filters_fe_decay_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_fe_decay(value);
        }
    }
}

static void event_handler_cb_filters_global_filter_cutoff_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_global_cutoff(value);
        }
    }
}

static void event_handler_cb_filters_global_filter_resonance_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_global_resonance(value);
        }
    }
}

static void event_handler_cb_motion___fx_vibrato_depth_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_vibrato_depth(value);
        }
    }
}

static void event_handler_cb_motion___fx_vibrato_rate_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_vibrato_rate(value);
        }
    }
}

static void event_handler_cb_motion___fx_detune_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_detune(value);
        }
    }
}

static void event_handler_cb_motion___fx_chorus_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_chorus(value);
        }
    }
}

static void event_handler_cb_motion___fx_echo_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_echo(value);
        }
    }
}

static void event_handler_cb_motion___fx_reverb_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_reverb(value);
        }
    }
}

static void event_handler_cb_pitch_performance_mode_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_performance_mode(value);
        }
    }
}

static void event_handler_cb_pitch_relative_pitch_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_relative_pitch(value);
        }
    }
}

static void event_handler_cb_pitch_scale_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_scale(value);
        }
    }
}

static void event_handler_cb_pitch_starting_note_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_starting_note(value);
        }
    }
}

static void event_handler_cb_pitch_arp_range_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_arp_range_max(value);
        }
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_left_value(ta);
            set_var_arp_range_max(value);
        }
    }
}

static void event_handler_cb_pitch_arp_pattern_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_arp_pattern(value);
        }
    }
}

//
// Screens
//

void create_screen_mix() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.mix = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 424, 56);
            lv_obj_set_size(obj, 52, 231);
        }
        {
            // a_level_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.a_level_slider = obj;
            lv_obj_set_pos(obj, 96, 91);
            lv_obj_set_size(obj, 260, 15);
            lv_obj_add_event_cb(obj, event_handler_cb_mix_a_level_slider, LV_EVENT_ALL, 0);
        }
        {
            // b_level_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.b_level_slider = obj;
            lv_obj_set_pos(obj, 96, 165);
            lv_obj_set_size(obj, 260, 15);
            lv_obj_add_event_cb(obj, event_handler_cb_mix_b_level_slider, LV_EVENT_ALL, 0);
        }
        {
            // c_level_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.c_level_slider = obj;
            lv_obj_set_pos(obj, 96, 234);
            lv_obj_set_size(obj, 260, 15);
            lv_obj_add_event_cb(obj, event_handler_cb_mix_c_level_slider, LV_EVENT_ALL, 0);
        }
        {
            // a_level_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_level_label = obj;
            lv_obj_set_pos(obj, 10, 90);
            lv_obj_set_size(obj, 60, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "A Level");
        }
        {
            // b_level_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_level_label = obj;
            lv_obj_set_pos(obj, 10, 164);
            lv_obj_set_size(obj, 60, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "B Level");
        }
        {
            // c_level_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_level_label = obj;
            lv_obj_set_pos(obj, 10, 234);
            lv_obj_set_size(obj, 60, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "C Level");
        }
        {
            // a_level_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_level_value_label = obj;
            lv_obj_set_pos(obj, 356, 90);
            lv_obj_set_size(obj, 52, 16);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // b_level_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_level_value_label = obj;
            lv_obj_set_pos(obj, 356, 164);
            lv_obj_set_size(obj, 52, 16);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // c_level_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_level_value_label = obj;
            lv_obj_set_pos(obj, 356, 234);
            lv_obj_set_size(obj, 52, 16);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_mix();
}

void tick_screen_mix() {
    {
        int32_t new_val = get_var_a_level();
        int32_t cur_val = lv_slider_get_value(objects.a_level_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.a_level_slider;
            lv_slider_set_value(objects.a_level_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_b_level();
        int32_t cur_val = lv_slider_get_value(objects.b_level_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.b_level_slider;
            lv_slider_set_value(objects.b_level_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_c_level();
        int32_t cur_val = lv_slider_get_value(objects.c_level_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.c_level_slider;
            lv_slider_set_value(objects.c_level_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_a_level_value();
        const char *cur_val = lv_label_get_text(objects.a_level_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.a_level_value_label;
            lv_label_set_text(objects.a_level_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_b_level_value();
        const char *cur_val = lv_label_get_text(objects.b_level_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.b_level_value_label;
            lv_label_set_text(objects.b_level_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_c_level_value();
        const char *cur_val = lv_label_get_text(objects.c_level_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.c_level_value_label;
            lv_label_set_text(objects.c_level_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_sources() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.sources = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // a_ratio_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.a_ratio_dropdown = obj;
            lv_obj_set_pos(obj, 38, 103);
            lv_obj_set_size(obj, 69, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "0.5\n1\n1.41\n1.5\n2\n2.5\n3\n4\n5\n6\n7\n9");
            lv_obj_add_event_cb(obj, event_handler_cb_sources_a_ratio_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // b_ratio_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.b_ratio_dropdown = obj;
            lv_obj_set_pos(obj, 39, 160);
            lv_obj_set_size(obj, 69, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "0.5\n1\n1.41\n1.5\n2\n2.5\n3\n4\n5\n6\n7\n9");
            lv_obj_add_event_cb(obj, event_handler_cb_sources_b_ratio_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // c_ratio_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.c_ratio_dropdown = obj;
            lv_obj_set_pos(obj, 38, 217);
            lv_obj_set_size(obj, 69, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "0.5\n1\n1.41\n1.5\n2\n2.5\n3\n4\n5\n6\n7\n9");
            lv_obj_add_event_cb(obj, event_handler_cb_sources_c_ratio_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // ratio_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ratio_label = obj;
            lv_obj_set_pos(obj, 38, 75);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Ratio:");
        }
        {
            // a_ratio_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_ratio_label = obj;
            lv_obj_set_pos(obj, 20, 115);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "A");
        }
        {
            // b_ratio_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_ratio_label = obj;
            lv_obj_set_pos(obj, 20, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "B");
        }
        {
            // c_ratio_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_ratio_label = obj;
            lv_obj_set_pos(obj, 20, 229);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "C");
        }
        {
            // a_mod_index_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.a_mod_index_slider = obj;
            lv_obj_set_pos(obj, 118, 105);
            lv_obj_set_size(obj, 140, 10);
            lv_slider_set_range(obj, 0, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_a_mod_index_slider, LV_EVENT_ALL, 0);
        }
        {
            // a_feedback_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.a_feedback_slider = obj;
            lv_obj_set_pos(obj, 276, 105);
            lv_obj_set_size(obj, 140, 10);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_a_feedback_slider, LV_EVENT_ALL, 0);
        }
        {
            // b_mod_index_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.b_mod_index_slider = obj;
            lv_obj_set_pos(obj, 118, 160);
            lv_obj_set_size(obj, 140, 10);
            lv_slider_set_range(obj, 0, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_b_mod_index_slider, LV_EVENT_ALL, 0);
        }
        {
            // b_feedback_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.b_feedback_slider = obj;
            lv_obj_set_pos(obj, 276, 160);
            lv_obj_set_size(obj, 140, 10);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_b_feedback_slider, LV_EVENT_ALL, 0);
        }
        {
            // c_mod_index_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.c_mod_index_slider = obj;
            lv_obj_set_pos(obj, 118, 217);
            lv_obj_set_size(obj, 140, 10);
            lv_slider_set_range(obj, 0, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_c_mod_index_slider, LV_EVENT_ALL, 0);
        }
        {
            // c_feedback_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.c_feedback_slider = obj;
            lv_obj_set_pos(obj, 276, 217);
            lv_obj_set_size(obj, 140, 10);
            lv_obj_add_event_cb(obj, event_handler_cb_sources_c_feedback_slider, LV_EVENT_ALL, 0);
        }
        {
            // mod_index_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mod_index_label = obj;
            lv_obj_set_pos(obj, 118, 75);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Mod Index:");
        }
        {
            // feedback_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.feedback_label = obj;
            lv_obj_set_pos(obj, 276, 75);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Feedback:");
        }
        {
            // a_mod_index_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_mod_index_value_label = obj;
            lv_obj_set_pos(obj, 118, 123);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // b_mod_index_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_mod_index_value_label = obj;
            lv_obj_set_pos(obj, 118, 184);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // c_mod_index_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_mod_index_value_label = obj;
            lv_obj_set_pos(obj, 118, 241);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // a_feedback_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_feedback_value_label = obj;
            lv_obj_set_pos(obj, 276, 123);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // b_feedback_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_feedback_value_label = obj;
            lv_obj_set_pos(obj, 276, 180);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // c_feedback_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_feedback_value_label = obj;
            lv_obj_set_pos(obj, 276, 241);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_sources();
}

void tick_screen_sources() {
    {
        if (!(lv_obj_get_state(objects.a_ratio_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_a_ratio();
            int32_t cur_val = lv_dropdown_get_selected(objects.a_ratio_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.a_ratio_dropdown;
                lv_dropdown_set_selected(objects.a_ratio_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.b_ratio_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_b_ratio();
            int32_t cur_val = lv_dropdown_get_selected(objects.b_ratio_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.b_ratio_dropdown;
                lv_dropdown_set_selected(objects.b_ratio_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.c_ratio_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_c_ratio();
            int32_t cur_val = lv_dropdown_get_selected(objects.c_ratio_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.c_ratio_dropdown;
                lv_dropdown_set_selected(objects.c_ratio_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        int32_t new_val = get_var_a_mod_index();
        int32_t cur_val = lv_slider_get_value(objects.a_mod_index_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.a_mod_index_slider;
            lv_slider_set_value(objects.a_mod_index_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_a_feedback();
        int32_t cur_val = lv_slider_get_value(objects.a_feedback_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.a_feedback_slider;
            lv_slider_set_value(objects.a_feedback_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_b_mod_index();
        int32_t cur_val = lv_slider_get_value(objects.b_mod_index_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.b_mod_index_slider;
            lv_slider_set_value(objects.b_mod_index_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_b_feedback();
        int32_t cur_val = lv_slider_get_value(objects.b_feedback_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.b_feedback_slider;
            lv_slider_set_value(objects.b_feedback_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_c_mod_index();
        int32_t cur_val = lv_slider_get_value(objects.c_mod_index_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.c_mod_index_slider;
            lv_slider_set_value(objects.c_mod_index_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_c_feedback();
        int32_t cur_val = lv_slider_get_value(objects.c_feedback_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.c_feedback_slider;
            lv_slider_set_value(objects.c_feedback_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_a_mod_index_value();
        const char *cur_val = lv_label_get_text(objects.a_mod_index_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.a_mod_index_value_label;
            lv_label_set_text(objects.a_mod_index_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_b_mod_index_value();
        const char *cur_val = lv_label_get_text(objects.b_mod_index_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.b_mod_index_value_label;
            lv_label_set_text(objects.b_mod_index_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_c_mod_index_value();
        const char *cur_val = lv_label_get_text(objects.c_mod_index_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.c_mod_index_value_label;
            lv_label_set_text(objects.c_mod_index_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_a_feedback_value();
        const char *cur_val = lv_label_get_text(objects.a_feedback_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.a_feedback_value_label;
            lv_label_set_text(objects.a_feedback_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_b_feedback_value();
        const char *cur_val = lv_label_get_text(objects.b_feedback_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.b_feedback_value_label;
            lv_label_set_text(objects.b_feedback_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_c_feedback_value();
        const char *cur_val = lv_label_get_text(objects.c_feedback_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.c_feedback_value_label;
            lv_label_set_text(objects.c_feedback_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_filters() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.filters = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 424, 56);
            lv_obj_set_size(obj, 52, 231);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 3, 56);
            lv_obj_set_size(obj, 274, 158);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 283, 56);
            lv_obj_set_size(obj, 137, 231);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 5, 217);
            lv_obj_set_size(obj, 274, 70);
        }
        {
            // a_filter_type_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.a_filter_type_dropdown = obj;
            lv_obj_set_pos(obj, 31, 85);
            lv_obj_set_size(obj, 105, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Lowpass\nBandpass\nHighpass");
            lv_obj_add_event_cb(obj, event_handler_cb_filters_a_filter_type_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // filter_type_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.filter_type_label = obj;
            lv_obj_set_pos(obj, 34, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Filter Type:");
        }
        {
            // a_ratio_label_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_ratio_label_1 = obj;
            lv_obj_set_pos(obj, 15, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "A");
        }
        {
            // b_ratio_label_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_ratio_label_1 = obj;
            lv_obj_set_pos(obj, 15, 137);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "B");
        }
        {
            // c_ratio_label_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_ratio_label_1 = obj;
            lv_obj_set_pos(obj, 15, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "C");
        }
        {
            // b_filter_type_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.b_filter_type_dropdown = obj;
            lv_obj_set_pos(obj, 31, 125);
            lv_obj_set_size(obj, 105, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Lowpass\nBandpass\nHighpass");
            lv_obj_add_event_cb(obj, event_handler_cb_filters_b_filter_type_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // c_filter_type_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.c_filter_type_dropdown = obj;
            lv_obj_set_pos(obj, 31, 165);
            lv_obj_set_size(obj, 105, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Lowpass\nBandpass\nHighpass");
            lv_obj_add_event_cb(obj, event_handler_cb_filters_c_filter_type_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // a_relative_cutoff_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.a_relative_cutoff_slider = obj;
            lv_obj_set_pos(obj, 144, 100);
            lv_obj_set_size(obj, 90, 10);
            lv_slider_set_range(obj, -30, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_a_relative_cutoff_slider, LV_EVENT_ALL, 0);
        }
        {
            // b_relative_cutoff_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.b_relative_cutoff_slider = obj;
            lv_obj_set_pos(obj, 145, 140);
            lv_obj_set_size(obj, 89, 10);
            lv_slider_set_range(obj, -30, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_b_relative_cutoff_slider, LV_EVENT_ALL, 0);
        }
        {
            // c_relative_cutoff_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.c_relative_cutoff_slider = obj;
            lv_obj_set_pos(obj, 145, 180);
            lv_obj_set_size(obj, 89, 10);
            lv_slider_set_range(obj, -30, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_c_relative_cutoff_slider, LV_EVENT_ALL, 0);
        }
        {
            // relative_cutoff_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.relative_cutoff_label = obj;
            lv_obj_set_pos(obj, 145, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Relative Cutoff:");
        }
        {
            // fe_amount_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.fe_amount_slider = obj;
            lv_obj_set_pos(obj, 313, 125);
            lv_obj_set_size(obj, 10, 127);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_fe_amount_slider, LV_EVENT_ALL, 0);
        }
        {
            // fe_decay_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.fe_decay_slider = obj;
            lv_obj_set_pos(obj, 379, 125);
            lv_obj_set_size(obj, 10, 127);
            lv_slider_set_range(obj, 10, 2000);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_fe_decay_slider, LV_EVENT_ALL, 0);
        }
        {
            // fe_amount_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fe_amount_label = obj;
            lv_obj_set_pos(obj, 294, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Amount");
        }
        {
            // fe_decay_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fe_decay_label = obj;
            lv_obj_set_pos(obj, 364, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Decay");
        }
        {
            // filter_envelope_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.filter_envelope_label = obj;
            lv_obj_set_pos(obj, 297, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Filter Envelope:");
        }
        {
            // global_filter_cutoff_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.global_filter_cutoff_slider = obj;
            lv_obj_set_pos(obj, 100, 241);
            lv_obj_set_size(obj, 134, 10);
            lv_slider_set_range(obj, 100, 8000);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_global_filter_cutoff_slider, LV_EVENT_ALL, 0);
        }
        {
            // filter_global_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.filter_global_label = obj;
            lv_obj_set_pos(obj, 13, 222);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Global:");
        }
        {
            // global_cutoff_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.global_cutoff_label = obj;
            lv_obj_set_pos(obj, 13, 242);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Cutoff");
        }
        {
            // global_filter_resonance_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.global_filter_resonance_slider = obj;
            lv_obj_set_pos(obj, 100, 266);
            lv_obj_set_size(obj, 134, 10);
            lv_slider_set_range(obj, 5, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_filters_global_filter_resonance_slider, LV_EVENT_ALL, 0);
        }
        {
            // global_resonance_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.global_resonance_label = obj;
            lv_obj_set_pos(obj, 13, 263);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Resonance");
        }
        {
            // a_relative_cutoff_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.a_relative_cutoff_value_label = obj;
            lv_obj_set_pos(obj, 239, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // b_relative_cutoff_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.b_relative_cutoff_value_label = obj;
            lv_obj_set_pos(obj, 240, 137);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // c_relative_cutoff_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.c_relative_cutoff_value_label = obj;
            lv_obj_set_pos(obj, 240, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // fe_amount_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fe_amount_value_label = obj;
            lv_obj_set_pos(obj, 303, 263);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // fe_decay_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fe_decay_value_label = obj;
            lv_obj_set_pos(obj, 369, 263);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // global_cutoff_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.global_cutoff_value_label = obj;
            lv_obj_set_pos(obj, 241, 238);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // global_resonance_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.global_resonance_value_label = obj;
            lv_obj_set_pos(obj, 242, 263);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_filters();
}

void tick_screen_filters() {
    {
        if (!(lv_obj_get_state(objects.a_filter_type_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_a_filter_type();
            int32_t cur_val = lv_dropdown_get_selected(objects.a_filter_type_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.a_filter_type_dropdown;
                lv_dropdown_set_selected(objects.a_filter_type_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.b_filter_type_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_b_filter_type();
            int32_t cur_val = lv_dropdown_get_selected(objects.b_filter_type_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.b_filter_type_dropdown;
                lv_dropdown_set_selected(objects.b_filter_type_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.c_filter_type_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_c_filter_type();
            int32_t cur_val = lv_dropdown_get_selected(objects.c_filter_type_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.c_filter_type_dropdown;
                lv_dropdown_set_selected(objects.c_filter_type_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        int32_t new_val = get_var_a_relative_cutoff();
        int32_t cur_val = lv_slider_get_value(objects.a_relative_cutoff_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.a_relative_cutoff_slider;
            lv_slider_set_value(objects.a_relative_cutoff_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_b_relative_cutoff();
        int32_t cur_val = lv_slider_get_value(objects.b_relative_cutoff_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.b_relative_cutoff_slider;
            lv_slider_set_value(objects.b_relative_cutoff_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_c_relative_cutoff();
        int32_t cur_val = lv_slider_get_value(objects.c_relative_cutoff_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.c_relative_cutoff_slider;
            lv_slider_set_value(objects.c_relative_cutoff_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_fe_amount();
        int32_t cur_val = lv_slider_get_value(objects.fe_amount_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.fe_amount_slider;
            lv_slider_set_value(objects.fe_amount_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_fe_decay();
        int32_t cur_val = lv_slider_get_value(objects.fe_decay_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.fe_decay_slider;
            lv_slider_set_value(objects.fe_decay_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_global_cutoff();
        int32_t cur_val = lv_slider_get_value(objects.global_filter_cutoff_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.global_filter_cutoff_slider;
            lv_slider_set_value(objects.global_filter_cutoff_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_global_resonance();
        int32_t cur_val = lv_slider_get_value(objects.global_filter_resonance_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.global_filter_resonance_slider;
            lv_slider_set_value(objects.global_filter_resonance_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_a_relative_cutoff_value();
        const char *cur_val = lv_label_get_text(objects.a_relative_cutoff_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.a_relative_cutoff_value_label;
            lv_label_set_text(objects.a_relative_cutoff_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_b_relative_cutoff_value();
        const char *cur_val = lv_label_get_text(objects.b_relative_cutoff_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.b_relative_cutoff_value_label;
            lv_label_set_text(objects.b_relative_cutoff_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_c_relative_cutoff_value();
        const char *cur_val = lv_label_get_text(objects.c_relative_cutoff_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.c_relative_cutoff_value_label;
            lv_label_set_text(objects.c_relative_cutoff_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_fe_amount_value();
        const char *cur_val = lv_label_get_text(objects.fe_amount_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.fe_amount_value_label;
            lv_label_set_text(objects.fe_amount_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_fe_decay_value();
        const char *cur_val = lv_label_get_text(objects.fe_decay_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.fe_decay_value_label;
            lv_label_set_text(objects.fe_decay_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_global_cutoff_value();
        const char *cur_val = lv_label_get_text(objects.global_cutoff_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.global_cutoff_value_label;
            lv_label_set_text(objects.global_cutoff_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_global_resonance_value();
        const char *cur_val = lv_label_get_text(objects.global_resonance_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.global_resonance_value_label;
            lv_label_set_text(objects.global_resonance_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_motion___fx() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.motion___fx = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 424, 56);
            lv_obj_set_size(obj, 52, 231);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 218, 56);
            lv_obj_set_size(obj, 195, 231);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 56);
            lv_obj_set_size(obj, 195, 231);
        }
        {
            // motion_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.motion_label = obj;
            lv_obj_set_pos(obj, 24, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Motion:");
        }
        {
            // fx_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fx_label = obj;
            lv_obj_set_pos(obj, 228, 65);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "FX:");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 25, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Vibrato");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 25, 119);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Depth");
        }
        {
            // vibrato_depth_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.vibrato_depth_slider = obj;
            lv_obj_set_pos(obj, 44, 144);
            lv_obj_set_size(obj, 10, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_vibrato_depth_slider, LV_EVENT_ALL, 0);
        }
        {
            // vibrato_depth_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vibrato_depth_value_label = obj;
            lv_obj_set_pos(obj, 33, 256);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 82, 119);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_opa(obj, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Rate");
        }
        {
            // vibrato_rate_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.vibrato_rate_slider = obj;
            lv_obj_set_pos(obj, 93, 147);
            lv_obj_set_size(obj, 10, 97);
            lv_slider_set_range(obj, 5, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_vibrato_rate_slider, LV_EVENT_ALL, 0);
        }
        {
            // vibrato_rate_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vibrato_rate_value_label = obj;
            lv_obj_set_pos(obj, 83, 256);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 138, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Detune");
        }
        {
            // detune_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.detune_slider = obj;
            lv_obj_set_pos(obj, 161, 119);
            lv_obj_set_size(obj, 10, 125);
            lv_slider_set_range(obj, 0, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_detune_slider, LV_EVENT_ALL, 0);
        }
        {
            // detune_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.detune_value_label = obj;
            lv_obj_set_pos(obj, 150, 256);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 350, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Reverb");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 228, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Chorus");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 298, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Echo");
        }
        {
            // chorus_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.chorus_slider = obj;
            lv_obj_set_pos(obj, 249, 122);
            lv_obj_set_size(obj, 10, 122);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_chorus_slider, LV_EVENT_ALL, 0);
        }
        {
            // chorus_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.chorus_value_label = obj;
            lv_obj_set_pos(obj, 238, 259);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // echo_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.echo_slider = obj;
            lv_obj_set_pos(obj, 311, 122);
            lv_obj_set_size(obj, 10, 122);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_echo_slider, LV_EVENT_ALL, 0);
        }
        {
            // echo_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.echo_value_label = obj;
            lv_obj_set_pos(obj, 300, 259);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // reverb_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.reverb_slider = obj;
            lv_obj_set_pos(obj, 371, 122);
            lv_obj_set_size(obj, 10, 122);
            lv_obj_add_event_cb(obj, event_handler_cb_motion___fx_reverb_slider, LV_EVENT_ALL, 0);
        }
        {
            // reverb_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.reverb_value_label = obj;
            lv_obj_set_pos(obj, 360, 259);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_motion___fx();
}

void tick_screen_motion___fx() {
    {
        int32_t new_val = get_var_vibrato_depth();
        int32_t cur_val = lv_slider_get_value(objects.vibrato_depth_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.vibrato_depth_slider;
            lv_slider_set_value(objects.vibrato_depth_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_vibrato_depth_value();
        const char *cur_val = lv_label_get_text(objects.vibrato_depth_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vibrato_depth_value_label;
            lv_label_set_text(objects.vibrato_depth_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_vibrato_rate();
        int32_t cur_val = lv_slider_get_value(objects.vibrato_rate_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.vibrato_rate_slider;
            lv_slider_set_value(objects.vibrato_rate_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_vibrato_rate_value();
        const char *cur_val = lv_label_get_text(objects.vibrato_rate_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vibrato_rate_value_label;
            lv_label_set_text(objects.vibrato_rate_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_detune();
        int32_t cur_val = lv_slider_get_value(objects.detune_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.detune_slider;
            lv_slider_set_value(objects.detune_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_detune_value();
        const char *cur_val = lv_label_get_text(objects.detune_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.detune_value_label;
            lv_label_set_text(objects.detune_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_chorus();
        int32_t cur_val = lv_slider_get_value(objects.chorus_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.chorus_slider;
            lv_slider_set_value(objects.chorus_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_chorus_value();
        const char *cur_val = lv_label_get_text(objects.chorus_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.chorus_value_label;
            lv_label_set_text(objects.chorus_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_echo();
        int32_t cur_val = lv_slider_get_value(objects.echo_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.echo_slider;
            lv_slider_set_value(objects.echo_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_echo_value();
        const char *cur_val = lv_label_get_text(objects.echo_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.echo_value_label;
            lv_label_set_text(objects.echo_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_reverb();
        int32_t cur_val = lv_slider_get_value(objects.reverb_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.reverb_slider;
            lv_slider_set_value(objects.reverb_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_reverb_value();
        const char *cur_val = lv_label_get_text(objects.reverb_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.reverb_value_label;
            lv_label_set_text(objects.reverb_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_pitch() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.pitch = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 424, 56);
            lv_obj_set_size(obj, 52, 231);
        }
        {
            // performance_mode_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.performance_mode_dropdown = obj;
            lv_obj_set_pos(obj, 16, 72);
            lv_obj_set_size(obj, 143, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Arppegiator\nQuantized\nContinuous");
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_performance_mode_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // performance_mode_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.performance_mode_label = obj;
            lv_obj_set_pos(obj, 16, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Performance Mode:");
        }
        {
            // relative_pitch_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.relative_pitch_slider = obj;
            lv_obj_set_pos(obj, 68, 186);
            lv_obj_set_size(obj, 309, 10);
            lv_slider_set_range(obj, -240, 240);
            lv_slider_set_mode(obj, LV_SLIDER_MODE_SYMMETRICAL);
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_relative_pitch_slider, LV_EVENT_ALL, 0);
        }
        {
            // relative_pitch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.relative_pitch_label = obj;
            lv_obj_set_pos(obj, 17, 160);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Relative Pitch:");
        }
        {
            // relative_pitch_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.relative_pitch_value_label = obj;
            lv_obj_set_pos(obj, 16, 183);
            lv_obj_set_size(obj, 52, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // scale_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.scale_dropdown = obj;
            lv_obj_set_pos(obj, 179, 72);
            lv_obj_set_size(obj, 123, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Pentatonic\nMajor\nMinor");
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_scale_dropdown, LV_EVENT_ALL, 0);
        }
        {
            // scale_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.scale_label = obj;
            lv_obj_set_pos(obj, 179, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Scale:");
        }
        {
            // starting_note_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.starting_note_slider = obj;
            lv_obj_set_pos(obj, 69, 142);
            lv_obj_set_size(obj, 308, 10);
            lv_slider_set_range(obj, 36, 84);
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_starting_note_slider, LV_EVENT_ALL, 0);
        }
        {
            // starting_note_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.starting_note_label = obj;
            lv_obj_set_pos(obj, 17, 116);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Starting Note:");
        }
        {
            // starting_note_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.starting_note_value_label = obj;
            lv_obj_set_pos(obj, 16, 139);
            lv_obj_set_size(obj, 52, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // arp_range_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.arp_range_slider = obj;
            lv_obj_set_pos(obj, 68, 186);
            lv_obj_set_size(obj, 309, 10);
            lv_slider_set_range(obj, -24, 24);
            lv_slider_set_mode(obj, LV_SLIDER_MODE_RANGE);
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_arp_range_slider, LV_EVENT_ALL, 0);
        }
        {
            // arp_range_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.arp_range_label = obj;
            lv_obj_set_pos(obj, 17, 160);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Arp Range:");
        }
        {
            // arp_range_min_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.arp_range_min_value_label = obj;
            lv_obj_set_pos(obj, 16, 183);
            lv_obj_set_size(obj, 41, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // arp_range_max_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.arp_range_max_value_label = obj;
            lv_obj_set_pos(obj, 388, 183);
            lv_obj_set_size(obj, 34, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            // arp_pattern_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.arp_pattern_label = obj;
            lv_obj_set_pos(obj, 16, 213);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Arp Pattern:");
        }
        {
            // arp_pattern_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.arp_pattern_dropdown = obj;
            lv_obj_set_pos(obj, 16, 229);
            lv_obj_set_size(obj, 143, LV_SIZE_CONTENT);
            lv_dropdown_set_options_static(obj, "Up\nDown\nUp & Down\nDown & Up\nRandom\nRandom Walk\nConverge\nThumb");
            lv_obj_add_event_cb(obj, event_handler_cb_pitch_arp_pattern_dropdown, LV_EVENT_ALL, 0);
        }
    }
    
    tick_screen_pitch();
}

void tick_screen_pitch() {
    {
        if (!(lv_obj_get_state(objects.performance_mode_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_performance_mode();
            int32_t cur_val = lv_dropdown_get_selected(objects.performance_mode_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.performance_mode_dropdown;
                lv_dropdown_set_selected(objects.performance_mode_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        int32_t new_val = get_var_relative_pitch();
        int32_t cur_val = lv_slider_get_value(objects.relative_pitch_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.relative_pitch_slider;
            lv_slider_set_value(objects.relative_pitch_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_relative_pitch_value();
        const char *cur_val = lv_label_get_text(objects.relative_pitch_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.relative_pitch_value_label;
            lv_label_set_text(objects.relative_pitch_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.scale_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_scale();
            int32_t cur_val = lv_dropdown_get_selected(objects.scale_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.scale_dropdown;
                lv_dropdown_set_selected(objects.scale_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        int32_t new_val = get_var_starting_note();
        int32_t cur_val = lv_slider_get_value(objects.starting_note_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.starting_note_slider;
            lv_slider_set_value(objects.starting_note_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_starting_note_value();
        const char *cur_val = lv_label_get_text(objects.starting_note_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.starting_note_value_label;
            lv_label_set_text(objects.starting_note_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_arp_range_max();
        int32_t cur_val = lv_slider_get_value(objects.arp_range_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.arp_range_slider;
            lv_slider_set_value(objects.arp_range_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_arp_range_min();
        int32_t cur_val = lv_slider_get_left_value(objects.arp_range_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.arp_range_slider;
            lv_slider_set_left_value(objects.arp_range_slider, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_arp_range_min_value();
        const char *cur_val = lv_label_get_text(objects.arp_range_min_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.arp_range_min_value_label;
            lv_label_set_text(objects.arp_range_min_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_arp_range_max_value();
        const char *cur_val = lv_label_get_text(objects.arp_range_max_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.arp_range_max_value_label;
            lv_label_set_text(objects.arp_range_max_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.arp_pattern_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_arp_pattern();
            int32_t cur_val = lv_dropdown_get_selected(objects.arp_pattern_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.arp_pattern_dropdown;
                lv_dropdown_set_selected(objects.arp_pattern_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_presets() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.presets = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 424, 56);
            lv_obj_set_size(obj, 52, 231);
        }
        {
            // save_button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.save_button = obj;
            lv_obj_set_pos(obj, 13, 15);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // save_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.save_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Save");
                }
            }
        }
        {
            // delete_button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.delete_button = obj;
            lv_obj_set_pos(obj, 316, 15);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // delete_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.delete_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Delete");
                }
            }
        }
        {
            // edit_button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.edit_button = obj;
            lv_obj_set_pos(obj, 215, 15);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x1ab900), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // edit_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.edit_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Edit");
                }
            }
        }
        {
            // load_button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.load_button = obj;
            lv_obj_set_pos(obj, 114, 15);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // load_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.load_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Load");
                }
            }
        }
        {
            // preset_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.preset_container = obj;
            lv_obj_set_pos(obj, 13, 69);
            lv_obj_set_size(obj, 403, 215);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    lv_obj_set_pos(obj, -3, 106);
                    lv_obj_set_size(obj, 403, 99);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    lv_obj_set_pos(obj, -2, -3);
                    lv_obj_set_size(obj, 402, 215);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                }
            }
        }
    }
    
    tick_screen_presets();
}

void tick_screen_presets() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_mix,
    tick_screen_sources,
    tick_screen_filters,
    tick_screen_motion___fx,
    tick_screen_pitch,
    tick_screen_presets,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 6) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_mix();
    create_screen_sources();
    create_screen_filters();
    create_screen_motion___fx();
    create_screen_pitch();
    create_screen_presets();
}