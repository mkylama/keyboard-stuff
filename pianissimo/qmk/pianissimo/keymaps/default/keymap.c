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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    TEST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
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
    [_BASE] = LAYOUT(
                                                              TG(_FN),
            KC_1,    KC_2,             KC_3,    KC_4,    KC_5,
        KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_A,    KC_B
    ),
    /* Base Layer
        ┌───────────────────────────────┐
        │                         ┌───┐ │
        │                         │   │ │
        │   ┌───┬───┐   ┌───┬───┬─┴─┬─┘ │
        │   │F2 │F4 │   │F7 │F9 │F11│   │
        │ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐ │
        │ │F1 │F3 │F5 │F6 │F8 │F10│F12│ │
        │ └───┴───┴───┴───┴───┴───┴───┘ │
        └───────────────────────────────┘
    */
    [_FN] = LAYOUT(
                                                              _______,
            KC_F2,   KC_F4,            KC_F7,   KC_F9,   KC_F11,
        KC_F1,   KC_F3,   KC_F5,   KC_F6,   KC_F8,   KC_F10,  KC_F12
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
