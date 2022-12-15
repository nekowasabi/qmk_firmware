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

#include <stdint.h>
#include "keycode.h"
#include "keycode_legacy.h"
#include "quantum_keycodes.h"
#include "keymap_japanese.h"
#include "nicola.h"

#include QMK_KEYBOARD_H
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
  _TK_RGT,
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

  TK_RGT_Q,
  TK_RGT_W,
  TK_RGT_E,
  TK_RGT_R,
  TK_RGT_T,
  TK_RGT_Y,
  TK_RGT_U,
  TK_RGT_I,
  TK_RGT_O,
  TK_RGT_P,
  TK_RGT_A,
  TK_RGT_S,
  TK_RGT_D,
  TK_RGT_F,
  TK_RGT_G,
  TK_RGT_H,
  TK_RGT_J,
  TK_RGT_K,
  TK_RGT_L,
  TK_RGT_SCLN,
  TK_RGT_Z,
  TK_RGT_X,
  TK_RGT_C,
  TK_RGT_V,
  TK_RGT_B,
  TK_RGT_N,
  TK_RGT_M,
  TK_RGT_COMM,
  TK_RGT_DOT,
  TK_RGT_SLSH,
  TK_RGT_1,
  TK_RGT_2,
  TK_RGT_3,
  TK_RGT_4,
  TK_RGT_5,
  TK_RGT_6,
  TK_RGT_7,
  TK_RGT_8,
  TK_RGT_9,
  TK_RGT_0,
  TK_RGT_AT,
  TK_RGT_LBRC,
  TK_RGT_COLN,
  TK_RGT_RBRC,
  TK_RGT_BSLS,
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
         KC_LCTRL, KC_LGUI, KC_LCTRL,   KC_LALT,  KC_O_MOD_INPUT,  KC_O_MOD,    LSFT_T(KC_SPC),  LCTL_T(KC_ENT), KC_BSPC, KC_DEL,  KC_O_OFF,   KC_LEFT,  KC_DOWN,  KC_RIGHT
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
      KC_LSFT,   NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,        NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, NG_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
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
      KC_TAB,    KC_Q,    JP_YEN,    LSFT(JP_BSLS),    LSFT(KC_4),    LSFT(JP_YEN),        KC_Y,    KC_HOME,    KC_PGUP,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,    LSFT(JP_MINS),    LSFT(KC_2),    LSFT(KC_7),    LSFT(KC_8),    LSFT(JP_LBRC),        JP_LBRC,    JP_MINS,    JP_CIRC,    JP_CIRC, JP_SCLN, JP_COLN, JP_RBRC,           KC_END,
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
      ),

  [_TK_RGT] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  TK_RGT_1,  TK_RGT_2,    TK_RGT_3,    TK_RGT_4,    TK_RGT_5,        TK_RGT_6,    TK_RGT_7,    TK_RGT_8,    TK_RGT_9,    TK_RGT_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    TK_RGT_Q,    TK_RGT_W,    TK_RGT_E,    TK_RGT_R,    TK_RGT_T,        TK_RGT_Y,    TK_RGT_U,    TK_RGT_I,    TK_RGT_O,    TK_RGT_P,   TK_RGT_AT, TK_RGT_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    TK_RGT_A,    TK_RGT_S,    TK_RGT_D,    TK_RGT_F,    TK_RGT_G,        TK_RGT_H,    TK_RGT_J,    TK_RGT_K,    TK_RGT_L, TK_RGT_SCLN, TK_RGT_COLN, TK_RGT_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    TK_RGT_Z,    TK_RGT_X,    TK_RGT_C,    TK_RGT_V,    TK_RGT_B,        TK_RGT_N,    TK_RGT_M, TK_RGT_COMM,  TK_RGT_DOT, TK_RGT_SLSH, TK_RGT_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
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

void inputEnglish(char* str) {
  register_code(KC_LCTRL);
  register_code(KC_F12);
  unregister_code(KC_F12);
  unregister_code(KC_LCTRL);
  send_string(str);
  register_code(KC_LSFT);
  register_code(KC_F11);
  unregister_code(KC_F11);
  unregister_code(KC_LSFT);
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
          register_code(KC_LCTRL);
          register_code(KC_F11);
          unregister_code(KC_F11);
          unregister_code(KC_LCTRL);
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

    case TK_LFT_Q ... TK_LFT_BSLS:
      if (record->event.pressed) {
        if (keycode == TK_LFT_H) send_string("hrkr");
        if (keycode == TK_LFT_I) send_string("itada");
        if (keycode == TK_LFT_O) send_string("qngq"); // おねがい
        if (keycode == TK_LFT_P) send_string("itasi");
        if (keycode == TK_LFT_Q) {
        }
        if (keycode == TK_LFT_S) send_string("sprt");
        if (keycode == TK_LFT_T) send_string("tyekku");
     if (keycode == TK_LFT_Y) send_string("dekiruyouni");
        if (keycode == TK_LFT_Z) send_string("pa");
        if (keycode == TK_LFT_SCLN) {
        }
        if (keycode == TK_LFT_COLN) {
        }
        layer_off(_TK_LFT);
      } else {
        layer_off(_TK_LFT);
      }
      nicola_clear();
      return false;
      break;
    case TK_RGT_Q ... TK_RGT_BSLS:
      if (record->event.pressed) {
        if (keycode == TK_RGT_BSLS) send_string("rasii");
        layer_off(_TK_RGT);
      } else {
        layer_off(_TK_RGT);
      }
      nicola_clear();
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
