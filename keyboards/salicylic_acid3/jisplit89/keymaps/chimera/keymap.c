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
  _TK_E, // 5 英語
  _TK_W, // 6 仕事用語
  _TK_H, // 7 人称 
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

  TK_E_Q,
  TK_E_W,
  TK_E_E,
  TK_E_R,
  TK_E_T,
  TK_E_Y,
  TK_E_U,
  TK_E_I,
  TK_E_O,
  TK_E_P,
  TK_E_A,
  TK_E_S,
  TK_E_D,
  TK_E_F,
  TK_E_G,
  TK_E_H,
  TK_E_J,
  TK_E_K,
  TK_E_L,
  TK_E_SCLN,
  TK_E_Z,
  TK_E_X,
  TK_E_C,
  TK_E_V,
  TK_E_B,
  TK_E_N,
  TK_E_M,
  TK_E_COMM,
  TK_E_DOT,
  TK_E_SLSH,
  TK_E_1,
  TK_E_2,
  TK_E_3,
  TK_E_4,
  TK_E_5,
  TK_E_6,
  TK_E_7,
  TK_E_8,
  TK_E_9,
  TK_E_0,
  TK_E_AT,
  TK_E_LBRC,
  TK_E_COLN,
  TK_E_RBRC,
  TK_E_BSLS,

  TK_W_Q,
  TK_W_W,
  TK_W_E,
  TK_W_R,
  TK_W_T,
  TK_W_Y,
  TK_W_U,
  TK_W_I,
  TK_W_O,
  TK_W_P,
  TK_W_A,
  TK_W_S,
  TK_W_D,
  TK_W_F,
  TK_W_G,
  TK_W_H,
  TK_W_J,
  TK_W_K,
  TK_W_L,
  TK_W_SCLN,
  TK_W_Z,
  TK_W_X,
  TK_W_C,
  TK_W_V,
  TK_W_B,
  TK_W_N,
  TK_W_M,
  TK_W_COMM,
  TK_W_DOT,
  TK_W_SLSH,
  TK_W_1,
  TK_W_2,
  TK_W_3,
  TK_W_4,
  TK_W_5,
  TK_W_6,
  TK_W_7,
  TK_W_8,
  TK_W_9,
  TK_W_0,
  TK_W_AT,
  TK_W_LBRC,
  TK_W_COLN,
  TK_W_RBRC,
  TK_W_BSLS,

  TK_H_Q,
  TK_H_W,
  TK_H_E,
  TK_H_R,
  TK_H_T,
  TK_H_Y,
  TK_H_U,
  TK_H_I,
  TK_H_O,
  TK_H_P,
  TK_H_A,
  TK_H_S,
  TK_H_D,
  TK_H_F,
  TK_H_G,
  TK_H_H,
  TK_H_J,
  TK_H_K,
  TK_H_L,
  TK_H_SCLN,
  TK_H_Z,
  TK_H_X,
  TK_H_C,
  TK_H_V,
  TK_H_B,
  TK_H_N,
  TK_H_M,
  TK_H_COMM,
  TK_H_DOT,
  TK_H_SLSH,
  TK_H_1,
  TK_H_2,
  TK_H_3,
  TK_H_4,
  TK_H_5,
  TK_H_6,
  TK_H_7,
  TK_H_8,
  TK_H_9,
  TK_H_0,
  TK_H_AT,
  TK_H_LBRC,
  TK_H_COLN,
  TK_H_RBRC,
  TK_H_BSLS,
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

  // 英語・English
  [_TK_E] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  TK_E_1,  TK_E_2,    TK_E_3,    TK_E_4,    TK_E_5,        TK_E_6,    TK_E_7,    TK_E_8,    TK_E_9,    TK_E_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    TK_E_Q,    TK_E_W,    TK_E_E,    TK_E_R,    TK_E_T,        TK_E_Y,    TK_E_U,    TK_E_I,    TK_E_O,    TK_E_P,   TK_E_AT, TK_E_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    TK_E_A,    TK_E_S,    TK_E_D,    TK_E_F,    TK_E_G,        TK_E_H,    TK_E_J,    TK_E_K,    TK_E_L, TK_E_SCLN, TK_E_COLN, TK_E_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    TK_E_Z,    TK_E_X,    TK_E_C,    TK_E_V,    TK_E_B,        TK_E_N,    TK_E_M, TK_E_COMM,  TK_E_DOT, TK_E_SLSH, TK_E_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTRL, KC_LGUI, KC_LALT,   KC_LCTRL,  KC_O_MOD_INPUT,  KC_O_MOD,    KC_SPC,  LCTL_T(KC_ENT), KC_BSPC, KC_KANA,  KC_O_TOGGL,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  // 仕事用語
  [_TK_W] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  TK_W_1,  TK_W_2,    TK_W_3,    TK_W_4,    TK_W_5,        TK_W_6,    TK_W_7,    TK_W_8,    TK_W_9,    TK_W_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    TK_W_Q,    TK_W_W,    TK_W_E,    TK_W_R,    TK_W_T,        TK_W_Y,    TK_W_U,    TK_W_I,    TK_W_O,    TK_W_P,   TK_W_AT, TK_W_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    TK_W_A,    TK_W_S,    TK_W_D,    TK_W_F,    TK_W_G,        TK_W_H,    TK_W_J,    TK_W_K,    TK_W_L, TK_W_SCLN, TK_W_COLN, TK_W_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    TK_W_Z,    TK_W_X,    TK_W_C,    TK_W_V,    TK_W_B,        TK_W_N,    TK_W_M, TK_W_COMM,  TK_W_DOT, TK_W_SLSH, TK_W_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTRL, KC_LGUI, KC_LALT,   KC_LCTRL,  KC_O_MOD_INPUT,  KC_O_MOD,    KC_SPC,  LCTL_T(KC_ENT), KC_BSPC, KC_KANA,  KC_O_TOGGL,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  // 人称
  [_TK_H] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_ZKHK,  TK_H_1,  TK_H_2,    TK_H_3,    TK_H_4,    TK_H_5,        TK_H_6,    TK_H_7,    TK_H_8,    TK_H_9,    TK_H_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    TK_H_Q,    TK_H_W,    TK_H_E,    TK_H_R,    TK_H_T,        TK_H_Y,    TK_H_U,    TK_H_I,    TK_H_O,    TK_H_P,   TK_H_AT, TK_H_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    TK_H_A,    TK_H_S,    TK_H_D,    TK_H_F,    TK_H_G,        TK_H_H,    TK_H_J,    TK_H_K,    TK_H_L, TK_H_SCLN, TK_H_COLN, TK_H_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    TK_H_Z,    TK_H_X,    TK_H_C,    TK_H_V,    TK_H_B,        TK_H_N,    TK_H_M, TK_H_COMM,  TK_H_DOT, TK_H_SLSH, TK_H_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
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

    // case MOD_:
    //   if (record->event.pressed) {
    //     nicola_on();
    //     // tap_code(KC_ZKHK);
    //   }
    //   return false;
    //   break;
    // 
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
        send_string("tyekku");
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
        // send_string("nakaguro");
        send_string("nkgr");
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
        send_string("itasi");
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
        SEND_STRING("dekiruyouni");
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

    // 月配列（E）
    case TK_E_A:
      if (record->event.pressed) {
        send_string("konnnitiha");
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_B:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_C:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_D:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_E:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_F:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_G:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_H:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_I:
      if (record->event.pressed) {
        send_string("itada");
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_J:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_K:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_L:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_M:
      if (record->event.pressed) {
        send_string("makako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_N:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_O:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_P:
      if (record->event.pressed) {
        send_string("nakaguro");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_Q:
      if (record->event.pressed) {
        SEND_STRING("bo" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_R:
      if (record->event.pressed) {
        inputEnglish("RTM");
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_S:
      if (record->event.pressed) {
        send_string("su");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_T:
      if (record->event.pressed) {
        SEND_STRING("ten" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_U:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_V:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_W:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_X:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_Y:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_Z:
      if (record->event.pressed) {
        send_string("pa");
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_1:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_2:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_3:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_4:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_5:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_6:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_7:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_8:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_9:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_0:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_AT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_LBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_SCLN:
      if (record->event.pressed) {
        send_string("ikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_COLN:
      if (record->event.pressed) {
        send_string("nikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_RBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_COMM:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_DOT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_SLSH:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;
    case TK_E_BSLS:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_E);
      }
      return false;
      break;

    // 仕事用語（W）
    case TK_W_A:
      if (record->event.pressed) {
        send_string("konnnitiha");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_B:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_C:
      if (record->event.pressed) {
        send_string("ko-dorebyu-");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_D:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_E:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_F:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_G:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_H:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_I:
      if (record->event.pressed) {
        send_string("itada");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_J:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_K:
      if (record->event.pressed) {
        send_string("kiridasi");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_L:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_M:
      if (record->event.pressed) {
        send_string("makako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_N:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_O:
      if (record->event.pressed) {
        send_string("otukaresamadesu");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_P:
      if (record->event.pressed) {
        send_string("nakaguro");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_Q:
      if (record->event.pressed) {
        SEND_STRING("bo" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_R:
      if (record->event.pressed) {
        inputEnglish("RTM");
        // register_code(KC_LCTRL);
        // register_code(KC_F12);
        // unregister_code(KC_F12);
        // unregister_code(KC_LCTRL);
        // send_string("RTM");
        // register_code(KC_LSFT);
        // register_code(KC_F11);
        // unregister_code(KC_F11);
        // unregister_code(KC_LSFT);
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_S:
      if (record->event.pressed) {
        send_string("su");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_T:
      if (record->event.pressed) {
        SEND_STRING("ten" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_U:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_V:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_W:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_X:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_Y:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_Z:
      if (record->event.pressed) {
        send_string("pa");
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_1:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_2:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_3:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_4:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_5:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_6:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_7:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_8:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_9:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_0:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_AT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_LBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_SCLN:
      if (record->event.pressed) {
        send_string("ikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_COLN:
      if (record->event.pressed) {
        send_string("nikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_RBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_COMM:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_DOT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_SLSH:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;
    case TK_W_BSLS:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_W);
      }
      return false;
      break;

    // 仕事用語（H）
    case TK_H_A:
      if (record->event.pressed) {
        send_string("konnnitiha");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_B:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_C:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_D:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_E:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_F:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_G:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_H:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_I:
      if (record->event.pressed) {
        send_string("itada");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_J:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_K:
      if (record->event.pressed) {
        send_string("kiridasi");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_L:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_M:
      if (record->event.pressed) {
        send_string("makako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_N:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_O:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_P:
      if (record->event.pressed) {
        send_string("nakaguro");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_Q:
      if (record->event.pressed) {
        SEND_STRING("bo" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_R:
      if (record->event.pressed) {
        inputEnglish("RTM");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_S:
      if (record->event.pressed) {
        send_string("su");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_T:
      if (record->event.pressed) {
        SEND_STRING("ten" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_U:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_V:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_W:
      if (record->event.pressed) {
        send_string("watasi");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_X:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_Y:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_Z:
      if (record->event.pressed) {
        send_string("pa");
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_1:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_2:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_3:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_4:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_5:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_6:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_7:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_8:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_9:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_0:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_AT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_LBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_SCLN:
      if (record->event.pressed) {
        send_string("ikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_COLN:
      if (record->event.pressed) {
        send_string("nikako");
        SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_RBRC:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_COMM:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_DOT:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_SLSH:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
      }
      return false;
      break;
    case TK_H_BSLS:
      if (record->event.pressed) {
      } else {
        layer_off(_TK_H);
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
