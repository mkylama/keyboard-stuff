/* Copyright 2021 MigiBacon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define LAYER_COUNT 5
#define DEFAULT_OCTAVE 3

const uint8_t octave_hue[] = {
    0,
    126,
    167,
    191,
    0,
    12,
    33,
    83
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MD,
    _AD
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  TEST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Midi
        ┌───────────────────────────────┐
        │                         ┌───┐ │
        │                         │Fn │ │
        │   ┌───┬───┐   ┌───┬───┬─┴─┬─┘ │
        │   │ 1 │ 2 │   │ 3 │ 4 │ 5 │   │
        │ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐ │
        │ │ C │ D │ E │ F │ G │ A │ B │ │
        │ └───┴───┴───┴───┴───┴───┴───┘ │
        └───────────────────────────────┘
    */
    [_MD] = LAYOUT(
                                                              TG(_AD),
            MI_Cs_1, MI_Ds_1,          MI_Fs_1, MI_Gs_1, MI_As_1,
        MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1
    ),
    /* Adjust layer
        ┌───────────────────────────────┐
        │                         ┌───┐ │
        │                         │   │ │
        │   ┌───┬───┐   ┌───┬───┬─┴─┬─┘ │
        │   │F2 │F4 │   │F7 │F9 │F11│   │
        │ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐ │
        │ │F1 │F3 │F5 │F6 │F8 │F10│RST│ │
        │ └───┴───┴───┴───┴───┴───┴───┘ │
        └───────────────────────────────┘
    */
    [_AD] = LAYOUT(
                                                              _______,
             KC_NO,  KC_NO,            KC_NO,   KC_NO,   KC_NO,
        KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET
    )
};

bool set_octave_led(void) {
    rgblight_sethsv_noeeprom(octave_hue[midi_config.octave], 255, 255);
    return true;
}

bool next_octave(void) {
    if (midi_config.octave < 7)
        midi_config.octave++;
    set_octave_led();
    return true;
}

bool prev_octave(void) {
    if (midi_config.octave > 1)
        midi_config.octave--;
    set_octave_led();
    return true;
}

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    midi_config.octave = DEFAULT_OCTAVE;
    rgblight_sethsv_noeeprom(octave_hue[midi_config.octave], 255, 255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _AD));
    set_octave_led();
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        next_octave();
    } else {
        prev_octave();
    }
}
