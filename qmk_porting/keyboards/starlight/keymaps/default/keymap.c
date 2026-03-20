/*
Copyright 2023 SharpSnail01 <https://github.com/SharpSnail01>

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

#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(/* 0: qwerty */
                     KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
                     KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_BSPC,
                     KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT,
                     MO(1),KC_LSFT, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_LPRN, KC_RPRN, KC_QUOT, KC_RCTL),
    [1] = LAYOUT_all(/* 1: fn */
                     USB_MODE, BLE_SLOT0, BLE_SLOT1, KC_KP_1, KC_KP_2, KC_KP_3, KC_PAST, KC_PPLS, KC_PEQL, _______,
                     BLE_ALL_CLEAR, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_NUHS, KC_PMNS, _______, _______,
                     _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, KC_SCLN, KC_SCLN, _______,
                     _______, _______, _______, KC_PSLS, _______, _______, KC_9,    KC_0,    KC_7,    _______),

};

