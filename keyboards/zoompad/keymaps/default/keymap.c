#include "kb.h"

enum preonic_layers {
  _BASE,
  _LOWER,
  _UPPER
};

enum preonic_keycodes {
  EDOWN = SAFE_RANGE,
  EUP,
  EBASE,
  ZMUTE,
  WINL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_zoom(
		EDOWN, WINL, KC_MPLY, KC_MNXT, ZMUTE, EUP),
	
	[_LOWER] = LAYOUT_zoom(
		_______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EBASE),

	[_UPPER] = LAYOUT_zoom(
		EBASE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case EDOWN:
			if(record->event.pressed) {
				layer_clear();
				layer_on(_LOWER);
			}
			return false;
			break;
		case EUP:
			if(record->event.pressed) {
				layer_clear();
				layer_on(_UPPER);
			}
			return false;
			break;
		case EBASE:
			if(record->event.pressed) {
				layer_clear();
				layer_on(_BASE);
			}
			return false;
			break;
		case ZMUTE:
			if(record->event.pressed) {
				SEND_STRING(SS_LALT("a"));
			}
			return false;
			break;
		case WINL:
			if(record->event.pressed) {
				SEND_STRING(SS_LGUI("l"));
			}
	}
	return true;
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
		case _UPPER:
            oled_write_P(PSTR("Upper\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    } else if (index == 1) { /* Second encoder */
		if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}