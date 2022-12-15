/* Copyright 2018-2019 eswai <@eswai>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "action_util.h"
#include QMK_KEYBOARD_H
#include "nicola.h"
#include <unistd.h>

#define NGBUFFER 30 // バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキー含む)
static bool is_nicola = false; // 親指シフトがオンかオフか
static uint8_t nicola_layer = 0; // レイヤー番号
static uint64_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

// 31キーを32bitの各ビットに割り当てる
#define B_Q    (1ULL<<0)
#define B_W    (1ULL<<1)
#define B_E    (1ULL<<2)
#define B_R    (1ULL<<3)
#define B_T    (1ULL<<4)

#define B_Y    (1ULL<<5)
#define B_U    (1ULL<<6)
#define B_I    (1ULL<<7)
#define B_O    (1ULL<<8)
#define B_P    (1ULL<<9)

#define B_A    (1ULL<<10)
#define B_S    (1ULL<<11)
#define B_D    (1ULL<<12)
#define B_F    (1ULL<<13)
#define B_G    (1ULL<<14)

#define B_H    (1ULL<<15)
#define B_J    (1ULL<<16)
#define B_K    (1ULL<<17)
#define B_L    (1ULL<<18)
#define B_SCLN (1ULL<<19)

#define B_Z    (1ULL<<20)
#define B_X    (1ULL<<21)
#define B_C    (1ULL<<22)
#define B_V    (1ULL<<23)
#define B_B    (1ULL<<24)

#define B_N    (1ULL<<25)
#define B_M    (1ULL<<26)
#define B_COMM (1ULL<<27)
#define B_DOT  (1ULL<<28)
#define B_SLSH (1ULL<<29)

#define B_1    (1ULL<<30)
#define B_2    (1ULL<<31)
#define B_3    (1ULL<<32)
#define B_4    (1ULL<<33)
#define B_5    (1ULL<<34)
#define B_6    (1ULL<<35)
#define B_7    (1ULL<<36)
#define B_8    (1ULL<<37)
#define B_9    (1ULL<<38)
#define B_0    (1ULL<<39)

#define B_AT   (1ULL<<40)
#define B_LBRC (1ULL<<41)
#define B_COLN (1ULL<<42)
#define B_RBRC (1ULL<<43)
#define B_BSLS (1ULL<<44)

#define B_SHFTL (1ULL<<45)
#define B_SHFTR (1ULL<<46)


// 文字入力バッファ
static uint16_t ninputs[NGBUFFER];

// キーコードとキービットの対応
// メモリ削減のため配列はNG_Qを0にしている
const uint64_t ng_key[] = {
  [NG_Q    - NG_Q] = B_Q,
  [NG_W    - NG_Q] = B_W,
  [NG_E    - NG_Q] = B_E,
  [NG_R    - NG_Q] = B_R,
  [NG_T    - NG_Q] = B_T,

  [NG_Y    - NG_Q] = B_Y,
  [NG_U    - NG_Q] = B_U,
  [NG_I    - NG_Q] = B_I,
  [NG_O    - NG_Q] = B_O,
  [NG_P    - NG_Q] = B_P,

  [NG_A    - NG_Q] = B_A,
  [NG_S    - NG_Q] = B_S,
  [NG_D    - NG_Q] = B_D,
  [NG_F    - NG_Q] = B_F,
  [NG_G    - NG_Q] = B_G,

  [NG_H    - NG_Q] = B_H,
  [NG_J    - NG_Q] = B_J,
  [NG_K    - NG_Q] = B_K,
  [NG_L    - NG_Q] = B_L,
  [NG_SCLN - NG_Q] = B_SCLN,

  [NG_Z    - NG_Q] = B_Z,
  [NG_X    - NG_Q] = B_X,
  [NG_C    - NG_Q] = B_C,
  [NG_V    - NG_Q] = B_V,
  [NG_B    - NG_Q] = B_B,

  [NG_N    - NG_Q] = B_N,
  [NG_M    - NG_Q] = B_M,
  [NG_COMM - NG_Q] = B_COMM,
  [NG_DOT  - NG_Q] = B_DOT,
  [NG_SLSH - NG_Q] = B_SLSH,

  [NG_1    - NG_Q] = B_1,
  [NG_2    - NG_Q] = B_2,
  [NG_3    - NG_Q] = B_3,
  [NG_4    - NG_Q] = B_4,
  [NG_5    - NG_Q] = B_5,
  [NG_6    - NG_Q] = B_6,
  [NG_7    - NG_Q] = B_7,
  [NG_8    - NG_Q] = B_8,
  [NG_9    - NG_Q] = B_9,
  [NG_0    - NG_Q] = B_0,

  [NG_AT   - NG_Q] = B_AT,
  [NG_LBRC - NG_Q] = B_LBRC,
  [NG_COLN - NG_Q] = B_COLN,
  [NG_RBRC - NG_Q] = B_RBRC,
  [NG_BSLS - NG_Q] = B_BSLS,

  [NG_SHFTL - NG_Q] = B_SHFTL,
  [NG_SHFTR - NG_Q] = B_SHFTR,
};

// 親指シフトカナ変換テーブル
typedef struct {
  uint64_t key;
  char kana[10];
} nicola_keymap;

const PROGMEM nicola_keymap ngmap[] = {
  // 同時
  {.key = B_A|B_9           , .kana = "atari"},
  {.key = B_A|B_Y           , .kana = "atte"},
  {.key = B_A|B_U           , .kana = "atta"},
  {.key = B_A|B_I           , .kana = "ari"},
  {.key = B_A|B_O           , .kana = "ori"},
  {.key = B_A|B_P           , .kana = "ato"},
  {.key = B_A|B_AT          , .kana = "are"},
  {.key = B_A|B_H           , .kana = "au"},
  {.key = B_A|B_J           , .kana = "aru"},
  {.key = B_A|B_L           , .kana = "juu"},
  {.key = B_A|B_SCLN        , .kana = "jou"},
  {.key = B_A|B_COLN        , .kana = "ano"},
  {.key = B_A|B_COMM        , .kana = "simatta"},
  {.key = B_A|B_DOT         , .kana = "simatte"},

  {.key = B_C|B_V           , .kana = "youni"},

  {.key = B_D|B_7           , .kana = "simai"},
  {.key = B_D|B_8           , .kana = "yuru"},
  {.key = B_D|B_9           , .kana = "dekireba"},
  {.key = B_D|B_0           , .kana = "dekinai"},
  {.key = B_D|B_Y           , .kana = "datte"},
  {.key = B_D|B_U           , .kana = "dou"},
  {.key = B_D|B_I           , .kana = "dasu"},
  {.key = B_D|B_O           , .kana = "darou"},
  {.key = B_D|B_P           , .kana = "dake"},
  {.key = B_D|B_AT          , .kana = "dakara"},
  {.key = B_D|B_LBRC        , .kana = "dousite"},
  {.key = B_D|B_F           , .kana = "nani"},
  {.key = B_D|B_H           , .kana = "datta"},
  {.key = B_D|B_J           , .kana = "nala"},
  {.key = B_D|B_K           , .kana = "doko"},
  {.key = B_D|B_L           , .kana = "mono"},
  {.key = B_D|B_SCLN        , .kana = "dekiru"},
  {.key = B_D|B_COLN        , .kana = "dekita"},
  {.key = B_D|B_RBRC        , .kana = "dekite"},
  {.key = B_D|B_M            , .kana = "nnde"},
  {.key = B_D|B_COMM            , .kana = "yori"},
  {.key = B_D|B_DOT            , .kana = "you"},
  {.key = B_D|B_SLSH            , .kana = "noni"},

  {.key = B_E|B_I            , .kana = "ite"},
  {.key = B_E|B_O            , .kana = "kyou"},
  {.key = B_E|B_AT            , .kana = "kyuu"},
  {.key = B_E|B_J            , .kana = "dete"},
  {.key = B_E|B_L            , .kana = "mite"},

  {.key = B_G|B_Y            , .kana = "gyaku"},
  {.key = B_G|B_U            , .kana = "ugo"},
  {.key = B_G|B_I            , .kana = "tori"},
  {.key = B_G|B_P            , .kana = "motto"},
  {.key = B_G|B_AT            , .kana = "ltuka"},
  {.key = B_G|B_J            , .kana = "kere"},
  {.key = B_G|B_K            , .kana = "deli"},
  {.key = B_G|B_L            , .kana = "teli"},
  {.key = B_G|B_F            , .kana = "kedo"},
  {.key = B_G|B_SCLN            , .kana = "ppu"},
  {.key = B_G|B_COLN        , .kana = "ga,"},
  {.key = B_G|B_COMM            , .kana = "ltuti"},
  {.key = B_G|B_DOT            , .kana = "kku"},
  {.key = B_G|B_SCLN            , .kana = "kko"},

  {.key = B_H|B_U            , .kana = "hiraku"},
  {.key = B_H|B_I            , .kana = "hito"},
  {.key = B_H|B_O            , .kana = "hodo"},
  {.key = B_H|B_J            , .kana = "sikasi"},

  {.key = B_I|B_3            , .kana = "itta"},
  {.key = B_I|B_4            , .kana = "itte"},
  {.key = B_I|B_Q            , .kana = "iu"},
  {.key = B_I|B_W            , .kana = "ita"},
  {.key = B_I|B_E            , .kana = "ite"},
  {.key = B_I|B_R            , .kana = "iru"},
  {.key = B_I|B_O            , .kana = "nai"},
  {.key = B_I|B_B            , .kana = "ireba"},

  {.key = B_J|B_I            , .kana = "teru"},
  {.key = B_J|B_O            , .kana = "siyou"},
  {.key = B_J|B_P            , .kana = "miyou"},
  {.key = B_J|B_L            , .kana = "simau"},
  {.key = B_J|B_SCLN            , .kana = "kata"},
  {.key = B_J|B_N            , .kana = "jikann"},


  {.key = B_K|B_1            , .kana = "komi"},
  {.key = B_K|B_2            , .kana = "keta"},
  {.key = B_K|B_3            , .kana = "kete"},
  {.key = B_K|B_4            , .kana = "keru"},
  {.key = B_K|B_Q            , .kana = "kou"},
  {.key = B_K|B_W            , .kana = "katta"},
  {.key = B_K|B_E            , .kana = "katte"},
  {.key = B_K|B_R            , .kana = "kono"},
  {.key = B_K|B_A            , .kana = "kara"},
  {.key = B_K|B_J            , .kana = "iru"},
  {.key = B_K|B_L            , .kana = "suru"},
  {.key = B_K|B_SCLN         , .kana = "konai"},
  {.key = B_K|B_Z            , .kana = "kita"},
  {.key = B_K|B_X            , .kana = "kite"},
  {.key = B_K|B_B            , .kana = "kuru"},
  {.key = B_K|B_M            , .kana = "mae"},
  {.key = B_K|B_N            , .kana = "noka"},

  {.key = B_L|B_SCLN         , .kana = "inai"},

  {.key = B_M|B_2            , .kana = "motta"},
  {.key = B_M|B_3            , .kana = "motte"},
  {.key = B_M|B_4            , .kana = "motu"},
  {.key = B_M|B_Q            , .kana = "masite"},
  {.key = B_M|B_W            , .kana = "matta"},
  {.key = B_M|B_E            , .kana = "matte"},
  {.key = B_M|B_R            , .kana = "maru"},
  {.key = B_M|B_A            , .kana = "masu"},
  {.key = B_M|B_S            , .kana = "masenn"},
  {.key = B_M|B_G            , .kana = "masita"},
  {.key = B_M|B_N            , .kana = "made"},
  {.key = B_M|B_COMM         , .kana = "demo"},

  {.key = B_N|B_1            , .kana = "nnda"},
  {.key = B_N|B_2            , .kana = "nnde"},
  {.key = B_N|B_3            , .kana = "naka"},
  {.key = B_N|B_4            , .kana = "nou"},
  {.key = B_N|B_5            , .kana = "donnna"},
  {.key = B_N|B_Q            , .kana = ";n"},
  {.key = B_N|B_W            , .kana = "natta"},
  {.key = B_N|B_E            , .kana = "natte"},
  {.key = B_N|B_R            , .kana = "naru"},
  {.key = B_N|B_T            , .kana = "naranai"},
  {.key = B_N|B_A            , .kana = "nari"},
  {.key = B_N|B_S            , .kana = "nara"},
  {.key = B_N|B_D            , .kana = "nanoni"},
  {.key = B_N|B_F            , .kana = "nanoka"},
  {.key = B_N|B_G            , .kana = "nakereba"},
  {.key = B_N|B_X            , .kana = "nano"},
  {.key = B_N|B_B            , .kana = "node"},

  {.key = B_O|B_P            , .kana = "sinai"},
  {.key = B_O|B_M            , .kana = "omo"},

  {.key = B_R|B_7            , .kana = "rareta"},
  {.key = B_R|B_8            , .kana = "rarere"},
  {.key = B_R|B_9            , .kana = "rarete"},
  {.key = B_R|B_E            , .kana = "tte"},
  {.key = B_R|B_Y            , .kana = "yaru"},
  {.key = B_R|B_U            , .kana = "reru"},
  {.key = B_R|B_I            , .kana = "koto"},
  {.key = B_R|B_O            , .kana = "rou"},
  {.key = B_R|B_P            , .kana = "naku"},
  {.key = B_R|B_AT           , .kana = "rya"},
  {.key = B_R|B_LBRC         , .kana = "ryu"},
  {.key = B_R|B_G            , .kana = "nagare"},
  {.key = B_R|B_H            , .kana = "reba"},
  {.key = B_R|B_J            , .kana = "deru"},
  {.key = B_R|B_L            , .kana = "miru"},
  {.key = B_R|B_SCLN            , .kana = "nare"},
  {.key = B_R|B_COLN            , .kana = "kore"},
  {.key = B_R|B_COMM            , .kana = "ryou"},
  {.key = B_R|B_DOT            , .kana = "ryuu"},
  {.key = B_R|B_SLSH            , .kana = "ryo"},
  {.key = B_R|B_BSLS            , .kana = "ryu"},

  {.key = B_S|B_7            , .kana = "sareta"},
  {.key = B_S|B_8            , .kana = "saseta"},
  {.key = B_S|B_9            , .kana = "sasete"},
  {.key = B_S|B_0            , .kana = "saseru"},
  {.key = B_S|B_Y            , .kana = "sarete"},
  {.key = B_S|B_U            , .kana = "sou"},
  {.key = B_S|B_I            , .kana = "sore"},
  {.key = B_S|B_O            , .kana = "sono"},
  {.key = B_S|B_P            , .kana = "syu"},
  {.key = B_S|B_AT           , .kana = "sya"},
  {.key = B_S|B_LBRC         , .kana = "seltu"},
  {.key = B_S|B_A            , .kana = "sase"},
  {.key = B_S|B_D            , .kana = "toiu"},
  {.key = B_S|B_F            , .kana = "sare"},
  {.key = B_S|B_H            , .kana = "sareru"},
  {.key = B_S|B_J            , .kana = "syo"},
  {.key = B_S|B_K            , .kana = "soko"},
  {.key = B_S|B_L            , .kana = "tokoro"},
  {.key = B_S|B_SCLN         , .kana = "soku"},
  {.key = B_S|B_COLN         , .kana = "sonnna"},
  {.key = B_S|B_RBRC         , .kana = "subete"},
  {.key = B_S|B_COMM         , .kana = "syou"},
  {.key = B_S|B_DOT          , .kana = "syuu"},
  {.key = B_S|B_SLSH         , .kana = "sure"},

  {.key = B_T|B_O         , .kana = "toka"},
  // {.key = B_T|B_P         , .kana = "tyu"},
  {.key = B_T|B_AT        , .kana = "tya"},
  {.key = B_T|B_H         , .kana = "tuu"},
  {.key = B_T|B_J         , .kana = "deta"},
  {.key = B_T|B_I         , .kana = "koto"},
  {.key = B_T|B_K         , .kana = "toki"},
  {.key = B_T|B_M         , .kana = "tame"},
  {.key = B_T|B_COMM      , .kana = "tyou"},
  {.key = B_T|B_DOT       , .kana = "tyuu"},
  {.key = B_T|B_SLSH      , .kana = "tyo"},
  {.key = B_T|B_BSLS      , .kana = "tyu"},

  {.key = B_U|B_Y      , .kana = "yuku"},
  {.key = B_U|B_I      , .kana = "iku"},
  {.key = B_U|B_O      , .kana = "tuite"},

  {.key = B_V|B_B      , .kana = "youna"},

  {.key = B_W|B_7      , .kana = "wareta"},
  {.key = B_W|B_8      , .kana = "warete"},
  {.key = B_W|B_9      , .kana = "wareru"},
  {.key = B_W|B_E      , .kana = "tta"},
  {.key = B_W|B_R      , .kana = "ware"},
  {.key = B_W|B_U      , .kana = "waru"},
  {.key = B_W|B_O      , .kana = "rare"},
  {.key = B_W|B_P      , .kana = "rase"},
  {.key = B_W|B_H      , .kana = "wara"},
  {.key = B_W|B_J      , .kana = "wari"},
  {.key = B_W|B_L      , .kana = "wake"},  

  {.key = B_X|B_7      , .kana = "suu"},
  {.key = B_X|B_8      , .kana = "huu"},
  {.key = B_X|B_9      , .kana = "bou"},
  {.key = B_X|B_0      , .kana = "zuu"},
  {.key = B_X|B_Y      , .kana = "guu"},
  {.key = B_X|B_U      , .kana = "mou"},
  {.key = B_X|B_I      , .kana = "kuu"},
  {.key = B_X|B_O      , .kana = "ou"},
  {.key = B_X|B_P      , .kana = "pou"},
  {.key = B_X|B_AT     , .kana = "gou"},
  {.key = B_X|B_LBRC   , .kana = "tukete"},
  {.key = B_X|B_H      , .kana = "hou"},
  {.key = B_X|B_J      , .kana = "deha"},
  {.key = B_X|B_L      , .kana = "teki"},
  {.key = B_X|B_SCLN   , .kana = "tuku"},
  {.key = B_X|B_COLN   , .kana = "tuke"},
  {.key = B_X|B_RBRC   , .kana = "tuketa"},
  {.key = B_X|B_C      , .kana = "seru"},
  {.key = B_X|B_V      , .kana = "saku"},
  {.key = B_X|B_M      , .kana = "oku"},
  {.key = B_X|B_DOT      , .kana = "rou"},
  {.key = B_X|B_SLSH      , .kana = "tukeru"},

  {.key = B_Y|B_1      , .kana = "yorosii"},
  {.key = B_Y|B_2      , .kana = "yotta"},
  {.key = B_Y|B_3      , .kana = "yotte"},
  {.key = B_Y|B_4      , .kana = "yoru"},
  {.key = B_Y|B_Q      , .kana = "yuu"},
  {.key = B_Y|B_W      , .kana = "yatta"},
  {.key = B_Y|B_E      , .kana = "yatte"},
  {.key = B_Y|B_R      , .kana = "yaru"},
  {.key = B_Y|B_T      , .kana = "tyotto"},
  {.key = B_Y|B_O      , .kana = "yarukoto"},

  {.key = B_Z|B_K      , .kana = "uuuuuuuu"},

  {.key = B_COMM|B_W      , .kana = "reta"},
  {.key = B_COMM|B_E      , .kana = "rete"},
  {.key = B_COMM|B_Z      , .kana = "meta"},
  {.key = B_COMM|B_X      , .kana = "mete"},
  {.key = B_COMM|B_C      , .kana = "meru"},

  {.key = B_SCLN|B_1      , .kana = "!"},
  {.key = B_SCLN|B_2      , .kana = "?"},

  // {.key = B_BSLS|B_1      , .kana = "kyuu"},
  // {.key = B_BSLS|B_2      , .kana = "kyou"},
  // {.key = B_BSLS|B_3      , .kana = "kya"},
  // {.key = B_BSLS|B_4      , .kana = "kyu"},
  // {.key = B_BSLS|B_5      , .kana = "kyo"},
  // {.key = B_BSLS|B_Q      , .kana = "myuu"},
  // {.key = B_BSLS|B_W      , .kana = "myou"},
  // {.key = B_BSLS|B_E      , .kana = "tyuu"},
  // {.key = B_BSLS|B_R      , .kana = "tyou"},
  // {.key = B_BSLS|B_T      , .kana = "tyo"},
  // {.key = B_BSLS|B_A      , .kana = "byuu"},
  {.key = B_BSLS|B_S      , .kana = "settei"},
  // {.key = B_BSLS|B_D      , .kana = "hyou"},
  // {.key = B_BSLS|B_F      , .kana = "hyuu"},
  // {.key = B_BSLS|B_G      , .kana = "rya"},
  // {.key = B_BSLS|B_X      , .kana = "gyuu"},
  // {.key = B_BSLS|B_C      , .kana = "gyou"},
  // {.key = B_BSLS|B_V      , .kana = "nyuu"},
  // {.key = B_BSLS|B_B      , .kana = "nyou"},
                                                         
  // 単独
  {.key = B_Q               , .kana = "na"},
  {.key = B_W               , .kana = "ra"},
  {.key = B_E               , .kana = "ji"},
  {.key = B_R               , .kana = "re"},
  {.key = B_T               , .kana = "ri"},
  {.key = B_Y               , .kana = "yo"},
  {.key = B_U               , .kana = "ru"},
  {.key = B_I               , .kana = "to"},
  {.key = B_O               , .kana = "ha"},
  {.key = B_P               , .kana = "-"},

  {.key = B_A               , .kana = "ki"},
  {.key = B_S               , .kana = "si"},
  {.key = B_D               , .kana = "u"},
  {.key = B_F               , .kana = "te"},
  {.key = B_G               , .kana = "ma"},
  {.key = B_H               , .kana = "no"},
  {.key = B_J               , .kana = "nn"},
  {.key = B_K               , .kana = "i"},
  {.key = B_L               , .kana = "ka"},
  {.key = B_SCLN            , .kana = "ta"},

  {.key = B_Z               , .kana = "xxx"},
  {.key = B_X               , .kana = "ni"},
  {.key = B_C               , .kana = "do"},
  {.key = B_V               , .kana = "ku"},
  {.key = B_B               , .kana = "sa"},
  {.key = B_N               , .kana = "lya"},
  {.key = B_M               , .kana = "ltu"},
  {.key = B_COMM            , .kana = "lyo"},
  {.key = B_DOT             , .kana = "lyu"},
  {.key = B_SLSH            , .kana = "wo"},

  {.key = B_1               , .kana = "pi"},
  {.key = B_2               , .kana = "bi"},
  // {.key = B_3               , .kana = "ti"},
  // {.key = B_4               , .kana = "ze"},
  {.key = B_5               , .kana = "pu"},
  {.key = B_6               , .kana = "xxx"},
  {.key = B_7               , .kana = "du"},
  {.key = B_8               , .kana = "zu"},
  {.key = B_9               , .kana = "xe"},
  {.key = B_0               , .kana = "xxx"},

  {.key = B_AT              , .kana = "o"},
  {.key = B_LBRC            , .kana = "ki"},
  {.key = B_COLN            , .kana = "ko"},
  {.key = B_RBRC            , .kana = "xxx"},
  {.key = B_BSLS            , .kana = "xxx"},

  // Shift and space
  // {.key = B_SHFTL           , .kana = " "},
  {.key = B_SHFTR           , .kana = " "},

  // 左シフト
  {.key = B_SHFTL|B_Q       , .kana = "za"},
  {.key = B_SHFTL|B_W       , .kana = "e"},
  {.key = B_SHFTL|B_E       , .kana = "ne"},
  {.key = B_SHFTL|B_R       , .kana = "lo"},
  {.key = B_SHFTL|B_T       , .kana = "zo"},
  {.key = B_SHFTL|B_Y       , .kana = "nante"},
  {.key = B_SHFTL|B_U       , .kana = "li"},
  {.key = B_SHFTL|B_I       , .kana = "sita"},
  {.key = B_SHFTL|B_O       , .kana = "ti"},
  {.key = B_SHFTL|B_P       , .kana = "xxx"},

  {.key = B_SHFTL|B_A       , .kana = "da"},
  {.key = B_SHFTL|B_S       , .kana = "a"},
  {.key = B_SHFTL|B_D       , .kana = "ge"},
  {.key = B_SHFTL|B_F       , .kana = "bu"},
  {.key = B_SHFTL|B_G       , .kana = "la"},
  {.key = B_SHFTL|B_H       , .kana = "tu"},
  {.key = B_SHFTL|B_J       , .kana = "wa"},
  {.key = B_SHFTL|B_K       , .kana = "su"},
  {.key = B_SHFTL|B_L       , .kana = "hu"},
  {.key = B_SHFTL|B_SCLN    , .kana = "de"},

  {.key = B_SHFTL|B_Z       , .kana = "ze"},
  {.key = B_SHFTL|B_X       , .kana = "hi"},
  {.key = B_SHFTL|B_C       , .kana = "se"},
  {.key = B_SHFTL|B_V       , .kana = "ba"},
  {.key = B_SHFTL|B_B       , .kana = "lu"},
  {.key = B_SHFTL|B_N       , .kana = "ya"},
  {.key = B_SHFTL|B_M       , .kana = "ga"},
  {.key = B_SHFTL|B_COMM    , .kana = "keta"},
  {.key = B_SHFTL|B_DOT     , .kana = "uti"},
  {.key = B_SHFTL|B_SLSH    , .kana = "eru"},

  {.key = B_SHFTL|B_1       , .kana = "1"},
  {.key = B_SHFTL|B_2       , .kana = "2"},
  {.key = B_SHFTL|B_3       , .kana = "3"},
  {.key = B_SHFTL|B_4       , .kana = "4"},
  {.key = B_SHFTL|B_5       , .kana = "5"},
  {.key = B_SHFTL|B_6       , .kana = "6"},
  {.key = B_SHFTL|B_7       , .kana = "7"},
  {.key = B_SHFTL|B_8       , .kana = "8"},
  {.key = B_SHFTL|B_9       , .kana = "9"},
  {.key = B_SHFTL|B_0       , .kana = "0"},

  {.key = B_SHFTL|B_AT      , .kana = "pu"},
  {.key = B_SHFTL|B_LBRC    , .kana = "ze"},
  {.key = B_SHFTL|B_COLN    , .kana = "tto"},
  {.key = B_SHFTL|B_RBRC    , .kana = "eta"},
  {.key = B_SHFTL|B_BSLS    , .kana = "ete"},

  // 右シフト
  // {.key = B_SHFTR|B_Q       , .kana = "xxx"},
  // {.key = B_SHFTR|B_W       , .kana = "xxx"},
  // {.key = B_SHFTR|B_E       , .kana = "xxx"},
  // {.key = B_SHFTR|B_R       , .kana = "xxx"},
  // {.key = B_SHFTR|B_T       , .kana = "xxx"},
  {.key = B_SHFTR|B_Y       , .kana = "mitai"},
  {.key = B_SHFTR|B_U       , .kana = "gi"},
  {.key = B_SHFTR|B_I       , .kana = "so"},
  {.key = B_SHFTR|B_O       , .kana = "mi"},
  {.key = B_SHFTR|B_P       , .kana = "he"},

  {.key = B_SHFTR|B_A       , .kana = "ho"},
  {.key = B_SHFTR|B_S       , .kana = "ro"},
  {.key = B_SHFTR|B_D       , .kana = "ke"},
  {.key = B_SHFTR|B_F       , .kana = "yu"},
  {.key = B_SHFTR|B_G       , .kana = "tu"},
  // {.key = B_SHFTR|B_H       , .kana = "xxx"},
  // {.key = B_SHFTR|B_J       , .kana = "xxx"},
  // {.key = B_SHFTR|B_K       , .kana = "xxx"},
  // {.key = B_SHFTR|B_L       , .kana = "xxx"},
  {.key = B_SHFTR|B_SCLN    , .kana = "site"},

  {.key = B_SHFTR|B_X       , .kana = "gu"},
  {.key = B_SHFTR|B_C       , .kana = "be"},
  {.key = B_SHFTR|B_V       , .kana = "bo"},
  {.key = B_SHFTR|B_B       , .kana = "."},
  {.key = B_SHFTR|B_N       , .kana = "mu"},
  {.key = B_SHFTR|B_M       , .kana = "me"},
  {.key = B_SHFTR|B_COMM    , .kana = "desu"},
  {.key = B_SHFTR|B_DOT     , .kana = "mo"},
  {.key = B_SHFTR|B_SLSH    , .kana = "tou"},
  
  {.key = B_SHFTR|B_1       , .kana = "di"},
  {.key = B_SHFTR|B_2       , .kana = "vu"},
  {.key = B_SHFTR|B_3       , .kana = "po"},
  {.key = B_SHFTR|B_4       , .kana = "pe"},
  {.key = B_SHFTR|B_5       , .kana = "xxx"},
  {.key = B_SHFTR|B_6       , .kana = "&"},
  {.key = B_SHFTR|B_7       , .kana = "nu"},
  {.key = B_SHFTR|B_8       , .kana = "xxx"},
  {.key = B_SHFTR|B_9       , .kana = "xxx"},
  {.key = B_SHFTR|B_0       , .kana = "xxx"},

  {.key = B_SHFTR|B_AT      , .kana = "go"},
  {.key = B_SHFTR|B_LBRC    , .kana = "xxx"},
  {.key = B_SHFTR|B_COLN    , .kana = ","},
  {.key = B_SHFTR|B_RBRC    , .kana = "xxx"},
  {.key = B_SHFTR|B_BSLS    , .kana = "pe"},


};

// 親指シフトのレイヤー、シフトキーを設定
void set_nicola(uint8_t layer) {
  nicola_layer = layer;
}

// 3打鍵のレイヤーフラグ
bool wait_flag_three = false;

// 親指シフトをオンオフ
void nicola_on(void) {
  is_nicola = true;
  keycomb = 0UL;
  nicola_clear();
  layer_on(nicola_layer);
}

void nicola_off(void) {
  is_nicola = false;
  keycomb = 0UL;
  nicola_clear();
  layer_off(nicola_layer);
}

// 親指シフトの状態
bool nicola_state(void) {
  return is_nicola;
}

// キー入力を文字に変換して出力する
void nicola_type(void) {
  nicola_keymap bngmap; // PROGMEM buffer
  switch (keycomb) {
    // 4delete
    case B_3:
      SEND_STRING(SS_TAP(X_DELETE) SS_TAP(X_DELETE) SS_TAP(X_DELETE) SS_TAP(X_DELETE) SS_TAP(X_DELETE));
      break;
    // 4backspace
    case B_4:
      SEND_STRING(SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE));
      break;
    // home
    case B_SHFTR|B_Q:
      tap_code(KC_HOME);
      break;
    // end
    case B_SHFTR|B_T:
      tap_code(KC_END);
      break;
    // word left
    case B_SHFTR|B_W:
      SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_UP(X_LCTRL));
      break;
    // word right
    case B_SHFTR|B_R:
      SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_UP(X_LCTRL));
      break;
    // delete
    case B_SHFTR|B_E:
      SEND_STRING(SS_TAP(X_DELETE));
      break;
    // left
    case B_SHFTR|B_H:
      SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      break;
    // down
    case B_SHFTR|B_J:
      SEND_STRING(SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN));
      break;
    // up
    case B_SHFTR|B_K:
      SEND_STRING(SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP));
      break;
    // right
    case B_SHFTR|B_L:
      SEND_STRING(SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT));
      break;
    // 同時押し
    case B_SHFTR|B_I|B_O:
      send_string("idou");
      break;
    case B_SHFTR|B_D|B_N:
      send_string("dhzz");
      break;
    // いろいろ
    case B_SHFTR|B_I|B_R:
      send_string(";r;r");
      break;
    // ほんとう
    case B_SHFTR|B_H|B_T:
      send_string("hztz");
      break;
    // そういう
    case B_SHFTR|B_S|B_I|B_I:
      send_string("sqz;");
      break;
    // いつも
    case B_SHFTR|B_I|B_T:
      send_string("qtm");
      break;
    // けいぞく
    case B_SHFTR|B_K|B_Z:
      send_string("kqzk");
      break;
    case B_SHFTR|B_I|B_G:
      send_string("igai");
      break;
    // ながら
    case B_SHFTR|B_N|B_G:
      send_string("ngr");
      break;
    case B_SHFTR|B_A|B_I:
      send_string("aida");
      break;
    case B_K|B_N|B_D:
      send_string("kakuninn");
      break;
    case B_S|B_K|B_O:
      send_string("sukosi");
      break;
    // そろそろ
    case B_SHFTR|B_S|B_P:
      send_string("srsr");
      break;
    // ながれ
    case B_SHFTR|B_N|B_R:
      send_string("ngq");
      break;
    // わたし
    case B_SHFTR|B_W|B_L:
      send_string("wq");
      break;
    // されていた
    case B_S|B_D|B_U:
      send_string("srtt");
      break;
    // されていて
    case B_S|B_D|B_I:
      send_string("srti");
      break;
    // されている
    case B_S|B_D|B_O:
      send_string("srtr");
      break;
    // していた
    case B_S|B_D|B_J:
      send_string("stt");
      break;
    // していて
    case B_S|B_D|B_K:
      send_string("stiq");
      break;
    // している
    case B_S|B_D|B_L:
      send_string("stir");
      break;
    // っていた
    case B_S|B_D|B_N:
      send_string("ttit");
      break;
    // っていて
    case B_S|B_D|B_M:
      send_string("ttiq");
      break;
    // っている
    case B_S|B_D|B_COMM:
      send_string("ttir");
      break;
    // つづけた
    case B_8|B_9|B_W:
      send_string("tuduketa");
      break;
    // つづけて
    case B_8|B_9|B_E:
      send_string("tudukete");
      break;
    // つづける
    case B_8|B_9|B_R:
      send_string("tudukeru");
      break;
    // つづく
    case B_8|B_9|B_A:
      send_string("tuduku");
      break;
    // つづいた
    case B_8|B_9|B_S:
      send_string("tuduita");
      break;
    // つづいて
    case B_8|B_9|B_D:
      send_string("tuduite");
      break;
    // つづく
    case B_8|B_9|B_F:
      send_string("tuduku");
      break;
    // すぎた
    case B_S|B_D|B_8:
      send_string("sgt");
      break;
    // すぎて
    case B_S|B_D|B_9:
      send_string("sgq");
      break;
    // すぎる
    case B_S|B_D|B_0:
      send_string("sgr");
      break;
    // ことができた
    case B_K|B_O|B_2:
      send_string("kotogadekita");
      break;
    // ことができて
    case B_K|B_O|B_3:
      send_string("kotogadekite");
      break;
    // ことができる
    case B_K|B_O|B_4:
      send_string("kotogadekiru");
      break;
    // こうどう
    case B_K|B_O|B_D:
      send_string("koudou");
      break;
    // おもしろ
    case B_O|B_M|B_S:
      send_string("omosiro");
      break;
    // おもい
    case B_O|B_M|B_Q:
      send_string("omoi");
      break;
    // おもった
    case B_O|B_M|B_W:
      send_string("omotta");
      break;
    // おもって
    case B_O|B_M|B_E:
      send_string("omotte");
      break;
    // おもう
    case B_O|B_M|B_R:
      send_string("omou");
      break;
    // ていた
    case B_J|B_I|B_S:
      send_string("teita");
      break;
    // ていて
    case B_J|B_I|B_D:
      send_string("teite");
      break;
    // ている
    case B_J|B_I|B_F:
      send_string("teiru");
      break;
    // られる
    case B_J|B_L|B_W:
      send_string("rareru");
      break;
    // られて
    case B_J|B_L|B_E:
      send_string("rarete");
      break;
    // られた
    case B_J|B_L|B_R:
      send_string("rareta");
      break;
    // われた
    case B_J|B_L|B_S:
      send_string("wareta");
      break;
    // われて
    case B_J|B_L|B_D:
      send_string("warete");
      break;
    // われる
    case B_J|B_L|B_F:
      send_string("wareru");
      break;
    // ・
    case B_T|B_P:
      send_string("/");
      SEND_STRING(SS_TAP(X_ENTER));
      break;
    // ——
    case B_J|B_K|B_Q:
      send_string("bo");
      SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      break;
    // …
    case B_J|B_K|B_W:
      SEND_STRING("ten" SS_TAP(X_SPACE) SS_TAP(X_ENTER));
      break;
    // ()
    case B_J|B_K|B_A:
      SEND_STRING(SS_DOWN(X_LSHIFT) SS_TAP(X_8) SS_TAP(X_9) SS_UP(X_LSHIFT) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      break;
    // 「」
    case B_K|B_L|B_A:
      send_string("ikako");
      SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      break;
    // 『』
    case B_K|B_L|B_Q:
      send_string("nikako");
      SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_ENTER) SS_TAP(X_LEFT));
      break;
    // こんだ
    case B_J|B_K|B_S:
      send_string("konda");
      break;
    // こんで
    case B_J|B_K|B_D:
      send_string("konde");
      break;
    // こむ
    case B_J|B_K|B_F:
      send_string("komu");
      break;
    // かんじ
    case B_K|B_N|B_J:
      send_string("kanji");
      break;
    // みょう
    case B_I|B_O|B_Q:
      send_string("myou");
      break;
    // みゅう
    case B_I|B_O|B_W:
      send_string("myuu");
      break;
    // びょう
    case B_I|B_O|B_A:
      send_string("byou");
      break;
    // びゅう
    case B_I|B_O|B_S:
      send_string("byuu");
      break;
    // ひょう
    case B_I|B_O|B_D:
      send_string("hyou");
      break;
    // ひゅう
    case B_I|B_O|B_F:
      send_string("hyuu");
      break;
    // ぎょう
    case B_I|B_O|B_Z:
      send_string("gyou");
      break;
    // ぎゅう
    case B_I|B_O|B_X:
      send_string("gyuu");
      break;
    // にょう
    case B_I|B_O|B_C:
      send_string("nyou");
      break;
    // にゅう
    case B_I|B_O|B_V:
      send_string("nyuu");
      break;
    // れていた
    case B_E|B_R|B_J:
      send_string("reteta");
      break;
    // れていて
    case B_E|B_R|B_K:
      send_string("reteite");
      break;
    // れている
    case B_E|B_R|B_L:
      send_string("reteiru");
      break;
    // おしまい
    case B_A|B_M|B_O:
      send_string("osimai");
      break;
    // こんな
    case B_A|B_K|B_N:
      send_string("konna");
      break;
    // しょん
    case B_J|B_S|B_O:
      send_string("shon");
      break;
    case B_S|B_M|B_SHFTR:
      send_string("sms");
      break;
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合 ngmapに定義されている
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof(bngmap));
        if (keycomb == bngmap.key) {
          // 月配列（Z）
          if (bngmap.key == B_Z)  {
            set_oneshot_layer(4, ONESHOT_START);
            return;
          }
          // 月配列（_）
          if (bngmap.key == B_BSLS)  {
            set_oneshot_layer(5, ONESHOT_START);
            return;
          }
          send_string(bngmap.kana);
          break;
        }
      }
  }

  nicola_clear(); // バッファを空にする
}

// modifierが押されたら薙刀式レイヤーをオフしてベースレイヤーに戻す
// get_mods()がうまく動かない
static int n_modifier = 0;

bool process_modifier(uint64_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
    case LCTL_T(0x01) ... LCTL_T(0xFFFFFFFFFFFFFFFF):
    case LSFT_T(0x01) ... LSFT_T(0xFFFFFFFFFFFFFFFF):
    case LALT_T(0x01) ... LALT_T(0xFFFFFFFFFFFFFFFF):
    case LGUI_T(0x01) ... LGUI_T(0xFFFFFFFFFFFFFFFF):
    case RCTL_T(0x01) ... RCTL_T(0xFFFFFFFFFFFFFFFF):
    case RSFT_T(0x01) ... RSFT_T(0xFFFFFFFFFFFFFFFF):
    case RALT_T(0x01) ... RALT_T(0xFFFFFFFFFFFFFFFF):
    case RGUI_T(0x01) ... RGUI_T(0xFFFFFFFFFFFFFFFF):
      if (record->event.pressed) {
        n_modifier++;
        layer_off(nicola_layer);
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(nicola_layer);
        }
      }
      return true;
      break;
  }
  return false;
}

// バッファをクリアする
void nicola_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
  n_modifier = 0;
}

// 親指シフトの入力処理
bool process_nicola(uint64_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case NG_Q ... NG_SHFTR:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        keycomb |= ng_key[keycode - NG_Q]; // キーの重ね合わせ
        // 2つのキーが入力されたら、3キー目の入力を1入力ぶん待つ
        if (ng_chrcount == 2 && !wait_flag_three) {
          wait_flag_three = true;
          return false;
        }
        // 2文字以上押したら処理を開始
        if (ng_chrcount > 1) {
          nicola_type();
        }
        wait_flag_three = false;
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case NG_Q ... NG_SHFTR:
        // 2文字入力していなくても、どれかキーを離したら処理を開始する
        if (ng_chrcount > 0) {
          nicola_type();
        }
        keycomb &= ~ng_key[keycode - NG_Q]; // キーの重ね合わせ
        wait_flag_three = false;
        return false;
        break;
    }
  }
  return true;
}

