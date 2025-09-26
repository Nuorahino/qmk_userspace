// TODO Settings and MEDIA layer

/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

typedef struct TapHolds {
  uint16_t  tap_code;
  uint16_t  hold_code;
} TapHold;


#define KEY_1 LALT_T(KC_F1)
#define KEY_2 LCTL_T(KC_F2)
#define KEY_3 LGUI_T(KC_F3)
#define KEY_4 RGUI_T(KC_F4)
#define KEY_5 RCTL_T(KC_F5)
#define KEY_6 RALT_T(KC_F6)

#define KEY_11 LALT_T(KC_F11)
#define KEY_12 LCTL_T(KC_F12)
#define KEY_13 LGUI_T(KC_F13)
#define KEY_14 RGUI_T(KC_F14)
#define KEY_15 RCTL_T(KC_F15)
#define KEY_16 RALT_T(KC_F16)

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUMBERS,
    LAYER_SYMBOLS,
    LAYER_MOUSE,
    LAYER_SETTINGS,
    LAYER_MEDIA,
};


#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define ESC_SYM LT(LAYER_SYMBOLS, KC_ESC)
#define TAB_FUN LT(LAYER_MEDIA, KC_TAB)
#define ENT_NUM LT(LAYER_NUMBERS, KC_ENT)
#define BSP_SFT MT(MOD_LSFT, KC_BSPC)
#define SPC_RSF MT(MOD_RSFT, KC_SPC)

#define __________THUMB_ROW__________ TAB_FUN, BSP_SFT, ESC_SYM, ENT_NUM, SPC_RSF

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M, KC_COMM,  KC_DOT,    KC_SLSH, \
                                      __________THUMB_ROW__________

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_NUMBERS                                                                    \
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, \
       KC_MINUS,    KEY_1,    KEY_2,    KEY_3,    KC_EQUAL,    KC_PLUS,    KEY_4,    KEY_5,    KEY_6, KC_UNDS, \
        KC_NO, KC_NO, KC_COPY, KC_PASTE, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_PSCR, \
                                      __________THUMB_ROW__________
// TODO: Check if there is more stuff, that should be inserted into the bottom row

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                  \
    LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), \
   KC_MINUS,    KEY_11,    KEY_12,    KEY_13,    KC_NUHS,    LSFT(KC_NUHS),    KEY_14,    KEY_15,    KEY_16, KC_UNDS, \
       KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,    KC_DELETE,    KC_INSERT,    KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, \
                                      __________THUMB_ROW__________


/**
 * \brief Mouse layout
 */
#define LAYOUT_LAYER_MOUSE                                                                    \
   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, \
    KC_NO,    KC_LALT,    KC_LCTL,    KC_LGUI,  KC_NO, KC_NO,    MS_BTN1,    MS_BTN3,    MS_BTN2,  KC_NO, \
   KC_F11,    KC_F12,    KC_F13,    KC_F14,    KC_F15,    KC_NO,    DPI_MOD,    DPI_RMOD,    S_D_MOD,    S_D_RMOD, \
                       DRGSCRL,    MOD_LSFT, SNIPING, MO(LAYER_MEDIA), MO(LAYER_SETTINGS)
//TODO: Thumb keys should be mod keys or such



// Until here most of the things are updated.


/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */
/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
#define LAYOUT_LAYER_MEDIA                                                                    \
    XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, \
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT, QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, KC_MPLY, KC_MSTP, KC_TRNS, KC_TRNS
//
//                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_SETTINGS                                                               \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    _______________DEAD_HALF_ROW_______________,  _______________DEAD_HALF_ROW_______________, \
                      XXXXXXX, _______, XXXXXXX,  KC_TRNS, KC_TRNS

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LT(LAYER_MOUSE, L10), LALT_T(L11), LCTL_T(L12), LGUI_T(L13),        L14,  \
             R15,  RGUI_T(R16), RCTL_T(R17), RALT_T(R18), LT(LAYER_MOUSE, R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)
  ),
  [LAYER_NUMBERS] = LAYOUT_wrapper(LAYOUT_LAYER_NUMBERS),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
  [LAYER_SETTINGS] = LAYOUT_wrapper(LAYOUT_LAYER_SETTINGS),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KEY_1:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_LCBR);
        }
        return false;
      }
      break;

    case KEY_2:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_LBRC);
        }
        return false;
      }
      break;

    case KEY_3:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_LPRN);
        }
        return false;
      }
      break;

    case KEY_4:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_RPRN);
        }
        return false;
      }
      break;

    case KEY_5:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_RBRC);
        }
        return false;
      }
      break;

    case KEY_6:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_RCBR);
        }
        return false;
      }
      break;

    case KEY_11:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_GRV);
        }
        return false;
      }
      break;

    case KEY_12:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_QUOT);
        }
        return false;
      }
      break;

    case KEY_13:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(KC_NUBS);
        }
        return false;
      }
      break;

    case KEY_14:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(LSFT(KC_NUBS));
        }
        return false;
      }
      break;

    case KEY_15:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(LSFT(KC_QUOT));
        }
        return false;
      }
      break;

    case KEY_16:
      if (record->tap.count) {
        if (record->event.pressed) {
          tap_code16(LSFT(KC_GRV));
        }
        return false;
      }
      break;
  }
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_RSFT, KC_SPC):
          return 140;
        case MT(MOD_LSFT, KC_BSPC):
          return 140;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode) {
//if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        switch (keycode) {
            case MT(MOD_RSFT, KC_SPC):
              return FLOW_TAP_TERM - 200;  // Short timeout on these keys.
            case MT(MOD_LSFT, KC_BSPC):
              return FLOW_TAP_TERM - 200;  // Short timeout on these keys.

            default:
              return FLOW_TAP_TERM;  // Longer timeout otherwise.
        }
//    }
    return 0;  // Disable Flow Tap.
}


bool is_flow_tap_key(uint16_t keycode) {
    switch (keycode) {
        case LT(LAYER_MOUSE, KC_A):
            return true;
        case LALT_T(KC_R):
            return true;
        case LCTL_T(KC_S):
            return true;
        case LGUI_T(KC_T):
            return true;
        case KC_D:
            return true;
        case KC_H:
            return true;
        case RGUI_T(KC_N):
            return true;
        case RCTL_T(KC_E):
            return true;
        case RALT_T(KC_I):
            return true;
        case LT(LAYER_MOUSE, KC_O):
            return true;
/*
        case KC_L1 ... KC_L6:
            return true;
        case KC_L11 ... KC_L16:
            return true;
*/
    }
    return false;
}
