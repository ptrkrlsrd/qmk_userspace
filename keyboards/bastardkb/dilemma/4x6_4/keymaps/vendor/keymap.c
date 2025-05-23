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
#include "sendstring_norwegian.h"


enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

enum {
    TD_Q_TAB,
    TD_1_SHFT,
    TD_W_SAVE,
    TD_GRV_ESC,
    CT_CLN,
    CT_DOT,
    CT_DASH,
    CT_MINS,
    CT_GRV_ESC,
    CT_SHFT_1,
    CT_SHFT_2,
    CT_SHFT_3,
    CT_SHFT_4,
    CT_SHFT_5,
    CT_SHFT_6,
    CT_SHFT_7,
    CT_SHFT_8,
    CT_SHFT_9,
    CT_SHFT_0
};

enum custom_keycodes {
    L_BRACER = SAFE_RANGE,
    R_BRACER,
    SAVE_MACRO
};

#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD

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
#define HM_Y    MT(MOD_HYPR, KC_Y)
#define HM_T    MT(MOD_HYPR, KC_T)

#define HM_H    MT(MOD_RALT, KC_H)
#define HM_J    MT(MOD_LSFT, KC_J)
#define HM_K    MT(MOD_LCTL, KC_K)
#define HM_L    MT(MOD_LGUI, KC_L)

/* Norwegian Special Characters */
#define U_LBRC RALT(KC_7)    // {
#define U_RBRC RALT(KC_0)    // }
#define U_LBRK RALT(KC_8)    // [
#define U_RBRK RALT(KC_9)    // ]

/* Tap Dance Shortcuts */
// Basic tap-dance
#define TD_QTAB TD(TD_Q_TAB)     // Tap: Q, Double-tap: Tab
#define TD_WSAVE TD(TD_W_SAVE)    // Tap: W, Hold: :W
#define TD_1SHFT TD(TD_1_SHFT)    // Tap: 1, Double-tap: !
#define TD_GESC TD(TD_GRV_ESC)    // Tap: Grave, Double-tap: Esc

// Number row tap-holds
#define TD_1 TD(CT_SHFT_1)
#define TD_2 TD(CT_SHFT_2)
#define TD_3 TD(CT_SHFT_3)
#define TD_4 TD(CT_SHFT_4)
#define TD_5 TD(CT_SHFT_5)
#define TD_6 TD(CT_SHFT_6)
#define TD_7 TD(CT_SHFT_7)
#define TD_8 TD(CT_SHFT_8)
#define TD_9 TD(CT_SHFT_9)
#define TD_0 TD(CT_SHFT_0)

// Special character tap-holds
#define TD_GRV TD(CT_GRV_ESC) 
#define TD_MIN TD(CT_MINS)
#define TD_COMM TD(CT_CLN)
#define TD_DOT TD(CT_DOT)
#define TD_SLSH TD(CT_DASH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#ifdef INTROSPECTION_KEYMAP_C
#    include INTROSPECTION_KEYMAP_C
#endif // INTROSPECTION_KEYMAP_C


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;


void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),
    [TD_W_SAVE] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, SAVE_MACRO),
    [TD_1_SHFT] = ACTION_TAP_DANCE_DOUBLE(KC_1, S(KC_1)),
    [TD_GRV_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
    [CT_SHFT_1] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_1), KC_1),
    [CT_SHFT_2] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_2), KC_2),
    [CT_SHFT_3] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_3), KC_3),
    [CT_SHFT_4] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_4), KC_4),
    [CT_SHFT_5] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_5), KC_5),
    [CT_SHFT_6] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_6), KC_6),
    [CT_SHFT_7] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_7), KC_7),
    [CT_SHFT_8] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_8), KC_8),
    [CT_SHFT_9] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_9), KC_9),
    [CT_SHFT_0] = ACTION_TAP_DANCE_TAP_HOLD(S(KC_0), KC_0),
    [CT_GRV_ESC] = ACTION_TAP_DANCE_TAP_HOLD(KC_ESC, KC_GRV),
    [CT_MINS] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, S(KC_MINS)),
    [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, S(KC_COMM)),
    [CT_DOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, S(KC_DOT)),
    [CT_DASH] = ACTION_TAP_DANCE_TAP_HOLD(KC_PSLS, S(KC_PSLS)), // Check this on windows
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case L_BRACER:
            if (record->event.pressed) {
                SEND_STRING("{ ");
            }
            return true;
        case R_BRACER:
            if (record->event.pressed) {
                SEND_STRING("} ");
            }
            return true;
        case SAVE_MACRO:
            if (record->event.pressed) {
                SEND_STRING(":w");
            }
            return true;
        break;
    case TD(TD_W_SAVE):
    case TD(CT_GRV_ESC):
    case TD(CT_SHFT_1):
    case TD(CT_SHFT_2):
    case TD(CT_SHFT_3):
    case TD(CT_SHFT_4):
    case TD(CT_SHFT_5):
    case TD(CT_SHFT_6):
    case TD(CT_SHFT_7):
    case TD(CT_SHFT_8):
    case TD(CT_SHFT_9):
    case TD(CT_SHFT_0):
    case TD(CT_DOT):
    case TD(CT_DASH):
    case TD(CT_MINS):
    case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
        action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
    }
    return true;
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────╮ ╭────────────────────────────────╮
         TD(CT_GRV_ESC), TD(CT_SHFT_1), TD(CT_SHFT_2), TD(CT_SHFT_3), TD(CT_SHFT_4), TD(CT_SHFT_5),           TD(CT_SHFT_6), TD(CT_SHFT_7), TD(CT_SHFT_8), TD(CT_SHFT_9), TD(CT_SHFT_0), TD(CT_MINS),
  // ├─────────────────────────────┤ ├────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    HM_T,                              HM_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       KC_LSFT,    KC_A,    HM_S,    HM_D,    HM_F,    HM_G,                           HM_H,    HM_J,    HM_K,    HM_L, KC_SCLN, KC_QUOT,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       KC_LCTL,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M, TD(CT_CLN),  TD(CT_DOT), TD(CT_DASH), KC_LALT,
  // ╰─────────────────────────────┤ ├────────────────────────────────╯
                         KC_LALT, KC_BSPC,  KC_SPC,   LOWER,                                RAISE,  KC_ENT, KC_LGUI,  KC_MUTE
  //                    ╰────────────────────────╯ ╰────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭─────────────────────────────╮ ╭────────────────────────────────╮
       S(KC_GRV),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       KC_NUBS, S(KC_NUBS), U_LBRK, U_RBRK, U_LBRC, U_RBRC,                KC_P1,   KC_P2,   KC_P3,   U_LBRK, U_RBRK, KC_COMM,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, TD(CT_CLN),  TD(CT_DOT), KC_SLSH,         KC_P4,   KC_P5,   KC_P6, U_LBRC, U_RBRC, KC_PEQL,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, RAISE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               KC_P7,   KC_P8,   KC_P9,   KC_NUBS, S(KC_NUBS), KC_PDOT,
  // ╰─────────────────────────────┤ ├────────────────────────────────╯
                         KC_NO, KC_NO, KC_NO, _______,                                        KC_TRNS, KC_NO, KC_NO, KC_NO
  //                    ╰────────────────────────╯ ╰────────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭─────────────────────────────╮ ╭────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       KC_NUBS, S(KC_NUBS), U_LBRK, U_RBRK, U_LBRC, U_RBRC,               U_LBRC, U_RBRC, U_LBRK, U_RBRK, KC_NUBS, S(KC_NUBS),
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, XXXXXXX,   SAVE_MACRO, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LEFT,   KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       TD(CT_CLN),  TD(CT_DOT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────┤ ├────────────────────────────────╯
                         XXXXXXX, _______, _______, XXXXXXX,    _______,                XXXXXXX, XXXXXXX, XXXXXXX
  //                    ╰────────────────────────╯ ╰────────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭─────────────────────────────╮ ╭────────────────────────────────╮
       QK_BOOT, EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR, QK_BOOT,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, SNIPING, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├─────────────────────────────┤ ├────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX,  SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰─────────────────────────────┤ ├────────────────────────────────╯
                         XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1, KC_BTN2, XXXXXXX
  //                    ╰────────────────────────╯ ╰────────────────────╯
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
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_LOWER]      = {ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_RAISE]      = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE
