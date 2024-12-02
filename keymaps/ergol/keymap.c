// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
//#include <keycodes.h>
#include <keymap_french.h>
//#include <send_string_keycodes.h>
//#include <os_detection.h>
//#include <ps2_mouse.h>
//#include <rgblight.h>

static uint16_t trackpoint_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

#define WINALT1(A) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A)));}
#define WINALT2(A, B) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B)));}
#define WINALT3(A, B, C) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C)));}
#define WINALT4(A, B, C, D) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C) SS_TAP(X_KP_ ## D)));}
#define UNSHIFT(A) {unregister_code(KC_LSFT); A ; register_code(KC_LSFT);}
#define SHIFT(A) {register_code(KC_LSFT); A ; unregister_code(KC_LSFT);}
#define ALTGR(A) {register_code(KC_RALT); A ; unregister_code(KC_RALT);}
#define OPTION(A) {register_code(KC_LOPT); A ; unregister_code(KC_LOPT);}
#define COMMAND(A) {register_code(KC_LGUI); A ; unregister_code(KC_LGUI);}
#define XKEY(A) {SEND_STRING(SS_TAP(A));}
#define XCIRC(A) {SEND_STRING(SS_TAP(X_LBRC) SS_TAP(A));}
#define XCIRCSHIFT(A) {SEND_STRING(SS_TAP(X_LBRC) SS_LSFT(SS_TAP(A)));}
#define XACUTSHIFT(A) {SEND_STRING(SS_LSFT(SS_LALT(SS_TAP(X_1))) SS_LSFT(SS_TAP(A)));}
#define XTRE(A) {SEND_STRING(SS_LSFT(SS_TAP(X_LBRC)) SS_TAP(A));}
#define XGRV(A) {SEND_STRING(SS_TAP(X_NUHS) SS_TAP(A));}
#define XGRVSHIFT(A) {SEND_STRING(SS_TAP(X_NUHS) SS_LSFT(SS_TAP(A)));}
#define XTILD(A) {SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_TAP(A));}
#define XTILDSHIFT(A) {SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_LSFT(SS_TAP(A)));}

bool macos_mode = false;

#define LED_INTERNAL  GP17

enum layers {
    _BAS,
    _SHF,
    _1DK,
    _SDK,
    _COD,
    _NUM,
    _FCT,
    _MSE
};

enum custom_keycodes {
  MA_TOBASE = SAFE_RANGE,

  //ERGOL BASE LAYER
  ME_EURO,
  ME_AT,
  ME_MINS,
  ME_PSCR,

  //ERGOL SHIFT LAYER
  ME_EXCL,
  ME_INSEC,
  ME_DQUO,
  ME_SCLN,
  ME_COLN,
  ME_DEL,
  ME_BSLH,
  ME_DLR1,

  //ERGOL DEAD LAYER
  ME_ACIR,
  ME_OE,
  ME_OCIR,
  ME_UCIR,
  ME_ECIR,
  ME_ICIR,
  ME_ITRE,
  ME_AE,
  ME_ETC,
  ME_QUOTFR,
  ME_GRV,
  ME_CADR,
  ME_SCADR,
  ME_QCADR,
  ME_LQUOTFR,
  ME_RQUOTFR,
  ME_DLR,
  ME_NTILD,
  ME_MICR,
  ME_SUP2,
  ME_SECT,
  ME_COPYR,
  ME_BULLET,
  ME_https,

  //ERGOL DEAD MAJ LAYER
  ME_ACIRM,
  ME_CCEDM,
  ME_OEM,
  ME_OCIRM,
  ME_UCIRM,
  ME_AGRVM,
  ME_EACUM,
  ME_EGRVM,
  ME_ECIRM,
  ME_ICIRM,
  ME_ITREM,
  ME_UGRVM,
  ME_AEM,
  ME_SUP3,
  ME_NTILDM,
  ME_RGSTRD,

  //ERGOL CODE LAYER
  ME_CIR,
  ME_TIL,
  ME_LCBR,
  ME_RCBR,
  ME_LBRC,
  ME_RBRC,
  ME_UNDS,
  ME_PLUS,
  ME_ASTR,
  ME_EQL,
  ME_PIPE,
  ME_LABK,
  ME_RABK,
  ME_HASH,
  ME_SML1,
  ME_SML2,
  ME_SML3,

  //FUNCTION LAYER
  ME_MICOFF,
  
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Tap dance enums
enum {
    TD1_CTL_GUI,
    TD2_BSPC_MS3,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD1_CTL_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
    [TD2_BSPC_MS3] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, MS_BTN3),
};

void keyboard_pre_init_user(void) {
  //internal led
  gpio_set_pin_output(LED_INTERNAL);
  gpio_write_pin(LED_INTERNAL,true);

  //RESET PS2
  gpio_set_pin_output(GP9);
  gpio_write_pin(GP9,true);
  wait_ms(2);
  gpio_write_pin(GP9,false);
    
}

uint32_t turn_off_led(uint32_t trigger_time, void *cb_arg) {
    rgblight_sethsv_at(HSV_OFF, 0);
    return 0;
}

uint32_t get_host_os(uint32_t trigger_time, void *cb_arg) {
  switch(detected_host_os()) {
    case OS_MACOS:
    case OS_IOS:
      macos_mode = true;
      //turn_on_macos(0,NULL);
      rgblight_sethsv_at(HSV_BLUE, 0);
      defer_exec(1500, turn_off_led, false);
      break;
    default:
      macos_mode = false;
      rgblight_sethsv_at(HSV_WHITE, 0);
      defer_exec(1500, turn_off_led, false);
      break;
  }
  return 0;
}

void keyboard_post_init_user(void) {
  // turn off internal led + detect host os
  gpio_write_pin(LED_INTERNAL,false);
  defer_exec(500, get_host_os, NULL);
  rgblight_sethsv_at(HSV_OFF, 0);

  //gpio_write_pin(GP9,false);

  //ps2_mouse_set_resolution(PS2_MOUSE_8_COUNT_MM);
  //ps2_mouse_set_scaling_2_1();
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BAS] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
FR_Q,         FR_C,         FR_O,         FR_P,         FR_W,                                     FR_J,         FR_M,         FR_D,         OSL(_1DK),    FR_Y,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
FR_A,         FR_S,         FR_E,         FR_N,         FR_F,                                     FR_L,         FR_R,         FR_T,         FR_I,         FR_U,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
LALT_T(FR_Z), FR_X ,        ME_MINS,      FR_V,         LT(_FCT,FR_B),                            FR_DOT,       FR_H,         FR_G,         FR_COMM,      RALT_T(FR_K),
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                        TD(TD1_CTL_GUI),LM(_SHF, MOD_LSFT),MO(_COD),TD(TD2_BSPC_MS3),LT(_NUM,KC_SPC),KC_ENT        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_SHF] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
_______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      ME_EXCL,      _______,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
_______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
_______,      _______,      FR_COMM,      _______,      _______,                                  ME_COLN,      _______,      _______,      ME_SCLN,      _______,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          _______,      _______,      _______,      ME_DEL,       ME_INSEC,     _______        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),
 

    [_1DK] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
ME_ACIR,      FR_CCED,      ME_OE,        ME_OCIR,      FR_DEG,                                   ME_SECT,      ME_MICR,      FR_UNDS,      FR_DIAE,      ME_UCIR,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
FR_AGRV,      FR_EACU,      FR_EGRV,      ME_ECIR,      ME_NTILD,                                 ME_LQUOTFR,   ME_RQUOTFR,   ME_ICIR,      ME_ITRE,      FR_UGRV,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
ME_AE,        ME_SUP2,      ME_QCADR,     ME_SCADR,     ME_CADR,                                  ME_ETC,       ME_https,     XXXXXXX,      XXXXXXX,      ME_COPYR,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          XXXXXXX,      OSL(_SDK),    XXXXXXX,      XXXXXXX,      ME_QUOTFR,    XXXXXXX        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_SDK] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
ME_ACIRM,     ME_CCEDM,     ME_OEM,       ME_OCIRM,     ME_BULLET,                                XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      ME_UCIRM,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
ME_AGRVM,     ME_EACUM,     ME_EGRVM,     ME_ECIRM,     ME_NTILDM,                                XXXXXXX,      XXXXXXX,      ME_ICIRM,     ME_ITREM,     ME_UGRVM,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
ME_AEM,       ME_SUP3,      XXXXXXX,      XXXXXXX,      XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      ME_RGSTRD,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_COD] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
FR_DQUO,      ME_LABK,      ME_RABK,      FR_AMPR,      FR_PERC,                                  XXXXXXX,      ME_EURO,      ME_SML1,      ME_SML2,      ME_SML3,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
ME_LCBR,      FR_LPRN,      FR_RPRN,      ME_RCBR,      ME_PIPE,                                  FR_DLR,       KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
FR_QUOT,      ME_LBRC,      ME_RBRC,      ME_UNDS,      ME_HASH,                                  XXXXXXX,      KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          _______,      XXXXXXX,      XXXXXXX,      _______,      KC_LSFT,      _______        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_NUM] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
KC_TAB,       ME_AT,        KC_DOT,       ME_TIL,       KC_ESC,                                   XXXXXXX,      KC_SPC,       KC_COMM,      XXXXXXX,      ME_BSLH,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
FR_1,         FR_2,         FR_3,         FR_4,         FR_5,                                     FR_6,         FR_7,         FR_8,         FR_9,         FR_0,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
XXXXXXX,      FR_LPRN,      FR_RPRN,      ME_CIR,       ME_GRV,                                   ME_EQL,       ME_PLUS,      ME_MINS,      ME_ASTR,      FR_SLSH,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          _______,      KC_LSFT,      _______,      _______,      _______,      _______        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_FCT] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
QK_REBOOT,    XXXXXXX,      XXXXXXX,      KC_BRIU,      KC_VOLU,                                  KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_BRID,      KC_VOLD,                                  KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,  
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,                                  KC_F11,       KC_F12,       XXXXXXX,      XXXXXXX,      KC_PSCR,  
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_MUTE,      ME_MICOFF,    XXXXXXX        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    ),

    [_MSE] = LAYOUT_36keys(
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+
_______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,   
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
_______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,
//-----------+-------------+-------------+-------------+-------------+                           +-------------+-------------+-------------+-------------+-------------+ 
_______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,
//-----------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
                                          _______,      _______,      _______,      MS_BTN3,      MS_BTN1,      MS_BTN2        
//                                       +-------------+-------------+-------------+-------------+-------------+-------------+     
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

  //release MOUSE layer if any other key is pressed
  if (trackpoint_timer && keycode!=MS_BTN1 && keycode!=MS_BTN2 && keycode!=MS_BTN3) { 
      layer_off(_MSE);
      trackpoint_timer = 0; //Reset the timer again until the mouse moves more
  }

  switch (keycode) {
    //TAP DANCE section
    case TD(TD2_BSPC_MS3):
      action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
      if (!record->event.pressed && action->state.count && !action->state.finished) {
        tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        tap_code16(tap_hold->tap);
      }
      break;

    // OTHER KEYS
    default:
    
      if (record->event.pressed) {
        switch (keycode) {
          //ERGO BASE LAYER
          case ME_MINS: if (macos_mode)      XKEY(X_EQL)                  else XKEY(X_6);               break;
          //ERGOL SHIFT LAYER
          case ME_EXCL: if (macos_mode)      UNSHIFT(XKEY(X_8))           else UNSHIFT(XKEY(X_SLSH));   break;
          case ME_INSEC:if (macos_mode)      UNSHIFT(OPTION(XKEY(X_SPC))) else UNSHIFT(WINALT3(2,5,5)); break; // ALT 255 = insec
          case ME_SCLN: UNSHIFT(XKEY(X_COMM)); break; 
          case ME_COLN: UNSHIFT(XKEY(X_DOT)); break;
          case ME_DEL:  UNSHIFT(XKEY(X_DEL)); break;
          // ERGOL DEAD LAYER
          case ME_ACIR:   if (macos_mode) XCIRC(X_Q)                else WINALT3(1,3,1); break;// ALT 131 = â
          case ME_OE:     if (macos_mode) OPTION(XKEY(X_O))         else WINALT4(0,1,5,6); break;//ALT 0156 = œ
          case ME_OCIR:   if (macos_mode) XCIRC(X_O)                else WINALT3(1,4,7); break;// ALT 147 = ô
          case ME_UCIR:   if (macos_mode) XCIRC(X_U)                else WINALT3(1,5,0); break;// ALT 150 = û
          case ME_ECIR:   if (macos_mode) OPTION(XKEY(X_E))         else WINALT3(1,3,6); break;// ALT 136 = ê
          case ME_ICIR:   if (macos_mode) OPTION(XKEY(X_I))         else WINALT3(1,4,0); break;// ALT 140 = î
          case ME_ITRE:   if (macos_mode) XTRE(X_I)                 else WINALT3(1,3,9); break;// ALT 139 = ï
          case ME_AE:     if (macos_mode) OPTION(XKEY(X_Q))         else WINALT3(1,4,5); break;// ALT 145 = æ
          case ME_ETC:    if (macos_mode) OPTION(XKEY(X_COMM))      else WINALT4(0,1,3,3); break; // ...
          case ME_QUOTFR: if (macos_mode) SHIFT(OPTION(XKEY(X_4)))  else WINALT4(0,1,4,6); break;//ALT 0146 = ’
          case ME_CADR:   if (macos_mode) OPTION(XKEY(X_EQL))       else WINALT4(0,1,5,1); break;// ALT 151 = 
          case ME_SCADR:  if (macos_mode) SHIFT(OPTION(XKEY(X_EQL)))else WINALT4(0,1,5,0); break;// ALT 0150 = 
          case ME_QCADR:  if (macos_mode) XKEY(X_EQL)               else WINALT4(0,1,7,3); break;// ALT 0173 = - (insec)
          case ME_LQUOTFR: if (macos_mode) OPTION(XKEY(X_7))        else WINALT3(1,7,4); break;// ALT 174 = «
          case ME_RQUOTFR: if (macos_mode) SHIFT(OPTION(XKEY(X_7))) else WINALT3(1,7,5); break;// ALT 175 = »
          case ME_NTILD:  if (macos_mode) XTILD(X_N)                else WINALT3(1,6,4); break;// ALT 164 = ñ
          case ME_MICR:   if (macos_mode) OPTION(XKEY(X_SCLN))      else SHIFT(XKEY(X_NUHS)); break;// ALT 181 = µ
          case ME_SUP2:   if (!macos_mode)                               XKEY(X_GRV); break;// ALT 178 = ²
          case ME_SECT:   if (macos_mode)  XKEY(X_6)                else SHIFT(XKEY(X_SLSH)); break;// ALT 167 = §
          case ME_COPYR:  if (macos_mode)  OPTION(XKEY(X_C))        else WINALT4(0,1,6,9); break;// ALT 0169 = ©
          case ME_https:  SEND_STRING("https" SS_TAP(X_DOT) SS_LSFT(SS_TAP(X_DOT)) SS_LSFT(SS_TAP(X_DOT))); break; // https://
          //ERGOL DEAD MAJ LAYER
          case ME_ACIRM: if (macos_mode)   XCIRCSHIFT(X_Q)          else WINALT3(1,8,2); break;// ALT 182 = Â
          case ME_CCEDM: if (macos_mode)   OPTION(XKEY(X_9))        else WINALT3(1,2,8); break;// ALT 128 = Ç
          case ME_OEM: if (macos_mode)     SHIFT(OPTION(XKEY(X_O))) else WINALT4(0,1,4,0); break;// ALT 0140 = Œ
          case ME_OCIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_LBRC))) else WINALT3(2,2,6); break;// ALT 226 = Ô
          case ME_UCIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_8))) else WINALT3(2,3,4); break;// ALT 234 = Û
          case ME_AGRVM: if (macos_mode)   SEND_STRING(SS_TAP(X_CAPS) SS_TAP(X_0) SS_TAP(X_CAPS)); else WINALT3(1,8,3); break;//ALT 183 = À
          case ME_EACUM: if (macos_mode)   XACUTSHIFT(X_E)          else WINALT3(1,4,4); break;//ALT 144 = É
          case ME_EGRVM: if (macos_mode)   XGRVSHIFT(X_E)           else WINALT3(2,1,2); break;//ALT 212 = È
          case ME_ECIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_E))) else WINALT3(2,1,0); break;// ALT 210 = Ê
          case ME_ICIRM: if (macos_mode)   SHIFT(OPTION(XKEY(X_H))) else WINALT3(2,1,5); break;// ALT 215 = Î
          case ME_ITREM: if (macos_mode)   OPTION(XKEY(X_J))        else WINALT3(2,1,6); break;// ALT 216 = Ï
          case ME_UGRVM: if (macos_mode)   OPTION(XKEY(X_QUOT))     else WINALT3(2,3,5); break;// ALT 235 = Ù
          case ME_AEM:   if (macos_mode)   SHIFT(OPTION(XKEY(X_Q))) else WINALT3(1,4,6); break;// ALT 146 = Æ
          case ME_SUP3:  if (!macos_mode)                                WINALT3(2,5,2); break;// ALT 252 = ³
          case ME_NTILDM: if (macos_mode)  XTILDSHIFT(X_N)          else WINALT3(1,6,5); break;// ALT 165 = Ñ
          case ME_RGSTRD: if (macos_mode)  OPTION(XKEY(X_R))        else WINALT4(0,1,7,4); break; // ALT 0174 = ®
          case ME_BULLET: if (macos_mode)  OPTION(XKEY(X_NUBS))     else WINALT1(7); break;// ALT 7 = •
          //ERGOL CODE LAYER
          case ME_EURO: if (macos_mode)   OPTION(XKEY(X_RBRC))      else ALTGR(XKEY(X_E));        break;
          case ME_LCBR:  if (macos_mode)  OPTION(XKEY(X_5))         else ALTGR(XKEY(X_4)); break; // {
          case ME_RCBR:  if (macos_mode)  OPTION(XKEY(X_MINS))      else ALTGR(XKEY(X_EQL)); break; // {
          case ME_LBRC:  if (macos_mode)  SHIFT(OPTION(XKEY(X_5)))  else ALTGR(XKEY(X_5)); break; // [
          case ME_RBRC:  if (macos_mode)  SHIFT(OPTION(XKEY(X_MINS))) else ALTGR(XKEY(X_MINS)); break; // ]
          case ME_UNDS:  if (macos_mode)  SHIFT(XKEY(X_EQL))        else XKEY(X_8); break; // _
          case ME_PLUS:  if (macos_mode)  SHIFT(XKEY(X_SLSH))       else SHIFT(XKEY(X_EQL)); break; // +
          case ME_EQL:   if (macos_mode)  XKEY(X_SLSH)              else XKEY(X_EQL); break; // =
          case ME_ASTR:  if (macos_mode)  SHIFT(XKEY(X_RBRC))       else XKEY(X_NUHS); break; // *
          case ME_PIPE:  if (macos_mode)  SHIFT(OPTION(XKEY(X_L)))  else ALTGR(XKEY(X_6)); break; // |
          case ME_LABK:  if (macos_mode)  XKEY(X_GRV)               else XKEY(X_NUBS); break; // <
          case ME_RABK:  if (macos_mode)  SHIFT(XKEY(X_GRV))        else SHIFT(XKEY(X_NUBS)); break; // >
          case ME_HASH:  if (macos_mode)  SHIFT(XKEY(X_NUBS))       else ALTGR(XKEY(X_3)); break; // #
          case ME_SML1:  if (macos_mode)  SEND_STRING(SS_TAP(X_DOT)  SS_TAP(X_EQL) SS_TAP(X_MINS)); else SEND_STRING(SS_TAP(X_DOT)  SS_TAP(X_6) SS_TAP(X_MINS)); break;
          case ME_SML2:  if (macos_mode)  SEND_STRING(SS_TAP(X_COMM) SS_TAP(X_EQL) SS_TAP(X_MINS)); else SEND_STRING(SS_TAP(X_COMM) SS_TAP(X_6) SS_TAP(X_MINS)); break;
          case ME_SML3:  if (macos_mode)  SEND_STRING(SS_TAP(X_DOT)  SS_TAP(X_EQL) SS_TAP(X_5));    else SEND_STRING(SS_TAP(X_DOT)  SS_TAP(X_6) SS_TAP(X_5)); break;
          // ERGOL NUM
          case ME_BSLH: if (macos_mode)      SHIFT(OPTION(XKEY(X_DOT)))    else ALTGR(XKEY(X_8)); break;
          case ME_AT:   if (macos_mode)      XKEY(X_NUBS)                 else ALTGR(XKEY(X_0));        break;
          case ME_GRV:    if (macos_mode) XGRV(X_SPC)               else WINALT2(9,6); break; // ALT 96 = ``
          case ME_CIR:   if (macos_mode)  XCIRC(X_SPC)              else WINALT2(9,4); break; // ALT 94 = ^
          case ME_TIL:   if (macos_mode)  XTILD(X_SPC)              else WINALT3(1,2,6); break; // ALT 126 = ~
          // ERGOL FUNCT
          case ME_PSCR: if (macos_mode)      SHIFT(COMMAND(XKEY(X_4)))    else XKEY(X_PSCR);            break;
          case ME_MICOFF: if (!macos_mode)   SEND_STRING(SS_LGUI(SS_TAP(X_F4))); break;

          /* case MA_EOL: WINALT2(2,0); break; // ALT 20 = ¶  */
        }
      }
  }
  return true;
}

// LED for some layers
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case _SHF: rgblight_sethsv_at(HSV_OFF, 0); break;
      case _1DK: rgblight_sethsv_at(HSV_PINK, 0); break;
      case _SDK: rgblight_sethsv_at(HSV_PINK, 0); break;
      case _COD: rgblight_sethsv_at(HSV_OFF, 0); break;//HSV_GREEN
      case _NUM: rgblight_sethsv_at(HSV_OFF, 0); break;//HSV_PURPLE
      case _FCT: rgblight_sethsv_at(HSV_ORANGE, 0); break;
      case _MSE: rgblight_sethsv_at(HSV_RED, 0); break;
      default: rgblight_sethsv_at(HSV_OFF, 0);
    }
    return state;
}

/*
bool led_update_user(led_t led_state) {
  if (detected_host_os() == OS_WINDOWS) { 
    //macos_mode = false;
    if (led_state.num_lock && !led_state.scroll_lock) {
      rgblight_sethsv_at(HSV_OFF, 0);
    } else {
      rgblight_sethsv_at(HSV_YELLOW, 0);
    }
  } else {
    rgblight_sethsv_at(HSV_OFF, 0);
  }
  return true;
}
*/

void ps2_mouse_moved_user(report_mouse_t *mouse_report) { // Whenever the TrackPoint starts moving, check if the timer exists.
    if (trackpoint_timer) {
        trackpoint_timer = timer_read();
    } else {
        if (!tp_buttons) { //I'm still a bit confused about this one, but I believe it checks that if the mousekey state isn't set, turn on this layer specified?
            layer_on(_MSE);
            trackpoint_timer = timer_read();
            //print("Trackpoint Buttons!: On\n");
        }
    }
}

void matrix_scan_user(void) {  // ALWAYS RUNNING VOID FUNCTION, CAN BE USED TO CHECK CLOCK RUNTIMES OVER THE DURATION THAT THE KEYBOARD IS POWERED ON
  if (trackpoint_timer && (timer_elapsed(trackpoint_timer) > MOUSE_LAYER_TIMEOUT)) { //If the time of both the TP timer
    if (!tp_buttons) {
      layer_off(_MSE);
      trackpoint_timer = 0; //Reset the timer again until the mouse moves more
    }
  }
}



