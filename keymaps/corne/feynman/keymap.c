/*
Custom Corne Keymap - Optimized for MacOS Development
*/

#include QMK_KEYBOARD_H

#define _BASE 0
#define _NUM 1
#define _POWER 2
#define _MEDIA 3
#define _SETTINGS 4

// Tap Dance declarations
enum {
    TD_SHIFT_CAPS,
};

// Custom Keycodes
enum custom_keycodes {
    KC_OLED_ANIM = SAFE_RANGE,
    KC_OPTION_CMD_LBRACKET,
    KC_OPTION_CMD_RBRACKET,
    KC_C_S_RIGHT,
    KC_CMD_SHIFT_BS,
    KC_CMD_P,
    KC_CMD_SHIFT_P,
    KC_OPTION_CMD_SLSH
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        LGUI(KC_SPC), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TG(_MEDIA),
        KC_TAB,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        TD(TD_SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                          KC_SPC, KC_LGUI, MO(_NUM), TG(_POWER), KC_ENT, KC_BSPC
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        KC_ESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        LGUI(KC_GRV), XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,  KC_MINS,                      XXXXXXX, KC_LEFT, KC_UP,   KC_RIGHT, XXXXXXX, XXXXXXX,
        TD(TD_SHIFT_CAPS), XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC,                 XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,
                                          C(KC_LOPT), KC_LGUI, XXXXXXX, KC_LCTL,  KC_ENT, KC_LOPT
    ),

    [_POWER] = LAYOUT_split_3x6_3(
        KC_OPTION_CMD_LBRACKET, KC_OPTION_CMD_RBRACKET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX, LCTL(LGUI(KC_Q)),
        KC_C_S_RIGHT, KC_CMD_SHIFT_BS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MS_LEFT, KC_MS_UP, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
        KC_CMD_P,     KC_CMD_SHIFT_P,  KC_OPTION_CMD_SLSH, LCTL(KC_C), XXXXXXX, LGUI(LSFT(KC_SPC)), XXXXXXX, XXXXXXX, KC_MS_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,
                                          LGUI(KC_SPC), LOPT(KC_LEFT_GUI), XXXXXXX, TG(_POWER), XXXXXXX, XXXXXXX
    ),

    [_MEDIA] = LAYOUT_split_3x6_3(
        LOPT(KC_SPC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_MEDIA),
        XXXXXXX,      XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TD(TD_SHIFT_CAPS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_RBRC,
                                          KC_OLED_ANIM, KC_LCTL, XXXXXXX, MO(_SETTINGS), XXXXXXX, XXXXXXX
    ),

    [_SETTINGS] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
            write_oled("BASE");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
            break;
        case _NUM:
            write_oled("NUM");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
            break;
        case _POWER:
            write_oled("POWER");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_TEAL);
            break;
        case _MEDIA:
            write_oled("MEDIA");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_CORAL);
            break;
        case _SETTINGS:
            write_oled("SETTINGS");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
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
        case KC_OPTION_CMD_LBRACKET:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LGUI);
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LBRC);
                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
            }
            return false;
        case KC_OPTION_CMD_RBRACKET:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LGUI);
                register_code(KC_RBRC);
            } else {
                unregister_code(KC_RBRC);
                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
            }
            return false;
        case KC_C_S_RIGHT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        default:
            return true;
    }
}
