/*TO DO
* Test if layer-toggle can work with Magic modifier (TG(layer) on _MML; in macro return true and set magic_mod_state = get layer; on release reverse layer magic_mod_state)
* Figure out logic for _MUN layer
* Figure out CAD-mode
* Evaluate whether customshift feature is still required in combination with comboshift feature.
*/

#include QMK_KEYBOARD_H

////BASIC DEFINITIONS////
//Layers//
enum layers {
    _QTY = 0, //QwerTY
    _NUM = 2, //NUMbers and symbols
    //_MUN = 5, //symbols and NUMbers (left right reversed)
    _NAV = 4, //NAVigation
    _MML = 6, //Magic modifier layer; above _NUM and NAV, because mods need to be accessible from there;
    _OTH = 8, //OTHer; above _MML, because _OTH is accessed from _MML.

};

//Custom keycodes//
//Tap-hold keys:                 //tap _ hold
#define DEL_NUM LT(_NUM, KC_DEL) //DEL _ number layer
#define BSP_NAV LT(_NAV, KC_BSPC)//BSPC _ navigation layer
#define MAGIMOD LT(_MML, KC_SPC) //Magic modifier, further defined in macro
//Homerow Mods: //Redundant because of magic mods; but added for convenience (long tapping term only, to not intefere too much)
#define HM_S    LALT_T(KC_S) //Homerow Mod LALT _ S
#define HM_D    LCTL_T(KC_D) //Homerow Mod LCTL _ D
#define HM_F    LSFT_T(KC_F) //Homerow Mod LSFT _ F
#define HM_L    RALT_T(KC_L) //Homerow Mod RALT _ L
#define HM_K    RCTL_T(KC_K) //Homerow Mod RCTL _ K
#define HM_J    RSFT_T(KC_J) //Homerow Mod RSFT _ J
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
        MM_OTH, //magic layer modifier
        SFTLOCK, CTLLOCK, RALTLCK, //magic mod lock keys
};

//Combos//
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Qwerty:
  [_QTY] = LAYOUT_split_3x5_3(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    HM_S,    HM_D,    HM_F,    KC_G,             KC_H,    HM_J,    HM_K,    HM_L,    DH_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                        BSP_NAV, MAGIMOD, DEL_NUM,          DEL_NUM, MAGIMOD, BSP_NAV
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_split_3x5_3(
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, DH_TILD,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, DH_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        KC_UNDS, _______, _______,          _______, _______, KC_0
  ),
  //Navigation:
  [_NAV] = LAYOUT_split_3x5_3(
      KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
      KC_MUTE, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,          XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, KC_MUTE,
                        _______, _______, _______,          _______, _______, _______
  ),
  //Magic modifier
  [_MML] = LAYOUT_split_3x5_3(
      MM_OTH,  RALTLCK, CTLLOCK, SFTLOCK, XXXXXXX,          XXXXXXX, SFTLOCK, CTLLOCK, RALTLCK, MM_OTH,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_CAPS,          KC_CAPS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
      KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, CW_TOGG,          CW_TOGG, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
  //OTHER:
  [_OTH] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PSCR,
      XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  KC_MENU, XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
};//.keymaps

////CUSTOM KEY BEHAVIOURS////

//Combos per layer////provision for CAD mode, TBD
/*static bool CAD_mode = false;
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case CAD_ ... CAD__:
            if (!CAD_mode) {
                return false;
            }
        case NUM_ ... NUM__:
            if (CAD_mode){
                return false;
            } return true;
        case MUN_ ... MUN__:
            if (!CAD_mode) {
                return false;
            } return true;
    }
    return true;
};*/

//Tap-hold per key config//
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DH_QUOT: case DH_DQOT:
        case DH_GRV:  case DH_TILD:
        case DH_CIRC:
            return TAPPING_TERM; //to be tweaked still

        case MAGIMOD:
            return TAPPING_TERM; //to be tweaked still

        case HM_S: case HM_D: case HM_F:
        case HM_L: case HM_K: case HM_J:
            return 300;

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
    static uint16_t magic_mod_state = 0; // 0 = inactive; 1 = pre-selection; 2 = locked; [keycode] = selected
    switch(keycode) {
        //general keycodes
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear();    //clears all layers that might be stuck
                magic_mod_state = 0; //reset Magic modifier
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

        //Magic modifiers:
        case MAGIMOD:
            if (record->event.pressed && record->tap.count && magic_mod_state == 0) { //when tapped && magic modifier NOT active
                tap_code16(keycode);
            } else if (record->event.pressed && !record->tap.count && magic_mod_state == 0) { //when held && magic modifier NOT active
                //activate magic modifier:
                magic_mod_state = 1; //Magic modifier in pre-selection mode
                layer_on(_MML);      //next keypress in _MML layer determines final state of Magic modifier
            } else if (record->event.pressed) { //when tapped or held && magic modifier IS active
                //cancel magic modifier:
                if(magic_mod_state == 2){clear_mods();}
                unregister_code16(magic_mod_state); //release selected modifier, if any
                layer_off(magic_mod_state);         //release selected layer modifier, if any
                layer_off(_MML);                    //cancel _MML layer if no mod was selected yet
                magic_mod_state = 0;                //reset magic modifier status to 0, inactive
            } else { //on key release
                if (magic_mod_state != 2) { //cancel magic modifier on key release, unless its locked (state = 2)
                    unregister_code16(magic_mod_state);
                    layer_off(magic_mod_state);
                    layer_off(_MML);
                    magic_mod_state = 0;
                } //to cancel locked magic modifier, tap magic modifier once more.
            } return false;
        case KC_LSFT:    case KC_RSFT:    case S(KC_RSFT):
        case KC_LCTL:    case KC_RCTL:    case C(KC_RCTL):
        case KC_LALT:    case KC_RALT:    case A(KC_RALT):
        case KC_LGUI:    case KC_RGUI:
        case S(KC_LCTL): case S(KC_LALT): case S(KC_LGUI):
        case C(KC_LALT): case C(KC_LGUI): case A(KC_LGUI):
        case KC_MEH:     case KC_HYPR:
            if (record->event.pressed && magic_mod_state == 1) { //when pressed && in pre-selection mode
                register_code16(keycode);
                layer_off(_MML);
                magic_mod_state = keycode; //set magic modifier state to [keycode]
            } return false;
        case MM_OTH:
            if (record->event.pressed && magic_mod_state == 1) {
                layer_on(_OTH);
                layer_off(_MML);
                magic_mod_state = _OTH; //set magic modifier state to [layer]
            } return false;
        case CW_TOGG: case KC_CAPS:
            if (record->event.pressed && magic_mod_state == 1) { //when pressed && in pre-selection mode
                return true;
                layer_off(_MML);
                magic_mod_state = 0; //since these are tap-only keycodes, magic mod state is reset immediately.
            } return false;
        case SFTLOCK:
            if (record->event.pressed && magic_mod_state == 1) {
                register_code16(KC_LSFT);
                layer_off(_MML);
                magic_mod_state = 2; //when set to 2, magic mod won't cancel on key release
            } return false;
        case CTLLOCK:
            if (record->event.pressed && magic_mod_state == 1) {
                register_code16(KC_LCTL);
                layer_off(_MML);
                magic_mod_state = 2; //when set to 2, magic mod won't cancel on key release
            } return false;
        case RALTLCK:
            if (record->event.pressed && magic_mod_state == 1) {
                register_code16(KC_RALT);
                layer_off(_MML);
                magic_mod_state = 2; //when set to 2, magic mod won't cancel on key release
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
