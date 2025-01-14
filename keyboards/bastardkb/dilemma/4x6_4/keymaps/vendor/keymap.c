/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#include "keymap_norwegian.h"

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// Home row mods
#define HM_A    KC_A
#define HM_S    MT(MOD_LALT, KC_S)
#define HM_D    MT(MOD_LSFT, KC_D)
#define HM_F    MT(MOD_LCTL, KC_F)
#define HM_G    MT(MOD_LGUI, KC_G)

#define HM_H    MT(MOD_LALT, KC_H)
#define HM_J    MT(MOD_LSFT, KC_J)
#define HM_K    MT(MOD_LCTL, KC_K)
#define HM_L    MT(MOD_LGUI, KC_L)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#ifdef INTROSPECTION_KEYMAP_C 
#    include INTROSPECTION_KEYMAP_C 
#endif // INTROSPECTION_KEYMAP_C

enum {
    TD_GRV_ESC,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_GRV_ESC] = ACTION_TAP_DANCE_DOUBLE(S(KC_GRV), KC_ESC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,   HM_A,    HM_S,    HM_D,    HM_F,    HM_G,       HM_H,    HM_J,    HM_K,    HM_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       MT(MOD_LCTL,KC_ESC), PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_NO,  KC_BSPC, MT(MOD_LCTL,KC_SPC), LOWER,      RAISE,   KC_ENT,  KC_MUTE, KC_LGUI
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),    S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_MINS),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TRNS, LSA(KC_8), LSA(KC_9), RALT(KC_8), RALT(KC_9), RALT(KC_RBRC),    KC_NO, KC_COMM, RALT(KC_0), RALT(KC_7), RALT(KC_9), RALT(KC_8),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TRNS, KC_LGUI, KC_LALT, KC_NUBS, KC_NUBS, S(KC_DOT),    KC_PEQL, KC_PMNS, KC_COMM, KC_NO, KC_NO, KC_NO,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TRNS, KC_NUBS, S(KC_NUBS), RALT(KC_NO), RALT(KC_NO), KC_NO,    KC_PDOT, KC_PSLS, KC_NO, KC_NO, KC_NO, KC_NO,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_NO, KC_NO, KC_NO, KC_TRNS,    KC_TRNS, KC_TRNS, KC_NO, KC_NO
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, KC_NO, MACRO(0), MACRO(2), KC_NO, KC_NO,    KC_NO, KC_NUHS, S(KC_9), S(KC_8), RALT(KC_0), RALT(KC_7),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, MACRO(0), MACRO(0), KC_NO, KC_NO, KC_NO,    KC_NO, S(KC_NUHS), KC_RGHT, KC_UP, KC_DOWN, KC_LEFT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, KC_NUBS, S(KC_NUBS), KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, S(KC_9), S(KC_8),
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_NO, KC_TRNS, KC_TRNS, KC_NO,    KC_NO, KC_NO, KC_NO, KC_TRNS
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, KC_NO, KC_NO, KC_NO, CUSTOM(0), CUSTOM(2),    KC_NO, KC_NO, KC_NO, KC_NO, CUSTOM(0), CUSTOM(2),
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,    KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, KC_NO,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_NO, KC_TRNS, CUSTOM(6), CUSTOM(4), QK_CLEAR_EEPROM, KC_NO,    KC_NO, KC_TRNS, CUSTOM(6), CUSTOM(4), QK_CLEAR_EEPROM, RESET,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_NO, KC_MS_BTN2, KC_MS_BTN1, KC_MS_BTN3,    KC_NO, KC_MS_BTN2, KC_MS_BTN1, KC_NO
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif // RGB_MATRIX_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_LOWER]      = {ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_RAISE]      = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE
