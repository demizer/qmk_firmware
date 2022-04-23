#include QMK_KEYBOARD_H

#include "oneshot.h"

enum layer_names {
    _BASE,
    _NAVL,
    _SYMB,
    _NUML,
};

#define VOLUP KC_KB_VOLUME_UP
#define VOLDN KC_KB_VOLUME_DOWN
#define VOLMUTE KC_AUDIO_MUTE
#define ZOOMOUT LCTL(KC_MINUS)
#define ZOOMIN LCTL(KC_PLUS)
#define ZOOMRES LCTL(KC_0)
#define LA_SYM MO(_SYMB)
#define LA_NAV MO(_NAVL)
#define ALTTAB LALT(KC_TAB)

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

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

// Tap dance enums
enum {
    SUPERE,
    RMINUS,
    VUNDER,
    CMDTIL,
    COMMAQ,
    DOTXLM,
    SUPERN,
    SUPERC,
    SUPERG,

};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void supere_finished(qk_tap_dance_state_t *state, void *user_data);
void supere_reset(qk_tap_dance_state_t *state, void *user_data);

void rminus_finished(qk_tap_dance_state_t *state, void *user_data);
void rminus_reset(qk_tap_dance_state_t *state, void *user_data);

void vunder_finished(qk_tap_dance_state_t *state, void *user_data);
void vunder_reset(qk_tap_dance_state_t *state, void *user_data);

void supern_finished(qk_tap_dance_state_t *state, void *user_data);
void supern_reset(qk_tap_dance_state_t *state, void *user_data);

void superc_finished(qk_tap_dance_state_t *state, void *user_data);
void superc_reset(qk_tap_dance_state_t *state, void *user_data);

void superg_finished(qk_tap_dance_state_t *state, void *user_data);
void superg_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, TD(SUPERE) , TD(COMMAQ)    , TD(DOTXLM)    , KC_P          , KC_Y      ,           KC_F        , TD(SUPERG)    , TD(SUPERC)    , TD(RMINUS), KC_L      , _______   ,
        _______, KC_A       , KC_O          , KC_E          , KC_U          , KC_I      ,           KC_D        , KC_H          , KC_T          , KC_N      , KC_S      , _______   ,
        _______, TD(CMDTIL) , KC_Q          , KC_J          , KC_K          , KC_X      ,           KC_B        , KC_M          , KC_W          , TD(VUNDER), KC_Z      , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              LA_NAV        , KC_BACKSPACE  ,                                     MEH_T(KC_SPC) , LA_SYM        ,
                                              _______       , ALTTAB        ,                                     KC_ENTER      , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_NAVL] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , LCTL(KC_P)    , VOLUP     ,           LCTL(KC_R)  , KC_HOME       , KC_UP         , KC_END    , ZOOMOUT   , _______   ,
        _______, OS_GUI     , OS_ALT        , OS_SHFT       , OS_CTRL       , VOLDN     ,           LCTL(KC_Z)  , KC_LEFT       , KC_DOWN       , KC_RIGHT  , ZOOMRES   , _______   ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , VOLMUTE   ,           KC_DEL      , KC_PGDN       , KC_PGUP       , KC_CAPS   , ZOOMIN    , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_SYMB] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, KC_ESC     , KC_LBRC       , KC_LCBR       , KC_LPRN       , KC_LT     ,           KC_GT       , KC_RPRN       , KC_RCBR       , KC_RBRC   , XXXXXXX   , _______   ,
        _______, KC_TAB     , XXXXXXX       , KC_AT         , KC_HASH       , XXXXXXX   ,           KC_ENTER    , OS_CTRL       , OS_SHFT       , OS_ALT    , OS_GUI    , _______   ,
        _______, XXXXXXX    , XXXXXXX       , KC_ASTERISK   , KC_CIRC       , KC_PERC   ,           KC_AMPERSAND, KC_DOLLAR     , KC_BACKSLASH  , KC_PIPE   , XXXXXXX   , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_NUML] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, KC_7       , KC_5          , KC_3          , KC_1          , KC_9      ,           KC_8        , KC_0          , KC_2          , KC_4      , KC_6      , _______   ,
        _______, OS_GUI     , OS_ALT        , OS_SHFT       , OS_CTRL       , KC_F11    ,           KC_F12      , OS_CTRL       , OS_SHFT       , OS_ALT    , OS_GUI    , _______   ,
        _______, KC_F7      , KC_F5         , KC_F3         , KC_F1         , KC_F9     ,           KC_F10      , KC_F2         , KC_F4         , KC_F6     , KC_F8     , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	// [LAYER_NAME] = LAYOUT_5x6(
    //     _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______       ,
    //     _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , XXXXXXX       , XXXXXXX       , XXXXXXX   , XXXXXXX   , XXXXXXX       ,
    //     _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , XXXXXXX       , XXXXXXX       , XXXXXXX   , XXXXXXX   , XXXXXXX       ,
    //     _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , XXXXXXX       , XXXXXXX       , XXXXXXX   , XXXXXXX   , XXXXXXX       ,
    //                           _______       , _______       ,                                                                     _______       , _______   ,
    //                                           _______       , _______       ,                                     _______       , _______       ,
    //                                           _______       , _______       ,                                     _______       , _______       ,
    //                                           _______       , _______       ,                                     _______       , _______       ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_GUI,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMB, _NAVL, _NUML);
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
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

static td_tap_t supere_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void supere_finished(qk_tap_dance_state_t *state, void *user_data) {
    supere_state.state = cur_dance(state);
    switch (supere_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_QUOTE); break;
        case TD_SINGLE_HOLD: register_code16(KC_QUOTE); break;
        case TD_DOUBLE_TAP: register_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code16(KC_ESC); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE);
        default:
            break;
    }
}

void supere_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (supere_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_QUOTE); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_ESC);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE);
        default:
            break;
    }
    supere_state.state = TD_NONE;
}

static td_tap_t rminus_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void rminus_finished(qk_tap_dance_state_t *state, void *user_data) {
    rminus_state.state = cur_dance(state);
    switch (rminus_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_R); break;
        case TD_SINGLE_HOLD: register_code16(KC_MINUS); break;
        case TD_DOUBLE_TAP: register_code16(KC_R); break;
        case TD_DOUBLE_HOLD: register_code16(KC_R); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_R); register_code16(KC_R);
        default:
            break;
    }
}

void rminus_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rminus_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_R); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_MINUS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_R); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_R);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_R);
        default:
            break;
    }
    rminus_state.state = TD_NONE;
}

static td_tap_t vunder_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void vunder_finished(qk_tap_dance_state_t *state, void *user_data) {
    vunder_state.state = cur_dance(state);
    switch (vunder_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_V); break;
        case TD_SINGLE_HOLD: register_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: register_code16(KC_V); break;
        case TD_DOUBLE_HOLD: register_code16(KC_V); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_V); register_code16(KC_V);
        default:
            break;
    }
}

void vunder_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (vunder_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_V); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_V); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_V);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_V);
        default:
            break;
    }
    vunder_state.state = TD_NONE;
}

static td_tap_t supern_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void supern_finished(qk_tap_dance_state_t *state, void *user_data) {
    supern_state.state = cur_dance(state);
    switch (supern_state.state) {
        case TD_SINGLE_TAP: layer_on(_SYMB); break;
        case TD_SINGLE_HOLD: layer_on(_NAVL); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default:
            break;
    }
}

void supern_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (supern_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD: layer_off(_NAVL); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default:
            break;
    }
    supern_state.state = TD_NONE;
}

static td_tap_t superc_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void superc_finished(qk_tap_dance_state_t *state, void *user_data) {
    superc_state.state = cur_dance(state);
    switch (superc_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_C); break;
        case TD_SINGLE_HOLD: register_code16(KC_SLASH); break;
        case TD_DOUBLE_TAP: register_code16(KC_C); break;
        case TD_DOUBLE_HOLD: register_code16(KC_C); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_C); register_code16(KC_C);
        default:
            break;
    }
}

void superc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (superc_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_C); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_SLASH); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_C); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_C);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_C);
        default:
            break;
    }
    superc_state.state = TD_NONE;
}

static td_tap_t superg_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void superg_finished(qk_tap_dance_state_t *state, void *user_data) {
    superg_state.state = cur_dance(state);
    switch (superg_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_G); break;
        case TD_SINGLE_HOLD: register_code16(KC_EQUAL); break;
        case TD_DOUBLE_TAP: register_code16(KC_G); break;
        case TD_DOUBLE_HOLD: register_code16(KC_G); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_G); register_code16(KC_G);
        default:
            break;
    }
}

void superg_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (superg_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_G); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_EQUAL); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_G); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_G);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_G);
        default:
            break;
    }
    superg_state.state = TD_NONE;
}

static td_tap_t cmdtil_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void cmdtil_finished(qk_tap_dance_state_t *state, void *user_data) {
    cmdtil_state.state = cur_dance(state);
    switch (cmdtil_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: register_code16(KC_TILD); break;
        case TD_DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case TD_DOUBLE_HOLD: register_code16(KC_GRAVE); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code16(KC_SCLN);
        default:
            break;
    }
}

void cmdtil_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cmdtil_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_TILD); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_GRAVE);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN);
        default:
            break;
    }
    cmdtil_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SUPERE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supere_finished, supere_reset),
    [RMINUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rminus_finished, rminus_reset),
    [VUNDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, vunder_finished, vunder_reset),
    [SUPERN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supern_finished, supern_reset),
    [SUPERC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superc_finished, superc_reset),
    [SUPERG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superg_finished, superg_reset),
    [CMDTIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdtil_finished, cmdtil_reset),
    [COMMAQ] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUES),
    [DOTXLM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EXLM),
};
