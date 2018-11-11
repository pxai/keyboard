#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_spanish.h"
// based on https://github.com/johgh/keyboard/blob/master/ergodox/dvorak_spanish/keymap.c

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define ES_ATIL 3 // á

// MACROS
#define OBRACE 0 // key { or shift
#define CBRACE 1 // key } or shift
#define OBRACK 2 // key [ or left alt
#define CBRACK 3 // key ] or left alt
#define MRALT   4 // key left or RALT
#define CAPS 5 // caps lock
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 90
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};
static uint16_t key_timer;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
*
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  |  TAB |           | BSPC |   6  |   7  |   8  |   9  |   0  |   "    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  º/ª | |   Q  |   W  |   E  |   R  |   T  |  {   |           |  }   |   Y  |   U  |   I  |   O  |   P  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ñ  | tilde  |
 * |--------+------+------+------+------+------|  (   |           |  )   |------+------+------+------+------+--------|
 * |   LSft |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   -  |  RSft  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | chang| CTRL | ALT  | [    |   ]  |                                       | LEFT | DOWN |  UP  |RIGHT |  ¡¿   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  <   |  =   |       |   /  |  >   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  +   |       |  -   |        |      |
 *                                 |SPACE |ENTER |------|       |------|   ;    | SPACE|
 *                                 |      |      |  *   |       |  _   |        |      |
 *                                 `--------------------'       `----------------------'
 *  CAG = CTRL-ALT-GUI
 *   CA = CTRL-ALT
 *   SA = SHIFT-ALT
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
          KC_ESC,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_TAB,
          KC_GRAVE,        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   M(OBRACE),
          KC_RALT,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
          KC_LSFT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   LSFT(KC_8),
          KC_FN1,      KC_LCTL,KC_LALT,M(OBRACK),M(CBRACK),
                                                                    KC_NONUS_BSLASH,  KC_RPRN,
                                                                      ALL_T(KC_RBRACKET),
                                                                      KC_SPC,KC_ENT,KC_PAST,
          // right hand
                      KC_BSPC,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   LSFT(KC_2),
                      M(CBRACE),   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_MINUS,
                                 KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,CTL_T(KC_QUOTE),
                      LSFT(KC_9),   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                                         KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_EQL,
          KC_PSLS, LSFT(KC_NONUS_BSLASH),
          KC_SLSH,
          LSFT(KC_SLSH),LSFT(KC_COMM), KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |ENTER |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |  -   |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_PIPE,M(ES_ATIL),KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_BSLS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_GRV,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          KC_FN1, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_ENT, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_SLSH,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
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
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_FN1, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case OBRACE: {
    if (record->event.pressed) {
        key_timer = timer_read();
        register_code(KC_RSFT);
    } else {
        unregister_code(KC_RSFT);
      //  if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
            register_code(KC_RALT);
            register_code(KC_QUOTE);
            unregister_code(KC_QUOTE);
            unregister_code(KC_RALT);
      //  }
    }
    break;
    }
    case CBRACE: {
        if (record->event.pressed) {
            key_timer = timer_read();
            register_code(KC_RSFT);
        } else {
            unregister_code(KC_RSFT);
        //    if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                register_code(KC_RALT);
                register_code(KC_BSLS);
                unregister_code(KC_BSLS);
                unregister_code(KC_RALT);
        //    }
        }
        break;
    }
    case OBRACK: {
        if (record->event.pressed) {
            key_timer = timer_read();
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
          //  if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                register_code(KC_RALT);
                register_code(KC_LBRACKET);
                unregister_code(KC_LBRACKET);
                unregister_code(KC_RALT);
          //  }
        }
        break;
    }
    case CBRACK: {
        if (record->event.pressed) {
            key_timer = timer_read();
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
            // if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                register_code(KC_RALT);
                register_code(KC_RBRACKET);
                unregister_code(KC_RBRACKET);
                unregister_code(KC_RALT);
            // }
        }
        break;
    }
    case MRALT: {
        if (record->event.pressed) {
            key_timer = timer_read();
            register_code(KC_RALT);
        } else {
            unregister_code(KC_RALT);
            if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                register_code(KC_F12);
                unregister_code(KC_F12);
            }
        }
        break;
    }
    case CAPS: {
        if (record->event.pressed) {
            register_code(KC_CAPSLOCK);
        } else {
            unregister_code(KC_CAPSLOCK);
        }
        break;
    }
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

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
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
