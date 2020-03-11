#include QMK_KEYBOARD_H

// Helpful defines for tap-hold (uses tapdance functionality)
#define _______ KC_TRNS

#define TAP(keycode) register_code(keycode); unregister_code(keycode)

#define TAPPING_TERM 100

#define void__AutoFunc(KC1,KC2) void KC1 ## _finished (qk_tap_dance_state_t *state, void *user_data) { \
    if (state->count == 1) { \
        if (!state->interrupted && state->pressed) { \
            TAP(KC2); \
        } else { \
            TAP(KC1); \
        } \
    } \
} \
void KC1 ## _tap (qk_tap_dance_state_t *state, void *user_data) { \
    if (state->count == 1) return; \
    if (state->count == 2) TAP(KC1); \
    if (state->count >= 2) TAP(KC1); \
} 

#define AutoFunc(KC1) ACTION_TAP_DANCE_FN_ADVANCED(KC1 ## _tap, KC1 ## _finished, NULL)

void__AutoFunc(KC_1, KC_F1)
void__AutoFunc(KC_2, KC_F2)
void__AutoFunc(KC_3, KC_F3)
void__AutoFunc(KC_4, KC_F4)
void__AutoFunc(KC_5, KC_F5)
void__AutoFunc(KC_6, KC_F6)
void__AutoFunc(KC_7, KC_F7)
void__AutoFunc(KC_8, KC_F8)
void__AutoFunc(KC_9, KC_F9)
void__AutoFunc(KC_0, KC_F10)
void__AutoFunc(KC_MINS, KC_F11)
void__AutoFunc(KC_EQL, KC_F12)
void__AutoFunc(KC_GRAVE, KC_ESC)
void__AutoFunc(KC_DEL, KC_INS)
void__AutoFunc(KC_APP, KC_PSCREEN)

enum {
 N1_F1 = 0,
 N2_F2
,N3_F3
,N4_F4
,N5_F5
,N6_F6
,N7_F7
,N8_F8
,N9_F9
,N0_F10
,MINS_F11
,EQL_F12
,G_ESC
,DEL_INS
,APP_PSCR
};

qk_tap_dance_action_t tap_dance_actions[] = {
 [N1_F1] = AutoFunc(KC_1)
,[N2_F2] = AutoFunc(KC_2)
,[N3_F3] = AutoFunc(KC_3)
,[N4_F4] = AutoFunc(KC_4)
,[N5_F5] = AutoFunc(KC_5)
,[N6_F6] = AutoFunc(KC_6)
,[N7_F7] = AutoFunc(KC_7)
,[N8_F8] = AutoFunc(KC_8)
,[N9_F9] = AutoFunc(KC_9)
,[N0_F10] = AutoFunc(KC_0)
,[MINS_F11] = AutoFunc(KC_MINS)
,[EQL_F12] = AutoFunc(KC_EQL)
,[G_ESC] = AutoFunc(KC_GRAVE)
,[DEL_INS] = AutoFunc(KC_DEL)
,[APP_PSCR] = AutoFunc(KC_APP)
};

// end tap-hold section

// start layer change section

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1: // function layer
            backlight_level(1);
            break;
        case 2: // no_macro layer
            backlight_level(1);
            break;
        default: //  default layer
            backlight_disable();
            break;
    }
  return state;
}

// end layer change section

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
   /* Layer 0: default layer 
    * 1-12 with tap-dance functionality for convenience
    * Grave tapdance to Esc
    * ,----------------------------------------------------------------.
    * |`   | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Esc |
    * |----------------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Rec1|
    * |----------------------------------------------------------------|
    * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |Stop|
    * |----------------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Ply1|
    * |----------------------------------------------------------------|
    * |Ctrl|Win |Alt |     Space/MO(1)       |Alt|A_PS|TG2|<- | Dn| -> |
    * `----------------------------------------------------------------'
    */
    
	[0] = LAYOUT_ansi( \
    TD(G_ESC), TD(N1_F1), TD(N2_F2), TD(N3_F3), TD(N4_F4), TD(N5_F5), TD(N6_F6), TD(N7_F7), TD(N8_F8), TD(N9_F9), TD(N0_F10), TD(MINS_F11), TD(EQL_F12), KC_BSPC, KC_GESC, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, DM_REC1, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, DM_RSTP, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, DM_PLY1, \
    KC_LCTL, KC_LGUI, KC_LALT, LT(1,KC_SPC), KC_RALT, TD(APP_PSCR), TG(2), KC_LEFT, KC_DOWN, KC_RGHT),
    
    
   /* Layer 1: function keys and arrow keys
    * All other keys are blank, except for modifier keys, which are transparent
    * <> Denotes transparent
    * ,----------------------------------------------------------------.
    * |   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|       |    |
    * |----------------------------------------------------------------|
    * |     |PWS|PgU|NWS|   |   |   |   |PWd| Up|NWd|   |   |     |Rec2|
    * |----------------------------------------------------------------|
    * |      |Hm |PgD| Ed|   |   |   |   |<- | Dn| ->|   |        |Stop|
    * |----------------------------------------------------------------|
    * | <>     |   |   |   |   |   |   |   |   |   |   |  <>  |   |Ply2|
    * |----------------------------------------------------------------|
    * | <> | <> | <> |            <>         |Ins|   |<> |   |   |    |
    * `----------------------------------------------------------------'
    */
    
	[1] = LAYOUT_ansi(
    KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, \
    KC_NO, LSFT(LCTL(KC_LEFT)), KC_PGUP, LSFT(LCTL(KC_RGHT)), KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_LEFT),  KC_UP, LCTL(KC_RGHT), KC_NO, KC_NO, KC_NO, DM_REC2, \
    KC_NO, KC_HOME, KC_PGDN, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, DM_RSTP, \
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, DM_PLY2, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO),

    
    /* Layer 2: gaming layer, all macros diabled
    * <> Denotes transparent
    * ,----------------------------------------------------------------.
    * |`   | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Esc |
    * |----------------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Rec1|
    * |----------------------------------------------------------------|
    * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |Stop|
    * |----------------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Ply1|
    * |----------------------------------------------------------------|
    * |Ctrl|Win |Alt |         Space         |Del|Pscr|<> |<- | Dn| -> |
    * `----------------------------------------------------------------'
    */
    
    [2] = LAYOUT_ansi( \
    KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,  KC_EQL, KC_BSPC, KC_GESC, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, DM_REC1, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, DM_RSTP, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, DM_PLY1, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_DEL, KC_PSCREEN, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
};
