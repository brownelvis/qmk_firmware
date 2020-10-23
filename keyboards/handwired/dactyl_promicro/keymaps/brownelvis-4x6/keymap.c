#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define ONE_GRV LT(1,KC_GRAVE)
#define CTL_Z LCTL_T(KC_Z)
#define ALT_SHFT LALT(KC_LSFT)
#define ALT_MENU LALT_T(KC_MENU)
#define LG_QUOT LGUI_T(KC_QUOT)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_SLS LCTL_T(KC_SLSH)
#define LT2_COL LT(_RAISE, KC_SCLN)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_4x6(
        KC_ESC , KC_Q  ,KC_W   , KC_E  , KC_R  , KC_T  ,                                        KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
        KC_TAB , KC_A  ,KC_S   , KC_D  , KC_F  , KC_G  ,                                        KC_H   , KC_J  , KC_K  , KC_L  ,LT2_COL,LG_QUOT,
        KC_LSFT, CTL_Z ,KC_X   , KC_C  , KC_V  , KC_B  ,                                        KC_N   , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LALT,KC_MENU,OSL(LOWER),                                                     KC_LEFT,KC_UP,KC_DOWN,KC_RIGHT,KC_RCTL,
                                                       ALT_MENU,KC_LGUI,       KC_LBRC,KC_RBRC,
                                                LOWER, KC_SPC  ,KC_DEL ,       KC_BSPC,KC_ENT ,RAISE
                                                                       
    ),
    [_LOWER] = LAYOUT_4x6(
        KC_TILD, KC_1  ,KC_2   , KC_3  , KC_4  , KC_5  ,                                       KC_6   , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
        _______,KC_EXLM,KC_AT  ,KC_LBRC,KC_RBRC,KC_PIPE,                                       KC_UP  ,KC_P4  ,KC_P5  ,KC_P6  ,KC_PAST,_______,
        _______,KC_HASH,KC_DLR ,KC_LPRN,KC_RPRN,KC_GRV ,                                       KC_DOWN,KC_P1  ,KC_P2  ,KC_P3  ,KC_PPLS,_______,
        RESET,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,                                                         KC_PDOT,KC_P0  ,KC_PEQL  ,KC_PSLS,_______,
                                                        _______,_______,       _______,_______,
                                                _______,_______,_______,       _______,_______,_______
    ),
    [_RAISE] = LAYOUT_4x6(
        KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,                                       KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,
        RGB_TOG, RGB_MODE_FORWARD, RGB_MODE_REVERSE, RGB_HUD, RGB_HUI,_______,                 _______,_______,KC_MPRV,KC_MNXT,_______,KC_MPLY,
        RGB_MODE_PLAIN,RGB_VAD,RGB_VAI,RGB_SAD,RGB_SAI,_______,                                KC_WBAK,KC_VOLU,KC_VOLD,KC_MUTE,_______,_______,
        RESET  ,_______,_______,_______,_______,                                               KC_HOME,KC_PGUP,KC_PGDN,KC_END,_______,
                                                        _______,_______,       _______,_______,
                                                _______,_______,_______,       _______,_______,_______
    )
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