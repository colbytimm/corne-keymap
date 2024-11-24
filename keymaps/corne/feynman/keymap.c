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

//qmk compile -c -kb crkbd/rev1 -km feynman -e CONVERT_TO=helios

#include QMK_KEYBOARD_H
#include <string.h>

#define _BASE 0
#define _NUM 1
#define _POWER 2
#define _MEDIA 3

bool ANIM_START = false;
bool ENABLE_RAINBOW = false;

#ifdef OLED_ENABLE
#include "enigma.c"
#endif

// Tap Dance declarations
enum {
    TD_SHIFT_CAPS,
};

enum custom_keycodes {
    KC_OLED_ANIM = SAFE_RANGE,
    OUTPUT_LAYOUT
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Shift, twice for Caps Lock
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
(LGUI(KC_SPC),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,TG(_MEDIA),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_SHIFT_CAPS),KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_SPC, KC_LGUI,MO(_NUM),   TG(_POWER),  KC_ENT, KC_BSPC
                                      //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LGUI(KC_GRAVE),XXXXXXX, XXXXXXX, XXXXXXX,  KC_EQL, KC_MINS,                      XXXXXXX, KC_LEFT,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_SHIFT_CAPS),XXXXXXX,XXXXXXX,XXXXXXX,LGUI(KC_V),LGUI(KC_C),                 XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       C(KC_LOPT), KC_LGUI, XXXXXXX,    KC_LCTL,  KC_ENT, KC_LOPT
                                      //`--------------------------'  `--------------------------'
    ),

    [_POWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         LGUI(KC_SPC),LOPT(KC_LEFT_GUI),XXXXXXX,TG(_POWER),XXXXXXX,XXXXXXX
                                      //`--------------------------'  `--------------------------'
    ),

//     [_VIM] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_ESC, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,    KC_I,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       XXXXXXX, XXXXXXX,KC_MS_LEFT,KC_MS_UP,KC_MS_RIGHT,XXXXXXX,                  XXXXXXX,    KC_H,    KC_K,    KC_L, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       XXXXXXX, XXXXXXX, XXXXXXX,KC_MS_DOWN,XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX,    KC_J, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           KC_LGUI, _______,  KC_SPC,  TG(_VIM), KC_BTN1, KC_BTN2
//                                       //`--------------------------'  `--------------------------'
//     ),

    [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 LOPT(KC_SPC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,TG(_MEDIA),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_VOLU,                      XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_SHIFT_CAPS),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, KC_VOLD,                     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_BSLS, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                     KC_OLED_ANIM, KC_LCTL, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
    )
};

void write_oled(const char* value) {
    if (!ANIM_START) {
        oled_write_P(PSTR(value), false);
    }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    if (ANIM_START) {
        if (is_keyboard_master()) {
            oled_render_anim();
        }
    } else {
        oled_render_cat();
        oled_write_P(PSTR("Layer: "), false);
    }

    uint8_t mods = get_mods();

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            write_oled("Base");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
            break;
        case _NUM:
            write_oled("Numbers");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
            break;
        case _POWER:
            write_oled("POWER");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_TEAL);
            break;
        case _MEDIA:
            write_oled("Media");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_CORAL);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            write_oled("Undefined");
    }
    if (mods & MOD_MASK_SHIFT) {
        oled_clear();
        oled_write_P(PSTR("Shift"), false);
    }
    if (mods & MOD_MASK_GUI) {
        oled_clear();
        oled_write_P(PSTR("CMD"), false);
    }

    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_OLED_ANIM:
            if (record->event.pressed) {
                ANIM_START=!ANIM_START;
                ENABLE_RAINBOW=!ENABLE_RAINBOW;
            } else {
                oled_clear();
            }
            return false;
        default:
            return true;
    }
}
