/*
Copyright 2021 MigiBacon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x4C42 // LB
#define PRODUCT_ID   0x7003
#define DEVICE_VER   0x0001
#define MANUFACTURER LeBacon
#define PRODUCT      Pianissimo

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 7

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D3, D2 }
#define MATRIX_COL_PINS { F7, B1, B2, B5, B4, E6, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoders */
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { D4 }

/* RGB indicator led */
#define RGB_DI_PIN F6
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 1
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 16
  #define RGBLIGHT_VAL_STEP 16
  #define RGBLIGHT_LIMIT_VAL 128
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION