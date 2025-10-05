/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre

GPLv2 or later.
*/

// qmk compile -c -kb crkbd/rev1 -km feynman -e CONVERT_TO=helios

#include QMK_KEYBOARD_H
#include <string.h>

/* Layers: swap your old _NUM/_POWER for _NAV/_SYM to match the new flow */
#define _BASE     0
#define _NAV      1
#define _SYM      2
#define _MEDIA    3
#define _SETTINGS 4

bool ANIM_START = false;
bool ENABLE_RAINBOW = false;

#ifdef OLED_ENABLE
#include "enigma.c"   // your animation & cat renderer
#endif

/* ───────────────── Tap Dance: keep your Shift/Caps toggle ───────────────── */
enum { TD_SHIFT_CAPS };

/* ─────────────── Custom keycodes: keep yours, add Raycast/Magnet ─────────── */
enum custom_keycodes {
    KC_OLED_ANIM = SAFE_RANGE,
    OUTPUT_LAYOUT,
    RGB_TOG_KEY,
    KC_OPTION_CMD_LBRACKET,
    KC_OPTION_CMD_RBRACKET,
    KC_C_S_RIGHT,
    KC_CMD_SHIFT_BS,
    KC_CMD_P,
    KC_CMD_SHIFT_P,
    KC_OPTION_CMD_SLSH,

    /* New: workflow macros */
    RAYCAST,     // Cmd+Space
    MG_LEFT,     // Ctrl+Opt+Left  (Magnet snap left)
    MG_RIGHT,    // Ctrl+Opt+Right (Magnet snap right)
    MG_FULL      // Ctrl+Opt+F     (Magnet full screen or your preferred bind)
};

/* Tap Dance bindings */
tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

/* ─────────────────────────── Home-Row Mods ────────────────────────────────
   Left:  A=Ctrl, S=Alt, D=Cmd, F=Shift
   Right: J=Shift, K=Cmd, L=Alt, ;=Ctrl
*/
#define HM_A    MT(MOD_LCTL, KC_A)
#define HM_S    MT(MOD_LALT, KC_S)
#define HM_D    MT(MOD_LGUI, KC_D)
#define HM_F    MT(MOD_LSFT, KC_F)
#define HM_J    MT(MOD_RSFT, KC_J)
#define HM_K    MT(MOD_RGUI, KC_K)
#define HM_L    MT(MOD_RALT, KC_L)
#define HM_SCL  MT(MOD_RCTL, KC_SCLN)

/* ─────────────────────────── Thumb assignments ─────────────────────────────
   L-inner: Space (tap) / NAV (hold)
   L-outer: Esc (tap)   / Ctrl (hold)
   R-inner: Enter (tap) / SYM (hold)
   R-outer: Backspace (tap) / MEDIA (hold)
*/
#define TH_L_IN   LT(_NAV, KC_SPC)
#define TH_L_OUT  MT(MOD_LCTL, KC_ESC)
#define TH_R_IN   LT(_SYM, KC_ENT)
#define TH_R_OUT  LT(_MEDIA, KC_BSPC)

/* Mac nav helpers */
#define W_L     LALT(KC_LEFT)
#define W_R     LALT(KC_RGHT)
#define L_HOME  LGUI(KC_LEFT)
#define L_END   LGUI(KC_RGHT)
#define DEL_W   LALT(KC_BSPC)
#define FDEL_W  LALT(KC_DEL)

/* ───────────────────────────── Keymaps ─────────────────────────────────── */
#define LAYOUT LAYOUT_split_3x6_3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ─────────────── BASE (typing) ───────────────
   Keep a couple of your base conveniences (e.g., dedicated Raycast if desired)
*/
[_BASE] = LAYOUT(
/* Row1 */   RAYCAST, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,            KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   TG(_MEDIA),
/* Row2 */   KC_TAB,  HM_A,  HM_S,  HM_D,  HM_F,  KC_G,            KC_H,   HM_J,   HM_K,   HM_L,   HM_SCL, KC_QUOT,
/* Row3 */   TD(TD_SHIFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B,      KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_BSLS,
/* Thumbs */                 TH_L_OUT, TH_L_IN, KC_DEL,     KC_MUTE, TH_R_IN, TH_R_OUT
),

/* ─────────────── NAV (hold Space) ───────────────
   VS Code / Warp / Arc navigation & editing, Mac primitives
*/
[_NAV] = LAYOUT(
/* Row1 */   _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
/* Row2 */   L_HOME,  W_L,     RAYCAST, W_R,     L_END,   KC_LEFT,   KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, KC_PGDN, _______,
/* Row3 */   KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, DEL_W,   KC_ESC,    FDEL_W,  KC_HOME, KC_END,  KC_TAB,  KC_LCMD, KC_RCMD,
/* Thumbs */                 _______, _______, _______,     _______, _______, _______
),

/* ─────────────── SYM / NUM (hold Enter) ───────────────
   Dev symbols grouped by shape; numbers on bottom row for fast reach
*/
[_SYM] = LAYOUT(
/* Row1 */   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,   KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
/* Row2 */   KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK,   KC_EQL,  KC_MINS, KC_QUOT, KC_DQUO, KC_GRV,  KC_TILD,
/* Row3 */   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,    KC_8,    KC_9,    KC_0,    KC_SCLN, KC_SLSH,
/* Thumbs */                 _______, _______, _______,     _______, _______, _______
),

/* ─────────────── MEDIA (hold Backspace) ───────────────
   Spotify, volume, Magnet window mgmt, plus your OLED anim toggle & settings
*/
[_MEDIA] = LAYOUT(
/* Row1 */   LOPT(KC_SPC), KC_MPRV, KC_MPLY, KC_MNXT, KC__MUTE, KC_VOLU,   MG_LEFT, MG_RIGHT, MG_FULL, _______, _______, TG(_MEDIA),
/* Row2 */   _______, _______, _______, _______, _______, KC_VOLD,          _______, _______, _______,  _______, _______, _______,
/* Row3 */   TD(TD_SHIFT_CAPS), _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_BSLS, KC_RBRC,
/* Thumbs */               KC_OLED_ANIM, KC_LCTL, _______,     MO(_SETTINGS), _______, _______
),

/* ─────────────── SETTINGS ───────────────
   Keep your RGB toggle etc. (expand as you like)
*/
[_SETTINGS] = LAYOUT(
/* Row1 */   _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, RGB_TOG_KEY,
/* Row2 */   _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
/* Row3 */   _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
/* Thumbs */                 _______, _______, _______,     _______, _______, _______
)
};

/* ─────────────────────────── OLED helpers ─────────────────────────────── */

static inline void write_oled(const char* value) {
    if (!ANIM_START) oled_write_P(PSTR(""), false), oled_write_P(PSTR(value), false);
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (ANIM_START) {
        if (is_keyboard_master()) { oled_render_anim(); }
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
        case _NAV:
            write_oled("NAV");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_TEAL);
            break;
        case _SYM:
            write_oled("SYM");
            rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
            rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
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

    if (mods & MOD_MASK_SHIFT) { oled_clear(); oled_write_P(PSTR("Shift"), false); }
    if (mods & MOD_MASK_GUI)   { oled_clear(); oled_write_P(PSTR("CMD"),   false); }

    return false;
}
#endif

/* ───────────────────────── Macro processing ────────────────────────────── */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* your existing OLED toggle */
        case KC_OLED_ANIM:
            if (record->event.pressed) {
                ANIM_START = !ANIM_START;
                ENABLE_RAINBOW = !ENABLE_RAINBOW;
            } else {
                oled_clear();
            }
            return false;

        /* your existing VS Code / mac shortcuts */
        case KC_OPTION_CMD_LBRACKET:
            if (record->event.pressed) { register_code(KC_LALT); register_code(KC_LGUI); register_code(KC_LBRC); }
            else { unregister_code(KC_LBRC); unregister_code(KC_LGUI); unregister_code(KC_LALT); }
            return false;

        case KC_OPTION_CMD_RBRACKET:
            if (record->event.pressed) { register_code(KC_LALT); register_code(KC_LGUI); register_code(KC_RBRC); }
            else { unregister_code(KC_RBRC); unregister_code(KC_LGUI); unregister_code(KC_LALT); }
            return false;

        case KC_C_S_RIGHT:
            if (record->event.pressed) { register_code(KC_LCTL); register_code(KC_LSFT); register_code(KC_RIGHT); }
            else { unregister_code(KC_RIGHT); unregister_code(KC_LSFT); unregister_code(KC_LCTL); }
            return false;

        case KC_CMD_SHIFT_BS:
            if (record->event.pressed) { register_code(KC_LGUI); register_code(KC_LSFT); register_code(KC_BSLS); }
            else { unregister_code(KC_BSLS); unregister_code(KC_LSFT); unregister_code(KC_LGUI); }
            return false;

        case KC_CMD_P:
            if (record->event.pressed) { register_code(KC_LGUI); register_code(KC_P); }
            else { unregister_code(KC_P); unregister_code(KC_LGUI); }
            return false;

        case KC_CMD_SHIFT_P:
            if (record->event.pressed) { register_code(KC_LGUI); register_code(KC_LSFT); register_code(KC_P); }
            else { unregister_code(KC_P); unregister_code(KC_LSFT); unregister_code(KC_LGUI); }
            return false;

        case KC_OPTION_CMD_SLSH:
            if (record->event.pressed) { register_code(KC_LALT); register_code(KC_LGUI); register_code(KC_SLSH); }
            else { unregister_code(KC_SLSH); unregister_code(KC_LGUI); unregister_code(KC_LALT); }
            return false;

        /* new: Raycast & Magnet */
        case RAYCAST:
            if (record->event.pressed) tap_code16(LGUI(KC_SPC));  // Cmd+Space
            return false;

        case MG_LEFT:
            if (record->event.pressed) tap_code16(LCTL(LALT(KC_LEFT)));  // Ctrl+Opt+Left
            return false;

        case MG_RIGHT:
            if (record->event.pressed) tap_code16(LCTL(LALT(KC_RGHT)));  // Ctrl+Opt+Right
            return false;

        case MG_FULL:
            if (record->event.pressed) tap_code16(LCTL(LALT(KC_F)));     // Ctrl+Opt+F
            return false;

        default:
            return true;
    }
}
