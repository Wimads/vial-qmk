/*TO DO
* further work out CAD mode
* work out capsword in CAD mode
* fix bug with capsword LED blink in CAD mode (colors don't interact properly)
*/

#include QMK_KEYBOARD_H

////BASIC DEFINITIONS////
//Layers//
enum layers {
    _QTY = 0, //QwerTY
    _CAD = 1, //CAD mode
    _NUM = 2, //NUMbers and symbols
    _DAC = 3, //CAD reversed
    _NAV = 4, //NAVigation
    _OTH = 6, //OTHer; above _MML, because _OTH is accessed from _MML.
};

//Custom keycodes//
//Tap-hold keys:                 //tap _ hold
#define DEL_RLT RALT_T(KC_DEL) //DEL _ number layer
#define BSP_NAV LT(_NAV, KC_BSPC)//BSPC _ navigation layer
#define DEL_CTL LCTL_T(KC_DEL)
#define BSP_ALT LALT_T(KC_BSPC)
#define FFF_NUM LT(_NUM, KC_F)
#define JJJ_NUM LT(_NUM, KC_J)
#define SPC_SFT LSFT_T(KC_SPC)
#define AAA_NAV LT(_NAV, KC_A)
//Bottom row mods:
#define XXX_ALT LALT_T(KC_X)
#define CCC_CTL LCTL_T(KC_C)
#define VVV_SFT LSFT_T(KC_V)
#define ZZZ_GUI LGUI_T(KC_Z)
//Dead-hold keys:                //normal on tap, dead key on hold; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define DH_QUOT LT(11, KC_QUOT)  //further defined in macro
#define DH_DQOT LT(12, KC_QUOT)  //further defined in macro
#define DH_GRV  LT(11, KC_GRV)   //further defined in macro
#define DH_TILD LT(12, KC_TILD)  //further defined in macro
#define DH_CIRC LT(12, KC_CIRC)  //further defined in macro
//Other:
#define DOTCOMM LT(10, KC_DOT)   //KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
//Macros:
enum custom_keycodes {
        CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
        CADTOGG,
    };

//Combos//
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Qwerty:
  [_QTY] = LAYOUT_split_3x5_3(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      AAA_NAV, KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    DH_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                        BSP_ALT, SPC_SFT, DEL_CTL,          DEL_RLT, SPC_SFT, BSP_NAV
  ),
  //CAD mode:
  [_CAD] = LAYOUT_split_3x5_3(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      AAA_NAV, KC_S,    KC_D,    FFF_NUM, KC_G,             KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      ZZZ_GUI, XXX_ALT, CCC_CTL, VVV_SFT, KC_B,             KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        BSP_ALT, SPC_SFT, DEL_CTL,          _______, KC_0,    DOTCOMM
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_split_3x5_3(
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, DH_TILD,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, DH_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        _______, _______, _______,          _______, KC_0,    DOTCOMM
  ),
  //DAC (inverted CAD):
  [_DAC] = LAYOUT_split_3x5_3(
      KC_PERC, KC_9,    KC_8,    KC_7,    DH_CIRC,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_MINS, KC_6,    KC_5,    KC_4,    KC_PLUS,          KC_H,    JJJ_NUM, KC_K,    KC_L,    DH_QUOT,
      KC_SLSH, KC_3,    KC_2,    KC_1,    KC_ASTR,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                        KC_0, OSM(KC_LSFT), XXXXXXX,        DEL_RLT, SPC_SFT,  BSP_NAV
  ),
  //Navigation:
  [_NAV] = LAYOUT_split_3x5_3(
      KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
      KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,          KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,
                        _______, _______, _______,          _______, _______, _______
  ),
  //OTHER:
  [_OTH] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PSCR,
      XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  KC_MENU, XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
};//.keymaps

////LED INDICATORS////
//HSV values both LEDs
int rgb_hue = 152;
int rgb_sat = 255;
int rgb_val = 255;
int rgb_mode = 1;
//HSV values right LED
int rgb_hue_r = 152;
int rgb_sat_r = 255;
int rgb_val_r = 255;
int rgb_mode_r = 1;

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {2, 2, 2, 2}; // RGB breathing animation speed

void matrix_init_user(void) { // Set default lighting state
    // initiate rgb underglow (default mode as per ASW_on true):
    rgblight_enable();
    rgblight_mode(rgb_mode);                                //set light effect for both LEDs
    rgblight_set_effect_range(rgb_mode_r, 1);               //override light effect for right LED
    rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);             //set HSV value for both LEDs
    rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1); //override HSV value for right LED
};

void caps_word_set_user(bool active) {
    if (active) {
        if(IS_LAYER_ON(_CAD)) {
            rgb_mode = 2;
            rgb_mode_r = 1;
        } else if(IS_LAYER_ON(_DAC)) {
            rgb_mode = 1;
            rgb_mode_r = 2;
        } else {
            rgb_mode = 2;
            rgb_mode_r = rgb_mode;
        }
        rgblight_mode(rgb_mode);
        rgblight_set_effect_range(rgb_mode_r, 1);
        rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
        rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
    } else {
        rgb_mode = 1;
        rgb_mode_r = rgb_mode;
        rgblight_mode(rgb_mode);
        rgblight_set_effect_range(rgb_mode_r, 1);
        rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
        rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
    }
};

layer_state_t layer_state_set_user(layer_state_t state) { // Respond to layer state
    switch(biton32(state)) {
        case _NUM:
            rgb_hue = 0;
            rgb_hue_r = rgb_hue;
            rgblight_mode(rgb_mode);
            rgblight_set_effect_range(rgb_mode_r, 1);
            rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
            break;
        case _CAD:
            rgb_hue = 80;
            rgb_hue_r = 0;
            rgblight_mode(rgb_mode);
            rgblight_set_effect_range(rgb_mode_r, 1);
            rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
            break;
        case _DAC:
            rgb_hue = 0;
            rgb_hue_r = 80;
            rgblight_mode(rgb_mode);
            rgblight_set_effect_range(rgb_mode_r, 1);
            rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
            break;
        default:
            rgb_hue = 152;
            rgb_hue_r = rgb_hue;
            rgblight_mode(rgb_mode);
            rgblight_set_effect_range(rgb_mode_r, 1);
            rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue_r, rgb_sat_r, rgb_val_r, 1);
            break;
     };
    return state;
};

////CUSTOM KEY BEHAVIOURS////

//Combos per layer////provision for CAD mode, TBD
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case CAD_START ... CAD_END:
            if (!IS_LAYER_ON(_CAD)) {
                return false;
            } return true;
    }
    return true;
};


//Tap-hold per key config//
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DH_QUOT: case DH_DQOT:
        case DH_GRV:  case DH_TILD:
        case DH_CIRC:
            return TAPPING_TERM; //to be tweaked still

        default:
            return TAPPING_TERM;
    }
};

//Customshift keycodes//
typedef struct _customshift_keycode_t { //define customshift functions
    uint16_t keycode_record;  //unmodified keycode
    uint16_t keycode_shifted; //alternate keycode to output on shift
} customshift_keycode_t;

#define KEY_MAP_SIZE 22 //amount of instances in customshift map

customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
    //Numbers and F-keys
    {KC_CIRC, KC_F12},   {KC_7,    KC_F7},    {KC_8,    KC_F8},    {KC_9,    KC_F9}, //F12  F7  F8  F9
    {KC_PLUS, KC_F11},   {KC_4,    KC_F4},    {KC_5,    KC_F5},    {KC_6,    KC_F6}, //F11  F4  F5  F6
    {KC_ASTR, KC_F10},   {KC_1,    KC_F1},    {KC_2,    KC_F2},    {KC_3,    KC_F3}, //F10  F1  F2  F3
    //punctuation
    {KC_EXLM, KC_QUES},  {KC_COMM, KC_SCLN},  {KC_DOT,  S(KC_SCLN)}, // !?  ,;  .:
    //symbols
    {KC_SLSH, KC_BSLS},  {KC_PIPE, KC_BSLS},  {KC_DLR,  RALT(KC_5)}, // /\  |\  $€
    {KC_LCBR, KC_LBRC},  {KC_RCBR, KC_RBRC},  //brackets for qwertai
    //Volume and brightness
    {KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};

int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in customshift map
};

//Macros//
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    int index = get_index_customshift(keycode);// check if keycode is in customshift map
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for customshift behaviours
    static bool dotcomm_state = true; //true = dot; false = comma;
    switch(keycode) {
        //general keycodes
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear();    //clears all layers that might be stuck
            } return false;
        case DOTCOMM:
            if (record->event.pressed && record->tap.count == 2) {//swap DOTCOMM state on double tap
                dotcomm_state = !dotcomm_state; //swap state
                tap_code16(KC_BSPC);            //remove character output from first tap
            } else if (record->event.pressed && dotcomm_state) {//when state is true
                if (mod_shift) { //send comm when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_COMM);
                    register_mods(mod_shift);
                } else { //send dot by default
                    tap_code16(KC_DOT);
                }
            } else if (record->event.pressed) {//when state is false
                if (mod_shift) { //send dot when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_DOT);
                    register_mods(mod_shift);
                } else { //send comm by default
                    tap_code16(KC_COMM);
                }
            } return false;
        case CADTOGG:
            if(record->event.pressed) {
                layer_invert(_CAD);
            } return false;

        //Dead-hold keys:
        case DH_QUOT: //works for both ['] and ["] (except when ["] is accessed via combo, because then shift is not activated)
            if (record->event.pressed && record->tap.count) { //if tapped, behave as normal key
                tap_code16(KC_QUOT); tap_code16(KC_SPC);
            } else if (record->event.pressed) { //if held, behave as dead key
                tap_code16(KC_QUOT);
                if (mod_shift) {unregister_mods(mod_shift);} //unregister shift to resolve conflict of holding shifted dead key
            } return false;
        case DH_DQOT: //workaround for combo-["]
            if (record->event.pressed && record->tap.count) { //if tapped, behave as normal key
                tap_code16(S(KC_QUOT)); tap_code16(KC_SPC);
            } else if (record->event.pressed) { //if held, behave as dead key
                tap_code16(S(KC_QUOT));
            } return false;
        case DH_GRV:
            if (record->event.pressed && record->tap.count) {
                tap_code16(KC_GRV); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_GRV); layer_off(_NUM);
            } return false;
        case DH_TILD:
            if (record->event.pressed && record->tap.count) {
                tap_code16(S(KC_GRV)); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(S(KC_GRV)); layer_off(_NUM);
            } return false;
        case DH_CIRC:
            if (record->event.pressed && record->tap.count) {
                tap_code16(S(KC_6)); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(S(KC_6)); layer_off(_NUM);
            } return false;

        default:
            //Customshift: //might be redundant now that shifted characters are acessed via combos
            if (index != -1) { //if key is in customshift map, then:
                if (record->event.pressed && mod_shift) { //shifted action
                    unregister_mods(mod_shift);
                    tap_code16(keymap[index].keycode_shifted); //custom shift key
                    register_mods(mod_shift);
                    return false; //ignore default shift behaviour
                } return true; //return as normal when not shifted
            }//end of if(index != -1)
    }//end of switch(keycode)
    return true; //if key is not in customshift map or other macro, return normal key behaviour
};


