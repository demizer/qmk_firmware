#include QMK_KEYBOARD_H

#include "oneshot.h"

enum layer_names {
    _BASE,
    _NAVL,
    _SYMB,
    _NUML,
    _MEGA,
};

#define VOLUP KC_KB_VOLUME_UP
#define VOLDN KC_KB_VOLUME_DOWN
#define VOLMUTE KC_AUDIO_MUTE
#define ZOOMOUT LCTL(KC_MINUS)
#define ZOOMIN LCTL(KC_PLUS)
#define ZOOMRES LCTL(KC_0)
#define LA_SYM MO(_SYMB)
#define LA_NAV MO(_NAVL)
#define LA_MEG MO(_MEGA)
#define ALTTAB LALT(KC_TAB)
#define CANCEL LCTL(KC_C)
#define WEB LGUI(KC_W)
#define EDIT LGUI(KC_H)
#define TERM LGUI(KC_T)
#define NOTES LGUI(KC_N)
#define SLACK LGUI(KC_S)
#define FILES LGUI(KC_F)
#define REVIEW LGUI(KC_R)
#define MAXIMIZE LGUI(KC_M)
#define MISC LGUI(KC_I)
#define TERMCOPY LCTL(LSFT(KC_C))
#define TERMPAST LCTL(LSFT(KC_V))
#define MT_CAPS MT(MOD_RCTL, KC_CAPS)
#define KC_SWIN MEH(KC_SPACE)
#define IDE_NEXT LCTL(KC_N)
#define IDE_PREV LCTL(KC_P)

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
    CMDTIL,
    COMMAQ,
    DOTXLM,
    F5SHFT,
    F4CTRL,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void supere_finished(qk_tap_dance_state_t *state, void *user_data);
void supere_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        KC_LGUI, KC_QUOTE   , TD(COMMAQ)    , TD(DOTXLM)    , KC_P          , KC_Y      ,           KC_F        , KC_G          , KC_C          , KC_R      , KC_L      , KC_CAPS   ,
        KC_LCTL, KC_A       , KC_O          , KC_E          , KC_U          , KC_I      ,           KC_D        , KC_H          , KC_T          , KC_N      , KC_S      , KC_RCTL   ,
        KC_ESC , KC_SCLN    , KC_Q          , KC_J          , KC_K          , KC_X      ,           KC_B        , KC_M          , KC_W          , KC_V      , KC_Z      , KC_SWIN   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              LA_NAV        , KC_BACKSPACE  ,                                     KC_SPC        , LA_SYM        ,
                                              KC_LSFT       , LA_MEG        ,                                     KC_ENTER      , KC_RSFT       ,
                                              IDE_PREV      , _______       ,                                     _______       , IDE_NEXT      ),

	[_NAVL] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, XXXXXXX    , XXXXXXX       , LCTL(KC_C)    , LCTL(KC_P)    , VOLUP     ,           _______     , KC_HOME       , KC_UP         , KC_END    , ZOOMOUT   , XXXXXXX   ,
        _______, KC_LGUI    , OS_ALT        , KC_LSFT       , KC_LCTL       , VOLDN     ,           KC_GRAVE    , KC_LEFT       , KC_DOWN       , KC_RIGHT  , ZOOMRES   , KC_PGUP   ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , VOLMUTE   ,           KC_TILD     , _______       , _______       , _______   , ZOOMIN    , KC_PGDN   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , _______       ,                                     TERMPAST      , _______       ,
                                              _______       , _______       ,                                     TERMCOPY      , KC_DEL        ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_SYMB] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, XXXXXXX    , KC_LBRC       , KC_LCBR       , KC_LPRN       , KC_LT     ,           KC_GT       , KC_RPRN       , KC_RCBR       , KC_RBRC   , XXXXXXX   , _______   ,
        _______, KC_TAB     , KC_PLUS       , KC_AT         , KC_HASH       , KC_DQUO   ,           KC_SLASH    , XXXXXXX       , OS_ALT        , XXXXXXX   , XXXXXXX   , _______   ,
        _______, XXXXXXX    , XXXXXXX       , KC_ASTERISK   , KC_CIRC       , KC_PERC   ,           KC_AMPERSAND, KC_DOLLAR     , KC_EQUAL      , KC_BSLS   , KC_PIPE   , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , KC_MINS       ,                                     _______       , _______       ,
                                              _______       , KC_UNDS       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_NUML] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______   ,
        _______, KC_F12     , KC_F3         , KC_F2         , KC_F1         , XXXXXXX   ,           XXXXXXX     , KC_7          , KC_8          , KC_9      , XXXXXXX   , _______   ,
        _______, KC_F11     , KC_F6         , KC_F5         , KC_F4         , KC_BSPC   ,           KC_DOT      , KC_4          , KC_5          , KC_6      , KC_EQUAL  , _______   ,
        _______, KC_F10     , KC_F9         , KC_F8         , KC_F7         , XXXXXXX   ,           KC_0        , KC_1          , KC_2          , KC_3      , KC_MINS   , _______   ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_MEGA] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           FILES       , XXXXXXX       , XXXXXXX       , REVIEW    , XXXXXXX   , XXXXXXX       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , MISC      ,           XXXXXXX     , EDIT          , TERM          , NOTES     , SLACK     , XXXXXXX       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , MAXIMIZE      , WEB           , XXXXXXX   , XXXXXXX   , XXXXXXX       ,
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
        case TD_SINGLE_HOLD: register_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOTE); register_code16(KC_QUOTE);
        default:
            break;
    }
}

void supere_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (supere_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GRAVE); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default:
            break;
    }
    supere_state.state = TD_NONE;
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
        case TD_DOUBLE_TAP:  break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code16(KC_SCLN);
        default:
            break;
    }
}

void cmdtil_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cmdtil_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_TILD); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN);
        default:
            break;
    }
    cmdtil_state.state = TD_NONE;
}

static td_tap_t f5shft_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void f5shft_finished(qk_tap_dance_state_t *state, void *user_data) {
    f5shft_state.state = cur_dance(state);
    switch (f5shft_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_F5); break;
        case TD_SINGLE_HOLD: register_code16(KC_LSFT); break;
        // case TD_DOUBLE_TAP: register_code16(KC_GRAVE); break;
        // case TD_DOUBLE_HOLD: register_code16(KC_GRAVE); break;
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code16(KC_SCLN);
        default:
            break;
    }
}

void f5shft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (f5shft_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_F5); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break;
        // case TD_DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        // case TD_DOUBLE_HOLD: unregister_code16(KC_GRAVE);
        // case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN);
        default:
            break;
    }
    f5shft_state.state = TD_NONE;
}

static td_tap_t f4ctrl_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void f4ctrl_finished(qk_tap_dance_state_t *state, void *user_data) {
    f4ctrl_state.state = cur_dance(state);
    switch (f4ctrl_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_F4); break;
        case TD_SINGLE_HOLD: register_code16(KC_LCTL); break;
        // case TD_DOUBLE_TAP: register_code16(KC_GRAVE); break;
        // case TD_DOUBLE_HOLD: register_code16(KC_GRAVE); break;
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code16(KC_SCLN);
        default:
            break;
    }
}

void f4ctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (f4ctrl_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_F4); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LCTL); break;
        // case TD_DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        // case TD_DOUBLE_HOLD: unregister_code16(KC_GRAVE);
        // case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN);
        default:
            break;
    }
    f4ctrl_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SUPERE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supere_finished, supere_reset),
    [CMDTIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdtil_finished, cmdtil_reset),
    [COMMAQ] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUES),
    [DOTXLM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EXLM),
    [F5SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f5shft_finished, f5shft_reset),
    [F4CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f4ctrl_finished, f4ctrl_reset),
};
