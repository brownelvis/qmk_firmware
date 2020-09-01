/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _SYS 3

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SYS MO(_SYS)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLASH,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT,KC_DOWN,KC_RIGHT,
                      KC_PGUP,KC_PGDN,                                                       KC_LEFT, KC_UP,
                                      RAISE,KC_SPC,                           KC_ENT, LOWER,
                                      OSM(MOD_RCTL), KC_DEL,                  KC_BSPACE, OSM(MOD_RALT),
                                      TG(LOWER), KC_LGUI,                     KC_HOME, KC_END                        
  ),

  [_LOWER] = LAYOUT_5x6(

     KC_TILD,KC_MYCM, KC_WHOM,KC_MAIL,KC_CALC,KC_MUTE,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
     _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,KC_PLUS,KC_SLASH,
     _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
     _______,_______,_______,_______,_______,_______,                        KC_P0, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                                             KC_WBAK,KC_WFWD,            _______, _______,
                                             SYS,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______

  ),

  [_RAISE] = LAYOUT_5x6(
       KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6,                          KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 , KC_F12,
       _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_SLASH,
       _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,KC_LBRACKET,KC_RBRACKET,
       _______,  _______,_______,_______,_______,_______,                        _______, KC_PLUS,KC_MINS,KC_EQL,_______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            SYS,_______,
                                               _______,_______,            _______,_______,
                                               KC_MUTE,KC_PSCR,            KC_VOLU,KC_VOLD
  ),

  [_SYS] = LAYOUT_5x6(
       RESET,  _______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
                                             _______,_______,            _______, _______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______
  ),
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
switch(get_highest_layer(layer_state)){
case 1:
if (clockwise) {
      tap_code16(KC_VOLU);
    } else {
      tap_code16(KC_VOLD);
    }
   break;
case 2:
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
case 2:
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
default:
if (clockwise) {
      tap_code16(KC_PGDN);
    } else {
      tap_code16(KC_PGUP);
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