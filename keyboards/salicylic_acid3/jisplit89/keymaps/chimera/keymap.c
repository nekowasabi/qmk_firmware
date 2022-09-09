/*
   Copyright 2022 takets

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

#include "keycode.h"
#include "keycode_legacy.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

#include "nicola.h"
NGKEYS nicola_keys;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _O_DFT,
  _O_MOD_INPUT,
  _O_MOD,
  _TK_LFT,
};

enum custom_keycodes {
  // NICOLA親指シフト
  KC_QWERTY = NG_SAFE_RANGE, // SAFE_RANGE を NG_SAFE_RANGE に変更してください
  KC_O_DFT,
  KC_O_MOD_INPUT,
  KC_O_MOD,
  KC_O_TOGGL,
  KC_O_OFF,
  KC_VIM_OFF,
  KC_WORD_LEFT,
  KC_WORD_RIGHT,

  TK_LFT_Q,
  TK_LFT_W,
  TK_LFT_E,
  TK_LFT_R,
  TK_LFT_T,
  TK_LFT_Y,
  TK_LFT_U,
  TK_LFT_I,
  TK_LFT_O,
  TK_LFT_P,
  TK_LFT_A,
  TK_LFT_S,
  TK_LFT_D,
  TK_LFT_F,
  TK_LFT_G,
  TK_LFT_H,
  TK_LFT_J,
  TK_LFT_K,
  TK_LFT_L,
  TK_LFT_SCLN,
  TK_LFT_Z,
  TK_LFT_X,
  TK_LFT_C,
  TK_LFT_V,
  TK_LFT_B,
  TK_LFT_N,
  TK_LFT_M,
  TK_LFT_COMM,
  TK_LFT_DOT,
  TK_LFT_SLSH,
  TK_LFT_1,
  TK_LFT_2,
  TK_LFT_3,
  TK_LFT_4,
  TK_LFT_5,
  TK_LFT_6,
  TK_LFT_7,
  TK_LFT_8,
  TK_LFT_9,
  TK_LFT_0,
  TK_LFT_AT,
  TK_LFT_LBRC,
  TK_LFT_COLN,
  TK_LFT_RBRC,
  TK_LFT_BSLS,
};

#define XXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_O_TOGGL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_COLN, JP_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, JP_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTRL, KC_LGUI, KC_LCTRL,   LALT_T(KC_DEL),  KC_O_MOD_INPUT,  KC_O_MOD,    LSFT_T(KC_SPC),  LCTL_T(KC_ENT), KC_BSPC, KC_DEL,  KC_O_OFF,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),
 
  [_O_DFT] = LAYOUT(
      //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_ZKHK,  NG_1,  NG_2,    NG_3,    NG_4,    NG_5,        NG_6,    NG_7,    NG_8,    NG_9,    NG_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,   NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,        NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,   NG_AT, NG_LBRC,  KC_ENT, KC_HOME,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_O_OFF,   NG_A,    NG_S,    NG_D,    NG_F,    NG_G,        NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, NG_COLN, NG_RBRC,           KC_END,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,   OSL(_TK_LFT),    NG_X,    NG_C,    NG_V,    NG_B,        NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, NG_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL, KC_LGUI, KC_LALT,   KC_LCTRL,  NG_SHFTL, KC_O_MOD, NG_SHFTR,  LCTL_T(KC_ENT), KC_BSPC, KC_DEL,  KC_O_OFF,          KC_LEFT, KC_DOWN,KC_RIGHT
      //`-----------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  [_O_MOD_INPUT] = LAYOUT(
      //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_Q,    JP_YEN,    LSFT(JP_BSLS),    LSFT(KC_4),    KC_T,        KC_Y,    KC_HOME,    KC_PGUP,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,    LSFT(JP_MINS),    LSFT(KC_2),    LSFT(KC_7),    LSFT(KC_8),    LSFT(JP_LBRC),        JP_LBRC,    JP_MINS,    KC_UP,    KC_RIGHT, JP_SCLN, JP_COLN, JP_RBRC,           KC_END,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_LSFT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7, KC_8,  KC_9, KC_0, JP_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL, KC_LGUI, KC_LALT, KC_LCTRL,  KC_O_MOD_INPUT,   KC_O_MOD,      KC_SPC,  KC_HENK, KC_KANA, KC_KANA,  KC_APP,          KC_LEFT, KC_DOWN,KC_RIGHT
      //`-----------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  [_O_MOD] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_HOME,    KC_PGUP,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    LSFT(KC_LEFT),    LSFT(KC_DOWN),    LSFT(KC_UP),    LSFT(KC_RIGHT),    KC_VIM_OFF,        KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT, KC_WORD_LEFT, KC_WORD_RIGHT, JP_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    KC_Z,    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    KC_B,        KC_N,    KC_END, KC_PGDN,  KC_DOT, KC_SLSH, JP_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTRL, KC_LGUI, KC_LALT,   KC_LCTRL,  KC_O_MOD_INPUT,  KC_O_MOD,    KC_SPC,  LCTL_T(KC_ENT), KC_BSPC, KC_KANA,  KC_O_TOGGL,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),



  [_TK_LFT] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  TK_LFT_1,  TK_LFT_2,    TK_LFT_3,    TK_LFT_4,    TK_LFT_5,        TK_LFT_6,    TK_LFT_7,    TK_LFT_8,    TK_LFT_9,    TK_LFT_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    TK_LFT_Q,    TK_LFT_W,    TK_LFT_E,    TK_LFT_R,    TK_LFT_T,        TK_LFT_Y,    TK_LFT_U,    TK_LFT_I,    TK_LFT_O,    TK_LFT_P,   TK_LFT_AT, TK_LFT_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    TK_LFT_A,    TK_LFT_S,    TK_LFT_D,    TK_LFT_F,    TK_LFT_G,        TK_LFT_H,    TK_LFT_J,    TK_LFT_K,    TK_LFT_L, TK_LFT_SCLN, TK_LFT_COLN, TK_LFT_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    TK_LFT_Z,    TK_LFT_X,    TK_LFT_C,    TK_LFT_V,    TK_LFT_B,        TK_LFT_N,    TK_LFT_M, TK_LFT_COMM,  TK_LFT_DOT, TK_LFT_SLSH, TK_LFT_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTRL, KC_LGUI, KC_LALT,   KC_LCTRL,  KC_O_MOD_INPUT,  KC_O_MOD,    KC_SPC,  LCTL_T(KC_ENT), KC_BSPC, KC_KANA,  KC_O_TOGGL,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  set_nicola(_O_DFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_O_MOD:
      if (record->event.pressed) {
        layer_on(_O_MOD);
      } else {
        layer_off(_O_MOD);
      }
      return false;
      break;
    case KC_O_MOD_INPUT:
      if (record->event.pressed) {
        layer_on(_O_MOD_INPUT);
      } else {
        layer_off(_O_MOD_INPUT);
      }
      return false;
      break;
    case KC_O_DFT:
      if (record->event.pressed) {
        nicola_on();
        // tap_code(KC_ZKHK);
      }
      return false;
      break;
    case KC_O_TOGGL:
      if (record->event.pressed) {
        if (nicola_state() == true) {
          nicola_off();
          register_code(KC_LCTRL);
          register_code(KC_F12);
          unregister_code(KC_F12);
          unregister_code(KC_LCTRL);
        } else {
          nicola_on();
          register_code(KC_LSFT);
          register_code(KC_F11);
          unregister_code(KC_F11);
          unregister_code(KC_LSFT);
        }
      }
      return false;
      break;

    case KC_O_OFF:
      if (record->event.pressed) {
        nicola_off();
        register_code(KC_LCTRL);
        register_code(KC_F12);
        unregister_code(KC_F12);
        unregister_code(KC_LCTRL);
      }
      return false;
      break;
    case KC_VIM_OFF:
      if (record->event.pressed) {
        nicola_off();
        register_code(KC_ESC);
        unregister_code(KC_ESC);
        register_code(KC_LCTRL);
        register_code(KC_F12);
        unregister_code(KC_F12);
        unregister_code(KC_LCTRL);
      }
      return false;
      break;
    case KC_WORD_LEFT:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LCTRL);
      }
      return false;
      break;
    case KC_WORD_RIGHT:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LCTRL);
      }
      return false;
      break;

    case TK_LFT_A:
      if (record->event.pressed) {
        send_string("ohayou");
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_B:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_C:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_D:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_E:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_F:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_G:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_H:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_I:
      if (record->event.pressed) {
        send_string("itada");
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_J:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_K:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_L:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_M:
      if (record->event.pressed) {
        send_string("makako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_N:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_O:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_P:
      if (record->event.pressed) {
        send_string("nakaguro");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_Q:
      if (record->event.pressed) {
        SEND_STRING("bo" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_R:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_S:
      if (record->event.pressed) {
        send_string("su");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_T:
      if (record->event.pressed) {
        SEND_STRING("ten" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_U:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_V:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_W:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_X:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_Y:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_Z:
      if (record->event.pressed) {
        send_string("pa");
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_1:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_2:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_3:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_4:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_5:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_6:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_7:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_8:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_9:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_0:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_AT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_LBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_SCLN:
      if (record->event.pressed) {
        send_string("ikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_COLN:
      if (record->event.pressed) {
        send_string("nikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_RBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_COMM:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_DOT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_SLSH:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
    case TK_LFT_BSLS:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_LFT);
      }
      return false;
      break;
  }

  bool a = true;
  if (nicola_state()) {
    process_modifier(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;

  return true;
}

