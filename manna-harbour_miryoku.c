// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


// tapping term per key
#undef TAPPING_TERM
#define TAPPING_TERM 230 //220 on choc corne
#define TAPPING_TERM_SHIFT 200
#define TAPPING_TERM_THUMB 170

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_T(KC_ESC):
            return TAPPING_TERM_THUMB;
        case LT(U_NAV,KC_SPC):
            return TAPPING_TERM_THUMB;
        case LT(U_MOUSE,KC_TAB):
            return TAPPING_TERM_THUMB;
        case LT(U_SYM,KC_ENT):
            return TAPPING_TERM_THUMB;
        case LT(U_NUM,KC_BSPC):
            return TAPPING_TERM_THUMB;
        case LT(U_FUN,KC_DEL):
            return TAPPING_TERM_THUMB;

        case LSFT_T(KC_T):
            return TAPPING_TERM_SHIFT;
        case LSFT_T(KC_N):
            return TAPPING_TERM_SHIFT;
        default:
            return TAPPING_TERM;
    }
}


// thumb combos

// #if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
const uint16_t PROGMEM thumbcombos_sym[] = {KC_EXLM, KC_AT, COMBO_END};
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};

const uint16_t PROGMEM combos_cmdf[] = {KC_F, LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdz[] = {LCTL_T(KC_A), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdx[] = {LALT_T(KC_R), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdc[] = {LGUI_T(KC_S), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdv[] = {LSFT_T(KC_T), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmda[] = {LT(U_BUTTON,KC_Z), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdr[] = {ALGR_T(KC_X), LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmds[] = {KC_C, LT(U_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM combos_cmdt[] = {KC_D, LT(U_NAV,KC_SPC), COMBO_END};

const uint16_t PROGMEM combos_volu[] = {LSFT_T(KC_N), LT(U_NUM,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combos_vold[] = {LGUI_T(KC_E), LT(U_NUM,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combos_briu[] = {KC_H, LT(U_NUM,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combos_brid[] = {KC_COMM, LT(U_NUM,KC_BSPC), COMBO_END};
combo_t key_combos[] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, CMD_T(KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  COMBO(thumbcombos_sym, KC_AMPR),
  COMBO(thumbcombos_fun, KC_APP),
  COMBO(combos_cmdf, LCMD(KC_F)),
  COMBO(combos_cmdz, LCMD(KC_Z)),
  COMBO(combos_cmdx, LCMD(KC_X)),
  COMBO(combos_cmdc, LCMD(KC_C)),
  COMBO(combos_cmdv, LCMD(KC_V)),
  COMBO(combos_cmda, LCMD(KC_A)),
  COMBO(combos_cmdr, LCMD(KC_R)),
  COMBO(combos_cmds, LCMD(KC_S)),
  COMBO(combos_cmdt, LCMD(KC_T)),
  COMBO(combos_volu, KC_VOLU),
  COMBO(combos_vold, KC_VOLD),
  COMBO(combos_briu, KC_BRIU),
  COMBO(combos_brid, KC_BRID),
};
