/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "achordion.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    SUPERSLSH,
};

td_state_t cur_dance(tap_dance_state_t *state);

void superslsh_finished(tap_dance_state_t *state, void *user_data);
void superslsh_reset(tap_dance_state_t *state, void *user_data);

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_HANDS_DOWN,
    LAYER_NUMERAL,
    LAYER_NAVIGATION,
    LAYER_FUNCTION,
    LAYER_POINTER,
    LAYER_MACRO,
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  HANDS_DOWN,
  SUDO_SYS_CTL
};

// Automatically enable sniping-mode on the pointer layer.
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define SPC_NUM LT(LAYER_NUMERAL, KC_SPC)
#define ENT_MACRO LT(LAYER_MACRO, KC_ENT)
#define TAB_NAV LT(LAYER_NAVIGATION, KC_TAB)
#define BSP_FUN LT(LAYER_FUNCTION, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)
#define DF_HNDN DF(LAYER_HANDS_DOWN)
#define DF_DVOK DF(LAYER_BASE)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t superslsh_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void superslsh_finished(tap_dance_state_t *state, void *user_data) {
    superslsh_state.state = cur_dance(state);
    switch (superslsh_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_SLSH); break;
        case TD_SINGLE_HOLD: register_code16(KC_BSLS); break;
        case TD_DOUBLE_TAP: register_code16(KC_PIPE); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_SLSH); break;
        /* case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE); */
        default:
            break;
    }
}

void superslsh_reset(tap_dance_state_t *state, void *user_data) {
    switch (superslsh_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_SLSH); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_BSLS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_PIPE); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_SLSH); break;
        /* case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE); */
        default:
            break;
    }
    superslsh_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [SUPERSLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superslsh_finished, superslsh_reset),
};

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                        \
    KC_QUOT, KC_COMM, KC_DOT,     KC_P,    KC_Y,       KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,   KC_E,     KC_U,    KC_I,       KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_COLN,    KC_Q,   KC_J,     KC_K,    KC_X,       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                     CW_TOGG,  TAB_NAV, SPC_NUM,  ENT_MACRO, BSP_FUN, KC_MUTE

#define LAYOUT_LAYER_HANDS_DOWN                                                                  \
    XXXXXXX,    KC_C,   KC_H,     KC_P,    KC_V,       KC_K,    KC_Y,    KC_O,    KC_J, KC_SLSH, \
       KC_R,    KC_S,   KC_N,     KC_T,    KC_G,       KC_W,    KC_U,    KC_E,    KC_I,    KC_A, \
       KC_X,    KC_M,   KC_L,     KC_D,    KC_B,       KC_Z,    KC_F, KC_QUOT, KC_COMM,  KC_DOT, \
                      CW_TOGG, TAB_NAV, SPC_NUM,  ENT_MACRO, BSP_FUN, KC_MUTE

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

#define LAYOUT_LAYER_NAVIGATION                                                                  \
    _______________DEAD_HALF_ROW_______________,  KC_DEL, KC_WBAK,  KC_ESC, KC_WFWD, KC_WREF,    \
    ______________HOME_ROW_GACS_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,    \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,    \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC, XXXXXXX

#define LAYOUT_LAYER_NUMERAL                                                                         \
    _______________DEAD_HALF_ROW_______________,       KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,  \
    ______________HOME_ROW_GACS_L______________,        KC_GRV,    KC_4,    KC_5,    KC_6,  KC_EQL,  \
    _______________DEAD_HALF_ROW_______________,          KC_0,    KC_1,    KC_2,    KC_3, KC_MINS,  \
                      XXXXXXX, XXXXXXX, _______, TD(SUPERSLSH), KC_BSPC, XXXXXXX

#define LAYOUT_LAYER_FUNCTION                                                                 \
    KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, _______________DEAD_HALF_ROW_______________, \
    KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, ______________HOME_ROW_GACS_R______________, \
    KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, _______________DEAD_HALF_ROW_______________, \
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX, XXXXXXX, KC_BTN3, SNIPING, DRGSCRL, _______, \
                      KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, KC_BTN3

#define LAYOUT_LAYER_MACRO                                                                    \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______________DEAD_HALF_ROW_______________, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ______________HOME_ROW_GACS_R______________, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______________DEAD_HALF_ROW_______________, \
                 XXXXXXX, XXXXXXX, SUDO_SYS_CTL, _______, XXXXXXX, XXXXXXX


/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_HANDS_DOWN] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_HANDS_DOWN))
  ),
  [LAYER_MACRO] = LAYOUT_wrapper(LAYOUT_LAYER_MACRO),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
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

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD,  KC_VOLU)},
    [LAYER_HANDS_DOWN] = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD,  KC_VOLU)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX),  ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(RGB_SPD,  RGB_SPI)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(RGB_VAD,  RGB_VAI)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),  ENCODER_CCW_CW(RGB_SAD,  RGB_SAI)},
    [LAYER_MACRO]      = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX),  ENCODER_CCW_CW(KC_LEFT,  KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }
  switch (keycode) {
    case HANDS_DOWN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(LAYER_HANDS_DOWN);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(LAYER_BASE);
      }
      return false;
      break;
    case SUDO_SYS_CTL:
      if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          SEND_STRING("QMK is the best thing ever!");
      /* } else { */
      /*     // when keycode QMKBEST is released */
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}
