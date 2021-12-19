#include QMK_KEYBOARD_H

enum layer_names {
    _MAIN,
    _QWERTY,
    _RAISE,
    _VIM,
};

/* #define RAISE MO(_RAISE) */
/* #define LOWER MO(_LOWER) */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MAIN] = LAYOUT_5x6(
        KC_QUES         , KC_EXLM   , KC_AT     , KC_HASH   , OSL(3)  , KC_LBRC   ,                   KC_RBRC   , KC_BSPC   , KC_SLSH   , KC_BSLS   , KC_PGDN   , KC_PGUP   ,
        KC_TAB          , KC_QUOT   , KC_COMM   , KC_DOT    , KC_P    , KC_Y      ,                   KC_F      , KC_G      , KC_C      , KC_R      , KC_L      , KC_PIPE   ,
        OSM(MOD_LCTL)   , KC_A      , KC_O      , KC_E      , KC_U    , KC_I      ,                   KC_D      , KC_H      , KC_T      , KC_N      , KC_S      , KC_EQL    , 
        KC_GESC         , KC_COLN   , KC_Q      , KC_J      , KC_K    , KC_X      ,                   KC_B      , KC_M      , KC_W      , KC_V      , KC_Z      , KC_ASTR   ,
                                      KC_LCBR   , KC_DLR    ,                                                               OSL(3)    , KC_RCBR   ,
                                                            MO(2)     , KC_LGUI     ,               KC_SPC      , MO(2)     ,
                                                            KC_LSPO   , KC_DEL      ,               KC_ENT      , KC_RSPC   ,
                                                            KC_NO     , LCTL(KC_U)  ,               RCTL(KC_D)  , KC_NO     ),

	[_QWERTY] = LAYOUT_5x6(
        KC_GRV          , KC_1      , KC_2      , KC_3      , KC_4  , KC_5      ,                   KC_6    , KC_7      , KC_8      , KC_9      , KC_0      , DF(0)     ,
        KC_TRNS         , KC_Q      , KC_W      , KC_E      , KC_R  , KC_T      ,                   KC_Y    , KC_U      , KC_I      , KC_O      , KC_P      , KC_TRNS   ,
        KC_TRNS         , KC_A      , KC_S      , KC_D      , KC_F  , KC_G      ,                   KC_H    , KC_J      , KC_K      , KC_L      , KC_SCLN   , KC_TRNS   ,
        KC_TRNS         , KC_Z      , KC_X      , KC_C      , KC_V  , KC_B      ,                   KC_N    , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_TRNS   ,
                                      KC_TRNS   , KC_TRNS   ,                                                             KC_TRNS   , KC_TRNS   ,
                                                        KC_TRNS     , KC_TRNS   ,               KC_TRNS     , KC_TRNS   ,
                                                        KC_TRNS     , KC_TRNS   ,               KC_TRNS     , KC_TRNS   ,
                                                        KC_TRNS     , KC_TRNS   ,               KC_TRNS     , KC_TRNS   ),

	[_RAISE] = LAYOUT_5x6(
        KC_F11          , KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,                   KC_F6       , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F12    ,
        KC_NO           , KC_NO     , KC_NO     , KC_UP     , KC_PERC   , KC_NO     ,                   KC_AMPR     , KC_7      , KC_8      , KC_9      , KC_CIRC   , KC_NO     ,
        KC_NO           , KC_NO     , KC_LEFT   , KC_DOWN   , KC_DOWN   , KC_NO     ,                   KC_NO       , KC_4      , KC_5      , KC_6      , KC_MINS   , KC_UNDS   ,
        DF(1)           , KC_SCLN   , KC_NO     , KC_GRV    , KC_DQUO   , KC_NO     ,                   KC_PLUS     , KC_1      , KC_2      , KC_3      , KC_NO     , KC_NO     ,
                                      KC_NO     , KC_NO     ,                                                                     KC_NO     , KC_0      ,
                                                            KC_NO       , KC_TRNS   ,                   KC_TRNS     , KC_NO     ,
                                                            KC_NO       , KC_NO     ,                   KC_NO       , KC_NO     ,
                                                            KC_NO       , KC_NO     ,                   KC_NO       , KC_NO     ),

	[_VIM] = LAYOUT_5x6(
        KC_NO           , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,                   KC_NO       , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
        KC_NO           , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,                   KC_NO       , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
        KC_NO           , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,                   KC_NO       , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
        KC_NO           , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,                   KC_NO       , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
                                      KC_NO     , KC_TRNS   ,                                                             KC_TRNS   , KC_NO     ,
                                                        KC_NO       , KC_NO     ,               KC_NO       , KC_NO     ,
                                                        KC_NO       , KC_NO     ,               KC_NO       , KC_NO     ,
                                                        KC_NO       , KC_NO     ,               KC_NO       , KC_NO     )
};
