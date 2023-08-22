/*TO DO
* Test if layer-toggle can work with quantum modifier (TG(layer) on _QMM; in macro return true and set quantum_modifier = get layer; on release reverse layer quantum_modifier)
* Figure out logic for _MUN layer
* Figure out CAD-mode
* Evaluate whether customshift feature is still required in combination with comboshift feature.
*/

#include QMK_KEYBOARD_H

////BASIC DEFINITIONS////
//Layers//
enum layers {
    _QTY = 0, //QwerTY
    _QMM = 2, //QuantuM Modifier
    _NUM = 4, //NUMbers and symbols
    //_MUN = 5, //symbols and NUMbers (left right reversed)
    _NAV = 6, //NAVigation
    _OTH = 8, //OTHer

};

//Custom keycodes//
//Tap-hold keys:                 //tap _ hold
#define DEL_NUM LT(_NUM, KC_DEL) //DEL _ number layer
#define BSP_NAV LT(_NAV, KC_BSPC)//BSPC _ navigation layer
#define QM_MOD  LT(_QMM, KC_SPC) //Quantum modifier, further defined in macro
#define QMrMOD  LT(_QMM, KC_SPC)
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
        QM_OTH, //quatum layer-modifiers
        SFTLOCK, CTLLOCK, RALTLCK, //quantum mod lock keys
};

//Combos//
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Qwerty:
  [_QTY] = LAYOUT_Wimads(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    DH_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                        BSP_NAV, QM_MOD,  DEL_NUM,          DEL_NUM, QMrMOD,  BSP_NAV
  ),
  //Quantum modifier
  [_QMM] = LAYOUT_Wimads(
      QM_OTH,  RALTLCK, CTLLOCK, SFTLOCK, XXXXXXX,          XXXXXXX, SFTLOCK, CTLLOCK, RALTLCK, QM_OTH,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, CW_TOGG,          CW_TOGG, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
      KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, KC_CAPS,          KC_CAPS, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
                        XXXXXXX, XXXXXXX, QM_MUN,           QM_MUN,  XXXXXXX, XXXXXXX
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_Wimads(
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, DH_TILD,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, DH_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        KC_UNDS, _______, _______,          _______, _______, KC_0
  ),
  //Navigation:
  [_NAV] = LAYOUT_Wimads(
      KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
      KC_MUTE, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,          XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, KC_MUTE,
                        _______, _______, _______,          _______, _______, _______
  ),
  //OTHER:
  [_OTH] = LAYOUT_Wimads(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PSCR,
      XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  LC_MENU, XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),

};//.keymaps

////CUSTOM KEY BEHAVIOURS////
//Combos per layer//
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case QTY_CS ... QTYrDRT:
            if (_QAI == get_highest_layer(default_layer_state)){
                return false;
            } return true;
        case QAI_Q ... QAI_DRTG:
            if (_QTY == get_highest_layer(default_layer_state)) {
                return false;
            } return true;
    }
    return true;
};

//Tap-hold per key config//
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DH_QUOT:
        case DH_GRV:
        case DH_TILD:
        case DH_CIRC:
            return 200; //to be tweaked still

        case QM_MOD:
        case QMrMOD:
            return 200; //to be tweaked still

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
    static uint16_t quantum_modifier = 0; // 0 = collapsed; 1 = in superposition; [keycode] = entangled
    switch(keycode) {
        //general keycodes
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear();    //clears all layers that might be stuck
                quantum_modifier = 0; //reset quantum modifier
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

        //Quantum modifiers:
        case QM_MOD: //quantum modifier
            if (record->event.pressed && record->tap.count && quantum_modifier == 0) { //when tapped && quantum_modifier NOT active
                return true; //KC_SPC
            } else if (record->event.pressed && !record->tap.count && quantum_modifier == 0) { //when held && quantum_modifier NOT active
                //activate quantum_modifier:
                quantum_modifier = 1; //quantum modifier in superposition
                layer_on(_QMM);        //next keypress in _QMM layer determines final state of quantum modifier
            } else if (record->event.pressed) { //when tapped or held && quantum_modifier IS active
                //cancel quantum_modifier:
                unregister_code16(quantum_modifier);
                layer_off(quantum_modifier);
                layer_off(_QMM);
                quantum_modifier = 0; //collapse superposition/entanglement
            } else { //on key release
                if (quantum_modifier != 2) {
                    //cancel quantum modifier:
                    unregister_code16(quantum_modifier);
                    layer_off(quantum_modifier);
                    layer_off(_QMM);       //necessary in case no subsequent key was pressed on _QMM layer
                    quantum_modifier = 0; //collapse superposition/entanglement
                } //if == 2, quantum modifier is locked; tap once more to cancel.
            } return false;
        case KC_LSFT:    case KC_RSFT:    case S(KC_RSFT):
        case KC_LCTL:    case KC_RCTL:    case C(KC_RCTL):
        case KC_LALT:    case KC_RALT:    case A(KC_RALT):
        case KC_LGUI:    case KC_RGUI:
        case S(KC_LCTL): case S(KC_LALT): case S(KC_LGUI):
        case C(KC_LALT): case C(KC_LGUI): case A(KC_LGUI):
        case KC_MEH:     case KC_HYPR:
            if (record->event.pressed && quantum_modifier == 1) { //when pressed && in superposition
                register_code16(keycode);
                layer_off(_QMM);
                quantum_modifier = keycode; //entangle QM_MOD with [keycode]
            } return false;
        case QM_OTH:
            if (record->event.pressed && quantum_modifier == 1) {
                layer_on(_OTH);
                layer_off(_QMM);
                quantum_modifier = _OTH;
            } return false;
        case CW_TOGG: case: KC_CAPS:
            if (record->event.pressed && quantum_modifier == 1) { //when pressed && in superposition
                return true;
                layer_off(_QMM);
                quantum_modifier = 0; //collapse superposition
            } return false;
        case SFTLOCK:
            if (record->event.pressed && quantum_modifier == 1) {
                register_code16(KC_LSFT);
                layer_off(_QMM);
                quantum_modifier = 2; //so mod doesn't get unregistered on release;
            } return false;
        case CTLLOCK:
            if (record->event.pressed && quantum_modifier == 1) {
                register_code16(KC_LCTL);
                layer_off(_QMM);
                quantum_modifier = 2; //so mod doesn't get unregistered on release;
            } return false;
        case RALTLCK:
            if (record->event.pressed && quantum_modifier == 1) {
                register_code16(KC_RALT);
                layer_off(_QMM);
                quantum_modifier = 2; //so mod doesn't get unregistered on release;
            } return false;

        //Dead-hold keys:
        case DH_QUOT: //works for both ['] and ["] (except when ["] is accessed via combo, because then shift is not activated)
            if (record->event.pressed && !record->tap.count) { //if tapped, behave as normal key
                tap_code16(KC_QUOT); tap_code16(KC_SPC);
            } else if (record->event.pressed) { //if held, behave as dead key
                tap_code16(KC_QUOT);
                if (mod_shift) {unregister_mods(mod_shift);} //unregister shift to resolve conflict of holding shifted dead key
            } return false;
        case DH_DQOT: //workaround for combo-["]
            if (record->event.pressed && !record->tap.count) { //if tapped, behave as normal key
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

////LED INDICATORS////
//TBD
