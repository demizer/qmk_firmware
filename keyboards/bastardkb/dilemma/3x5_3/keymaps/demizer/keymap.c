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

// Tap dance enums
enum {
    SUPERQDK,
    SUPERQHD,
    COMMAQ,
    DOTXLM,
    /* CMDTIL, */
    /* F5SHFT, */
    /* F4CTRL, */
};

td_state_t cur_dance(tap_dance_state_t *state);

void superqdk_finished(tap_dance_state_t *state, void *user_data);
void superqdk_reset(tap_dance_state_t *state, void *user_data);
void superqhd_finished(tap_dance_state_t *state, void *user_data);
void superqhd_reset(tap_dance_state_t *state, void *user_data);

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_HANDS_DOWN,
    LAYER_NUMERAL,
    LAYER_NAVIGATION,
    LAYER_FUNCTION,
    LAYER_POINTER,
    LAYER_SYMBOLS,
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  HANDS_DOWN
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define SPC_NUM LT(LAYER_NUMERAL, KC_SPC)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)
#define ENT_NAV LT(LAYER_NAVIGATION, KC_ENT)
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

static td_tap_t superqdk_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t superqhd_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void superqdk_finished(tap_dance_state_t *state, void *user_data) {
    superqdk_state.state = cur_dance(state);
    switch (superqdk_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_QUOTE); break;
        case TD_SINGLE_HOLD: register_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: register_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_QUOTE); break;
        /* case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE); */
        default:
            break;
    }
}

void superqdk_reset(tap_dance_state_t *state, void *user_data) {
    switch (superqdk_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_ESC); break;
        /* case TD_DOUBLE_HOLD: break; */
        /* case TD_DOUBLE_SINGLE_TAP: break; */
        default:
            break;
    }
    superqdk_state.state = TD_NONE;
}

void superqhd_finished(tap_dance_state_t *state, void *user_data) {
    superqhd_state.state = cur_dance(state);
    switch (superqhd_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_Q); break;
        case TD_SINGLE_HOLD: register_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: register_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_Q); break;
        /* case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE); */
        default:
            break;
    }
}

void superqhd_reset(tap_dance_state_t *state, void *user_data) {
    switch (superqhd_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_Q); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_ESC); break;
        /* case TD_DOUBLE_HOLD: break; */
        /* case TD_DOUBLE_SINGLE_TAP: break; */
        default:
            break;
    }
    superqhd_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [SUPERQDK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superqdk_finished, superqdk_reset),
    [SUPERQHD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superqhd_finished, superqhd_reset),
    [COMMAQ] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUES),
    [DOTXLM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EXLM),
};

enum combos { ESCAPE_COMBO, SUPER_COMBO };
const uint16_t PROGMEM escape_combo[] = {ENT_NAV, BSP_FUN, COMBO_END};
const uint16_t PROGMEM super_combo[] = {TAB_SYM, SPC_NUM, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [ESCAPE_COMBO] = COMBO(escape_combo, KC_ESC),
    [SUPER_COMBO] = COMBO(super_combo, KC_LGUI),
    /* COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too! */
};

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                                    \
 TD(SUPERQDK), TD(COMMAQ), TD(DOTXLM),       KC_P,       KC_Y,       KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,       KC_O,       KC_E,       KC_U,       KC_I,       KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_COLN,       KC_Q,       KC_J,       KC_K,       KC_X,       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                            CW_TOGG,    TAB_SYM,    SPC_NUM,    ENT_NAV, BSP_FUN, KC_MUTE

#define LAYOUT_LAYER_HANDS_DOWN                                                               \
 TD(SUPERQHD),    KC_C,    KC_H,    KC_P,    KC_V,    KC_K,    KC_Y,    KC_O,    KC_J, KC_SLSH, \
       KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_W,    KC_U,    KC_E,    KC_I,    KC_A, \
       KC_X,    KC_M,    KC_L,    KC_D,    KC_B,    KC_Z,    KC_F, KC_QUOT, KC_COMM,  KC_DOT, \
                      CW_TOGG, TAB_SYM, SPC_NUM,    ENT_NAV, BSP_FUN, KC_MUTE

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                   \
    _______________DEAD_HALF_ROW_______________, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,  \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_BSLS,  KC_DOT,    KC_4,    KC_5,    KC_6,  KC_EQL,  \
    _______________DEAD_HALF_ROW_______________,    KC_0,    KC_1,    KC_2,    KC_3, KC_UNDS,  \
                      XXXXXXX, XXXXXXX, _______, KC_QUES, _______, XXXXXXX

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                  \
    XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HANDS_DOWN, \
    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, ______________HOME_ROW_GACS_R______________,    \
    XXXXXXX, XXXXXXX,  KC_INS,  KC_DEL, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DVORAK,     \
                      XXXXXXX, KC_WREF, KC_WBAK, _______, XXXXXXX,  XXXXXXX

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                 \
    KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, _______________DEAD_HALF_ROW_______________, \
    KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, ______________HOME_ROW_GACS_R______________, \
    KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, _______________DEAD_HALF_ROW_______________, \
                      XXXXXXX, XXXXXXX,  KC_ESC, XXXXXXX, _______, XXXXXXX

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX, XXXXXXX, KC_BTN3, SNIPING, DRGSCRL, _______, \
                      KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, KC_BTN3

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                  \
    _______________DEAD_HALF_ROW_______________, KC_LCBR, KC_AMPR, KC_ASTR, KC_RPRN, KC_RCBR, \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_PIPE, KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, \
    _______________DEAD_HALF_ROW_______________, KC_LPRN, KC_EXLM,   KC_AT, KC_HASH, KC_MINS, \
                      XXXXXXX, _______, XXXXXXX, KC_SLSH, KC_TILD, KC_GRV

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
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_HANDS_DOWN] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_HANDS_DOWN))
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

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_HANDS_DOWN] = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),  ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),  ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
  }
  return true;
}
