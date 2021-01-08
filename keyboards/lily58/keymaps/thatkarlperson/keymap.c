#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _COLEMAK = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
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

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LATAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, RATAB,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTEN,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    RCTEN,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS,          KC_QUOT, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴─────┬──┴──────┬─┴──────┬─┴─────┬──┴──────┬─┘        └─┬──────┴─┬──────┴─┬──────┴────┬───┴────┬───┴────────┴────────┘
                             KC_LGUI, MO(_RAISE),MO(_LOWER),KC_SPC,            KC_SPC,  KC_ENT,  KC_BSLS,    KC_RGUI
                         // └─────────┴────────┴────────┴────────┘            └────────┴────────┴───────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
     KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
     _______, KC_DQUO, KC_QUOT, KC_UP,   KC_LT,   KC_GT,                              _______, KC_QUOT, KC_DQUO, KC_LBRC, KC_RBRC, KC_PIPE,
     _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_UNDS,                            KC_MINS, KC_PLUS, KC_EQL,  KC_LCBR, KC_RCBR, KC_BSLS,
     _______, _______, _______, _______, _______, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, _______, KC_COMM, KC_DOT,  KC_BSLS, KC_PAST,
                            _______, _______, _______, KC_DEL,                    KC_DEL,  _______, _______, _______
  ),


  [_RAISE] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
     _______, KC_EXLM, KC_AT,   KC_PGUP, KC_DLR,  KC_PERC,                            _______, KC_P7,   KC_P8,   KC_P9,   KC_COLN, _______,
     _______, _______, KC_HOME, KC_PGDN, KC_END , KC_UNDS,                            KC_MINS, KC_P4,   KC_P5,   KC_P6,   KC_QUOT, KC_BSLS,
     _______, _______, _______, _______, _______, KC_MINS, KC_LPRN,          KC_RPRN, KC_UNDS, KC_P1,   KC_P2,   KC_P3,   KC_PIPE, _______,
                            _______,  _______, _______, _______,                   _______, _______, KC_P0, _______
  ),

  [_ADJUST] = LAYOUT(
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     DEBUG,   _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
     RESET,   _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
                            _______, _______, _______, TM_LEFT,                   TM_RGHT, _______, _______, _______

  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
