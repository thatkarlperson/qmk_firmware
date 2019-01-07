#include QMK_KEYBOARD_H
#include "version.h"

#define _BASE 0 // default layer
#define _LOWER 1 // symbols
#define _RAISE 2 // media keys

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD,
  LOWER,
  RAISE
};

// Alt doubles as Tab; Ctrl as Enter.
#define LATAB LALT_T(KC_TAB)
#define RATAB RALT_T(KC_TAB)
#define LCTEN LCTL_T(KC_ENT)
#define RCTEN RCTL_T(KC_ENT)

// Terminal switching keys
#define TM_LEFT LSFT(KC_LEFT)
#define TM_RGHT LSFT(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc/`  |   1  |   2  |   3  |   4  |   5  |TmLeft|           |TmRght|   6  |   7  |   8  |   9  |   0  |  Bksp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | LAltTab|   Q  |   W  |   F  |   P  |   G  | PgUp |           | Home |   J  |   L  |   U  |   Y  |   ;  |RAltTab |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |RCtrlEnt|
 * |--------+------+------+------+------+------| PgDn |           |  End |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGui | LApp | LAlt | RAISE| LOWER|                                       | Enter|   -  |   =  |  \   | RGui |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Left  | Right|       |  `   |   '   |
 *                                 ,------|------|------|       |------+-------+------.
 *                                 |      |      | Up   |       |  [   |       |      |
 *                                 | Space|Backsp|------|       |------| Enter |Space |
 *                                 |      |ace   | Down |       |  ]   |       |      |
 *                                 `--------------------'       `---------------------'
 */
[_BASE] = LAYOUT_ergodox(
  // left hand
  KC_GESC,         KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    TM_LEFT,
  LATAB,           KC_Q,        KC_W,          KC_F,    KC_P,    KC_G,    KC_PGUP,
  LCTEN,           KC_A,        KC_R,          KC_S,    KC_T,    KC_D,
  KC_LSFT,         KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    KC_PGDN,
  KC_LGUI,         KC_APP,      KC_LALT,   RAISE, LOWER,
                                                                 KC_LEFT, KC_RIGHT,
                                                                          KC_UP,
                                                         KC_SPC, KC_BSPC, KC_DOWN,
  // right hand
  TM_RGHT,     KC_6,    KC_7,    KC_8,    KC_9,        KC_0,           KC_BSPC,
  KC_HOME,      KC_J,    KC_L,    KC_U,    KC_Y,        KC_SCLN,       RATAB,
                KC_H,    KC_N,    KC_E,    KC_I,        KC_O,           RCTEN,
  KC_END,       KC_K,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,        KC_RSFT,
  KC_ENTER,     KC_MINS, KC_EQL,  KC_BSLS, KC_RGUI,
  KC_GRV, KC_QUOT,
  KC_LBRC,
  KC_RBRC, KC_ENTER, KC_SPC
),
/* Keymap 1: LOWER Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |    `    |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Version |      |      |  Up  |      |      |      |           |      |      |   '  |   "  |   [  |   ]  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Debug  |      | Left | Down | Right|      |------|           |------|   -  |   +  |   =  |   {  |  }   |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  EPRM   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_LOWER] = LAYOUT_ergodox(
  // left hand
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  VRSN,    KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,
  DEBUG,   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
  EPRM,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               RGB_MOD, KC_TRNS,
                                                        KC_TRNS,
                                      RGB_VAD, RGB_VAI, KC_TRNS,
  // right hand
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_TRNS, KC_QUOT, KC_DQUO, KC_LBRC, KC_RBRC, KC_F12,
           KC_MINS, KC_PLUS, KC_EQL,  KC_LCBR, KC_RCBR, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  RGB_TOG, RGB_SLD,
  KC_TRNS,
  KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_RAISE] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                    KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WBAK
),
};

/*
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(LOWER)                // FN1 - Momentary Layer 1 (Symbols)
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;

    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
