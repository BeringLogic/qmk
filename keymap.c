/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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



#include QMK_KEYBOARD_H
#include "users/holykeebs/holykeebs.h"
#include "keymap_canadian_french.h"
#include "sendstring_canadian_french.h"

#define QK_C_EEPROM QK_CLEAR_EEPROM

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
    F_SHIFT_CAPSLOCK,
};

td_state_t cur_dance(tap_dance_state_t *state);

void f_finished(tap_dance_state_t *state, void *user_data);
void f_reset(tap_dance_state_t *state, void *user_data);

// Macros
enum custom_keycodes {
    M_MAKE = SAFE_RANGE,
    M_FLASH,
};

// https://docs.qmk.fm/feature_macros
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_MAKE:
        if (record->event.pressed) {
            SEND_STRING("qmk compile -j 20" SS_TAP(X_ENTER));
        }
        break;
    case M_FLASH:
        if (record->event.pressed) {
           SEND_STRING("qmk flash && qmk flash" SS_TAP(X_ENTER));
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------------.                    ,------------------------------------------------------------------------.
       KC_TAB,        KC_Q,        KC_W,        KC_E,                KC_R,    KC_T,                         KC_Y,        KC_U,        KC_I,        KC_O,           KC_P, KC_BSPC,
  //|--------+------------+------------+------------+--------------------+--------|                    |--------+------------+------------+------------+---------------+--------|
       KC_ESC,LGUI_T(KC_A),LALT_T(KC_S),LCTL_T(KC_D),TD(F_SHIFT_CAPSLOCK),    KC_G,                         KC_H,RSFT_T(KC_J),RCTL_T(KC_K),LALT_T(KC_L),RGUI_T(KC_SCLN), KC_INS,
  //|--------+------------+------------+------------+--------------------+--------|                    |--------+------------+------------+------------+---------------+--------|
      KC_LSFT,        KC_Z,        KC_X,        KC_C,                KC_V,    KC_B,                         KC_N,        KC_M,     KC_COMM,      KC_DOT,        KC_SLSH,  KC_DEL,
  //|--------+------------+------------+------------+--------------------+--------+--------|  |--------+--------+------------+------------+------------+---------------+--------|
                                                                    MO(4), TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR,       MO(5)
                                                  //`--------------------------------------'  `------------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LCTL,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_LSFT,                         KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      FR_HASH, FR_EXLM, FR_DQUO, FR_SLSH,  FR_DLR, FR_PERC,                      FR_QUES, FR_AMPR, FR_LPRN, FR_RPRN, FR_ASTR, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      FR_TILD,   FR_AT, FR_QUOT, FR_BSLS, FR_CENT,  FR_DEG,                      KC_MINS,  KC_EQL, FR_LBRC, FR_RBRC, FR_LABK, FR_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      FR_UNDS, FR_PLUS, FR_LCBR, FR_RCBR, FR_RABK,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                   ,-------------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                     KC_WAKE, XXXXXXX, XXXXXXX, XXXXXXX,   KC_PSCR, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+----------+--------|
      XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                     KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX,A(KC_PSCR),  EE_CLR,
  //|--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+----------+--------|
      XXXXXXX, XXXXXXX, UG_TOGG, UG_VALD, UG_VALU, UG_NEXT,                      KC_PWR, XXXXXXX, XXXXXXX, XXXXXXX,C(KC_PSCR),  QK_RBT,
  //|--------+--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+----------+--------|
                                          XXXXXXX, _______,  KC_SPC,    KC_ENT, _______, XXXXXXX
                                      //`--------------------------' `--------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       M_MAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      M_FLASH, _______, _______, _______, _______, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  KC_END, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,  KC_SPC,     KC_ENT, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, FR_DCIR, FR_CEDL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, _______, _______, _______, _______, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_DGRV, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,  KC_SPC,     KC_ENT, XXXXXXX, _______
                                      //`--------------------------'  `--------------------------'
  ),

  /* [3] = LAYOUT_split_3x6_3( */
  /* //,------------------------------------------------------------------------------.                   ,-----------------------------------------------------------------------------. */
  /*         QK_BOOT,     HK_DUMP,     HK_SAVE,     HK_RESET,     XXXXXXX, HK_C_SCROLL,                         XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     QK_BOOT, */
  /* //|------------+------------+------------+-------------+------------+------------|                   |------------+------------+------------+------------+------------+------------| */
  /*     QK_C_EEPROM,  HK_P_SET_D,  HK_P_SET_S, HK_P_SET_BUF,     XXXXXXX, HK_S_MODE_T,                           KC_UP,     KC_DOWN,     XXXXXXX,     XXXXXXX,     XXXXXXX, QK_C_EEPROM, */
  /* //|------------+------------+------------+-------------+------------+------------|                   |------------+------------+------------+------------+------------+------------| */
  /*         KC_LSFT,     XXXXXXX,     XXXXXXX,      XXXXXXX,     XXXXXXX, HK_D_MODE_T,                         XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX, */
  /* //|------------+------------+------------+-------------+------------+------------+--------| |--------+------------+------------+------------+------------+------------+------------| */
  /*                                                                MO(4),     _______,  KC_SPC,    KC_ENT,     _______,       MO(5) */
  /*                                                      //`----------------------------------' `----------------------------------' */
  /* ) */
};

// https://docs.qmk.fm/features/tap_dance
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

// Create an instance of 'td_tap_t' for the 'f' tap dance.
static td_tap_t ftap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void f_finished(tap_dance_state_t *state, void *user_data) {
    ftap_state.state = cur_dance(state);
    switch (ftap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_F); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_HOLD: register_code(KC_CAPS); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_F); register_code(KC_F); break;
        default: break;
    }
}

void f_reset(tap_dance_state_t *state, void *user_data) {
    switch (ftap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_F); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_CAPS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_F); break;
        default: break;
    }
    ftap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [F_SHIFT_CAPSLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset)
};

