/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */	
    [0] = LAYOUT(
        LALT(KC_F4), MO(1), KC_MUTE,
        LCTL(KC_C), LCTL(KC_X), LCTL(KC_V),
        KC_WBAK, KC_WREF, KC_WFWD
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET, _______, KC_STOP,
        KC_MYCM, KC_WHOM, KC_MAIL,
	RGB_MODE_FORWARD, RGB_HUI, RGB_SAI
      
    ),
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
switch(get_highest_layer(layer_state)){
case 1:
if (clockwise) {
      tap_code16(KC_DOWN);
    } else {
      tap_code16(KC_UP);
    }
   break;
default:
if (clockwise) {
      tap_code16(KC_PGDN);
    } else {
      tap_code16(KC_PGUP);
    }
break;
}
}
if (index == 1) {
switch(get_highest_layer(layer_state)){
case 1:
if (clockwise) {
      tap_code16(KC_VOLU);
    } else {
      tap_code16(KC_VOLD);
    }
   break;
default:
    if (clockwise) {
  if (!is_alt_tab_active) {
    is_alt_tab_active = true;
    register_code(KC_LALT);
  }
  alt_tab_timer = timer_read();
  tap_code16(KC_TAB);
} else {
  alt_tab_timer = timer_read();
  tap_code16(S(KC_TAB));
}
   break;
}
}
}
					
#endif // ENCODER_ENABLE

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}