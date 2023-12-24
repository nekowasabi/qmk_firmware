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

#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _O_DFT,
    _O_MOD_INPUT,
    _O_MOD,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE, // SAFE_RANGE を NG_SAFE_RANGE に変更してください
    KC_O_DFT,
    KC_O_MOD_INPUT,
    KC_O_MOD,
    KC_O_TOGGL,
    KC_O_OFF,
    KC_VIM_OFF,
    KC_WORD_LEFT,
    KC_WORD_RIGHT,
    KC_WORD_SELECT_LEFT,
    KC_WORD_SELECT_RIGHT,
};

#define XXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      JP_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_COLN, JP_RBRC,           KC_RSFT,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, JP_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_CAPS_LOCK, KC_LALT, KC_LALT,   KC_LGUI,  JP_MHEN,  KC_O_MOD,    KC_SPC,  JP_HENK, LCTL_T(KC_BSPC), KC_DEL,  LCTL_T(KC_DEL),   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  [_O_MOD] = LAYOUT(
      //,----------------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      JP_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_TAB,    KC_Q,    KC_WORD_SELECT_LEFT,    KC_WORD_SELECT_RIGHT,    KC_R,    KC_T,        KC_Y,    KC_HOME,    KC_PGUP,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_CAPS,    LSFT(KC_LEFT),    LSFT(KC_DOWN),    LSFT(KC_UP),    LSFT(KC_RIGHT),    KC_VIM_OFF,        KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT, KC_WORD_LEFT, KC_WORD_RIGHT, JP_RBRC,           KC_END,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
      KC_LSFT,    KC_Z,    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    KC_B,        KC_N,    KC_END, KC_PGDN,  KC_DOT, KC_SLSH, JP_BSLS, KC_PGDN,   KC_UP, KC_PGUP,
      //|---------+---------+---------+---------+---------+--------|   |---------+---------+---------+---------+---------+---------+---------+---------+--------|
         KC_LCTL, KC_LGUI, KC_LALT,   KC_LCTL,  KC_O_MOD_INPUT,  KC_O_MOD,    KC_SPC,  LCTL_T(KC_ENT), KC_BSPC, JP_KANA,  KC_O_TOGGL,   KC_LEFT,  KC_DOWN,  KC_RIGHT
      //`----------------------------------------------------------|   |--------------------------------------------------------------------------------'
      ),

  [_O_MOD_INPUT] = LAYOUT(
      //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_PSCR,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      JP_ZKHK,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_MINS, JP_CIRC,  JP_YEN, KC_BSPC,  KC_DEL,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_Q,    JP_YEN,    LSFT(JP_BSLS),    LSFT(KC_4),    LSFT(JP_YEN),        KC_Y,    KC_HOME,    KC_PGUP,    KC_O,    KC_P,   JP_AT, JP_LBRC,  KC_ENT, KC_HOME,
      //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,    LSFT(JP_MINS),    LSFT(KC_2),    LSFT(KC_7),    LSFT(KC_8),    LSFT(JP_LBRC),        JP_LBRC,

};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void inputEnglish(char* str) {
    register_code(KC_LCTL);
    register_code(KC_F12);
    unregister_code(KC_F12);
    unregister_code(KC_LCTL);
    send_string(str);
    register_code(KC_LSFT);
    register_code(KC_F11);
    unregister_code(KC_F11);
    unregister_code(KC_LSFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL << _QWERTY);
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
        case KC_WORD_SELECT_LEFT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case KC_WORD_LEFT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case KC_WORD_RIGHT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
    }

    return true;
}
