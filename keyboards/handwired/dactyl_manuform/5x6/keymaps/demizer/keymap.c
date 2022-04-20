#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _NUML,
    _SYMB,
    _FUNL,
    _NAVL,
};

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_O LALT_T(KC_O)
#define HOME_E LSFT_T(KC_E)
#define HOME_U LCTL_T(KC_U)

// Right-hand home row mods
#define HOME_H RCTL_T(KC_H)
#define HOME_T RSFT_T(KC_T)
#define HOME_N LALT_T(KC_N)
#define HOME_S RGUI_T(KC_S)

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
    SUPERG,
    RMINUS,
    VUNDER,
    NMINUS,
    NUNDER,
    COLONX,
    COMMAQ,
    DOTXLM,
    SUPERN,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void superg_finished(qk_tap_dance_state_t *state, void *user_data);
void superg_reset(qk_tap_dance_state_t *state, void *user_data);

void rminus_finished(qk_tap_dance_state_t *state, void *user_data);
void rminus_reset(qk_tap_dance_state_t *state, void *user_data);
void vunder_finished(qk_tap_dance_state_t *state, void *user_data);
void vunder_reset(qk_tap_dance_state_t *state, void *user_data);

void nminus_finished(qk_tap_dance_state_t *state, void *user_data);
void nminus_reset(qk_tap_dance_state_t *state, void *user_data);
void nunder_finished(qk_tap_dance_state_t *state, void *user_data);
void nunder_reset(qk_tap_dance_state_t *state, void *user_data);

void supern_finished(qk_tap_dance_state_t *state, void *user_data);
void supern_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______           , _______   , _______       ,
        _______, TD(SUPERG) , TD(COMMAQ)    , TD(DOTXLM)    , KC_P          , KC_Y      ,           KC_F        , KC_G          , KC_C          , TD(RMINUS)        , KC_L      , _______       ,
        _______, HOME_A     , HOME_O        , HOME_E        , HOME_U        , KC_I      ,           KC_D        , HOME_H        , HOME_T        , HOME_N            , HOME_S    , _______       ,
        _______, TD(COLONX) , KC_Q          , KC_J          , KC_K          , KC_X      ,           KC_B        , KC_M          , KC_W          , TD(VUNDER)        , KC_Z      , _______       ,
                              _______       , _______       ,                                                                     _______       , _______           ,
                                              TD(SUPERN)    , KC_BACKSPACE  ,                                     MEH_T(KC_SPC) , TO(_NUML)     ,
                                              _______       , LALT(KC_TAB)  ,                                     KC_ENTER      , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_NUML] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______       , _______       ,
        _______, KC_ESC     , KC_AT         , KC_HASH       , KC_DOLLAR     , KC_PERCENT,           KC_PLUS     , KC_7          , KC_8          , KC_9      , TD(NMINUS)    , _______       ,
        _______, KC_TAB     , XXXXXXX       , KC_LSFT       , OSL(_FUNL)    , KC_EQUAL  ,           KC_DOT      , KC_4          , KC_5          , KC_6      , RCTL(KC_0)    , _______       ,
        _______, XXXXXXX    , XXXXXXX       , _______       , TO(_NAVL)     , XXXXXXX   ,           KC_0        , KC_1          , KC_2          , KC_3      , TD(NUNDER)    , _______       ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              TO(_BASE)     , _______       ,                                     _______       , _______       ,
                                              _______       , KC_DELETE     ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),


	[_SYMB] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______       ,
        _______, KC_ESC     , KC_AT         , KC_HASH       , KC_DOLLAR     , KC_PERCENT,           KC_CIRC     , KC_AMPERSAND  , KC_ASTERISK   , KC_SCLN   , KC_EXLM   , _______       ,
        _______, KC_TAB     , XXXXXXX       , KC_LSFT       , XXXXXXX       , KC_QUOTE  ,           KC_BACKSLASH, KC_LCBR       , KC_RCBR       , KC_PIPE   , KC_BSPC   , _______       ,
        _______, XXXXXXX    , XXXXXXX       , KC_LT         , KC_GT         , KC_DQUO   ,           KC_LBRC     , KC_LPRN       , KC_RPRN       , KC_RBRC   , XXXXXXX   , _______       ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              TO(_BASE)     , _______       ,                                     _______       , KC_SLASH      ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_FUNL] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______   , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , KC_F7         , KC_F8         , KC_F9     , KC_F12    , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , KC_F4         , KC_F5         , KC_F6     , KC_F11    , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           XXXXXXX     , KC_F1         , KC_F2         , KC_F3     , KC_F10    , _______       ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              TO(_BASE)     , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ,
                                              _______       , _______       ,                                     _______       , _______       ),

	[_NAVL] = LAYOUT_5x6(
        _______, _______    , _______       , _______       , _______       , _______   ,           _______     , _______       , _______       , _______   , _______       , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           LCTL(KC_R)  , LCTL(KC_P)    , LCTL(KC_C)    , LCTL(KC_K), LCTL(KC_Z)    , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           KC_CAPS     , KC_LEFT       , KC_DOWN       , KC_UP     , KC_RIGHT      , _______       ,
        _______, XXXXXXX    , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX   ,           KC_INSERT   , KC_HOME       , KC_PGDN       , KC_PGUP   , KC_END        , _______       ,
                              _______       , _______       ,                                                                     _______       , _______   ,
                                              TO(_BASE)     , _______       ,                                   LCTL(KC_LEFT)   , LCTL(KC_RIGHT),
                                              _______       , _______       ,                                   _______         , _______       ,
                                              _______       , _______       ,                                   _______         , _______       ),

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

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
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

static td_tap_t superg_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void superg_finished(qk_tap_dance_state_t *state, void *user_data) {
    superg_state.state = cur_dance(state);
    switch (superg_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_GRAVE); break;
        case TD_SINGLE_HOLD: register_code16(KC_QUOTE); break;
        case TD_DOUBLE_TAP: register_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code16(KC_ESC); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_GRAVE); register_code16(KC_GRAVE);
        default:
            break;
    }
}

void superg_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (superg_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_QUOTE); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_ESC);
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE);
        default:
            break;
    }
    superg_state.state = TD_NONE;
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
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
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

static td_tap_t nminus_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void nminus_finished(qk_tap_dance_state_t *state, void *user_data) {
    nminus_state.state = cur_dance(state);
    switch (nminus_state.state) {
        case TD_SINGLE_TAP: register_code16(RCTL(KC_PLUS)); break;
        case TD_SINGLE_HOLD: register_code16(KC_MINUS); break;
        case TD_DOUBLE_TAP: register_code16(RCTL(KC_PLUS)); break;
        case TD_DOUBLE_HOLD: register_code16(RCTL(KC_PLUS)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(RCTL(KC_PLUS)); register_code16(RCTL(KC_PLUS));
        default:
            break;
    }
}

void nminus_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (nminus_state.state) {
        case TD_SINGLE_TAP: unregister_code16(RCTL(KC_PLUS)); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_MINUS); break;
        case TD_DOUBLE_TAP: unregister_code16(RCTL(KC_PLUS)); break;
        case TD_DOUBLE_HOLD: unregister_code16(RCTL(KC_PLUS));
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(RCTL(KC_PLUS));
        default:
            break;
    }
    nminus_state.state = TD_NONE;
}

static td_tap_t nunder_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void nunder_finished(qk_tap_dance_state_t *state, void *user_data) {
    nunder_state.state = cur_dance(state);
    switch (nunder_state.state) {
        case TD_SINGLE_TAP: register_code16(RCTL(KC_MINS)); break;
        case TD_SINGLE_HOLD: register_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: register_code16(RCTL(KC_MINS)); break;
        case TD_DOUBLE_HOLD: register_code16(RCTL(KC_MINS)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code16(RCTL(KC_MINS)); register_code16(RCTL(KC_MINS));
        default:
            break;
    }
}

void nunder_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (nunder_state.state) {
        case TD_SINGLE_TAP: unregister_code16(RCTL(KC_MINS)); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: unregister_code16(RCTL(KC_MINS)); break;
        case TD_DOUBLE_HOLD: unregister_code16(RCTL(KC_MINS));
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(RCTL(KC_MINS));
        default:
            break;
    }
    nunder_state.state = TD_NONE;
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

qk_tap_dance_action_t tap_dance_actions[] = {
    [SUPERG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, superg_finished, superg_reset),
    [RMINUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rminus_finished, rminus_reset),
    [VUNDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, vunder_finished, vunder_reset),
    [NMINUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nminus_finished, nminus_reset),
    [NUNDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nunder_finished, nunder_reset),
    [SUPERN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supern_finished, supern_reset),
    [COLONX] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
    [COMMAQ] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUES),
    [DOTXLM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EXLM),
};
