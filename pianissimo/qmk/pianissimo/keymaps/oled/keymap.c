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

#define DEFAULT_OCTAVE 4

uint8_t menu_pos = 0;
uint8_t menu_items = 2;

const uint8_t octave_hue[] = {
    0,
    83,
    126,
    167,
    191,
    0,
    12,
    33
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _KB,
    _AD,
    _MD
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  KC_KNOB = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keyboard layer
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
    [_KB] = LAYOUT(
                                                              MO(_AD),
             KC_NO,  KC_NO,            KC_NO,   KC_NO,   KC_NO,
        KC_C,   KC_D,    KC_E,    KC_F,    KC_G,    KC_A,    KC_B
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
    ),

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
                                                              KC_KNOB,
            MI_Cs_1, MI_Ds_1,          MI_Fs_1, MI_Gs_1, MI_As_1,
        MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,  MI_G_1,  MI_A_1,  RESET
    )
};

#ifdef OLED_DRIVER_ENABLE
void render_num(uint8_t num, uint8_t pos_x, uint8_t pos_y, bool invert) {
    static const char PROGMEM nums[16][2][3] = {
        {{0x88, 0x89, 0}, {0xa8, 0xa9, 0}},
        {{0x8a, 0x8b, 0}, {0xaa, 0xab, 0}},
        {{0x8c, 0x8d, 0}, {0xac, 0xad, 0}},
        {{0x8e, 0x8f, 0}, {0xae, 0xaf, 0}},
        {{0x90, 0x91, 0}, {0xb0, 0xb1, 0}},
        {{0x92, 0x93, 0}, {0xb2, 0xb3, 0}},
        {{0x94, 0x95, 0}, {0xb4, 0xb5, 0}},
        {{0x96, 0x97, 0}, {0xb6, 0xb7, 0}},
        {{0x98, 0x99, 0}, {0xb8, 0xb9, 0}},
        {{0x9a, 0x9b, 0}, {0xba, 0xbb, 0}},
        {{0x80, 0x81, 0}, {0xa0, 0xa1, 0}},
        {{0x82, 0x83, 0}, {0xa2, 0xa3, 0}},
        {{0x84, 0x85, 0}, {0xa4, 0xa5, 0}},
        {{0x86, 0x87, 0}, {0xa6, 0xa7, 0}},
        {{0x9C, 0x9D, 0}, {0xbc, 0xbd, 0}},
        {{0x9D, 0x9D, 0}, {0xbd, 0xbd, 0}},
    };

    oled_set_cursor(pos_x, pos_y);
    oled_write_P(nums[num][0], invert);
    oled_set_cursor(pos_x, pos_y + 1);
    oled_write_P(nums[num][1], invert);
}

void render_big_num(uint8_t num, uint8_t pos_x, uint8_t pos_y) {
    if (num > 99) {
        render_num(num / 100, pos_x, pos_y, false);
    } else {
        render_num(15, pos_x, pos_y, false);
    }

    if (num > 9) {
        render_num(num % 100 / 10, pos_x + 2, pos_y, false);
    } else {
        render_num(15, pos_x + 2, pos_y, false);
    }

    render_num(num % 10, pos_x + 4, pos_y, false);
}

void oled_task_user(void) {
  //oled_render_logo();
}
#endif

bool set_octave_led(void) {
    rgblight_sethsv_noeeprom(octave_hue[midi_config.octave], 255, 255);
    return true;
}

bool change_octave(short step) {
    if (step > 0 && midi_config.octave < 7)
        midi_config.octave++;
    else if (step < 0 && midi_config.octave > 1)
        midi_config.octave--;
    set_octave_led();
    render_big_num(midi_config.octave - 1, 3, 0);
    return true;
}

bool change_velocity(short step) {
    if (step > 0 && midi_config.velocity < 127)
        midi_config.velocity++;
    else if (step < 0 && midi_config.velocity > 0)
        midi_config.velocity--;
    render_big_num(midi_config.velocity, 15, 0);
    return true;
}

bool change_modulation(short step) {
    if (step > 0 && midi_config.modulation_interval  < 127)
        midi_config.modulation_interval ++;
    else if (step < 0 && midi_config.modulation_interval  > 0)
        midi_config.modulation_interval --;
    render_big_num(midi_config.modulation_interval , 15, 0);
    return true;
}

bool change_layer(short step) {
    if (IS_LAYER_ON(_MD)) {
        layer_off(_MD);
        render_big_num(0, 15, 0);
    } else {
        layer_on(_MD);
        render_big_num(1, 15, 0);
    }
    return true;
}

const rgblight_segment_t PROGMEM my_keyboard_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_keyboard_layer,
    my_adjust_layer
);

void oled_render_logo(void) {
  static const char PROGMEM pnssm_logo[] = {
    0x80, 0x80, 0x80, 0x83, 0x84, 0x80, 0x86, 0x87, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x93, 0x80,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0x80,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0x80,
    0x80, 0x80, 0x80, 0x81, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x85, 0x89, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8a,
    0
  };
  oled_write_P(pnssm_logo, false);
}

void render_menu(void) {
    render_num(10, 0, 0, menu_pos == 0);
    render_num(14, 2, 0, false);
    render_num(11, 11, 0, menu_pos == 1);
    render_num(14, 13, 0, false);
    //render_num(12, 0, 2, menu_pos == 2);
    //render_num(14, 2, 2, false);
    //render_num(13, 11, 2, menu_pos == 3);
    //render_num(14, 13, 2, false);
}

void render_numbers(void) {
    render_big_num(midi_config.octave - 1, 3, 0);
    render_big_num(1, 15, 0);
    // render_big_num(midi_config.modulation_interval , 3, 2);
    // RENDER LAYER
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    midi_config.octave = DEFAULT_OCTAVE;

    layer_on(_MD);

    render_menu();
    render_numbers();

    rgblight_sethsv_noeeprom(octave_hue[midi_config.octave], 255, 255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _KB));
    rgblight_set_layer_state(1, layer_state_cmp(state, _AD));
    set_octave_led();
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_KNOB:
            if (record->event.pressed) {
                menu_pos++;
                if (menu_pos >= menu_items)
                    menu_pos = 0;
                render_menu();
            }
            return true;
        default:
            return true;
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        switch (menu_pos) {
            case 0:
                change_octave(1);
                break;
            case 1:
                change_layer(1);
                break;
            case 2:
                //change_layer(1);
                break;
            case 3:
                //change_layer(1);
                break;
        }
    } else {
        switch (menu_pos) {
            case 0:
                change_octave(-1);
                break;
            case 1:
                change_layer(-1);
                break;
            case 2:
                //change_layer(-1);
                break;
            case 3:
                //change_layer(-1);
                break;
        }
    }
}
