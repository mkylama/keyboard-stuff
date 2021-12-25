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
    _M1,
    _M2,
    _M3,
    _M4,
    _M5,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CC_NXT = SAFE_RANGE,
    CC_PRV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_M1] = LAYOUT(
                                                              TG(_M2),
            MI_Cs_1, MI_Ds_1,          MI_Fs_1, MI_Gs_1, MI_As_1,
        MI_C_1,   MI_D_1,  MI_E_1,  MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1
    ),
    [_M2] = LAYOUT(
                                                              TG(_M3),
            MI_Cs_2, MI_Ds_2,          MI_Fs_2, MI_Gs_2, MI_As_2,
        MI_C_2,   MI_D_2,  MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2
    ),
    [_M3] = LAYOUT(
                                                              TG(_M4),
            MI_Cs_3, MI_Ds_3,          MI_Fs_3, MI_Gs_3, MI_As_3,
        MI_C_3,   MI_D_3,  MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3
    ),
    [_M4] = LAYOUT(
                                                              TG(_M5),
            MI_Cs_4, MI_Ds_4,          MI_Fs_4, MI_Gs_4, MI_As_4,
        MI_C_4,   MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4
    ),
    [_M5] = LAYOUT(
                                                              TG(_FN),
            MI_Cs_5, MI_Ds_5,          MI_Fs_5, MI_Gs_5, MI_As_5,
        MI_C_5,   MI_D_5,  MI_E_5,  MI_F_5,  MI_G_5,  MI_A_5,  MI_B_5
    ),
    [_FN] = LAYOUT(
                                                              TO(_M1),
            KC_1,    KC_2,             KC_3,    KC_4,    KC_5,
        KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_A,    KC_H
    ),
};

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
                            24,
      13, 15,     18, 20, 22, 
    12, 14, 16, 17, 19, 21, 23
);

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
