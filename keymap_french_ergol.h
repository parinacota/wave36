
#pragma once
#include "keycodes.h"
// clang-format off

// Aliases
#define FR_LSQU KC_GRV  // `
#define FR_1    KC_1    // 1
#define FR_2    KC_2    // 2
#define FR_3    KC_3    // 3
#define FR_4    KC_4    // 4
#define FR_5    KC_5    // 5
#define FR_6    KC_6    // 6
#define FR_7    KC_7    // 7
#define FR_8    KC_8    // 8
#define FR_9    KC_9    // 9
#define FR_0    KC_0    // 0
#define FR_SLSH KC_MINS // /
#define FR_EQL  KC_EQL  // =
#define FR_Q    KC_Q    // Q
#define FR_C    KC_W    // C
#define FR_O    KC_E    // O
#define FR_P    KC_R    // P
#define FR_W    KC_T    // W
#define FR_J    KC_Y    // J
#define FR_M    KC_U    // M
#define FR_D    KC_I    // D
#define FR_1DK  KC_O    // 1dk (dead lafayette)
#define FR_Y    KC_P    // Y
#define FR_LBRC KC_LBRC // [
#define FR_RBRC KC_RBRC // ]
#define FR_A    KC_A    // A
#define FR_S    KC_S    // S
#define FR_E    KC_D    // E
#define FR_N    KC_F    // N
#define FR_F    KC_G    // F
#define FR_L    KC_H    // L
#define FR_R    KC_J    // R
#define FR_T    KC_K    // R
#define FR_I    KC_L    // I
#define FR_U    KC_SCLN // U
#define FR_QUOT KC_QUOT // '
#define FR_BSLS KC_NUHS // (backslash)
#define FR_LABK KC_NUBS // <
#define FR_Z    KC_Z    // Z
#define FR_X    KC_X    // X
#define FR_MINS KC_C    // -
#define FR_V    KC_V    // V
#define FR_B    KC_B    // B
#define FR_DOT  KC_N    // .
#define FR_H    KC_M    // H
#define FR_G    KC_COMM // G
#define FR_COMM KC_DOT  // ,
#define FR_K    KC_SLSH // K

//SHIFTED
#define FR_TILO S(FR_LSQU) // ~
#define FR_EURO S(FR_1)    // €
#define FR_LDQF S(FR_2)    // «
#define FR_RDQF S(FR_3)    // »
#define FR_DLR  S(FR_4)    // $
#define FR_PERC S(FR_5)    // %
#define FR_CIRC S(FR_6)    // ^
#define FR_AMPR S(FR_7)    // &
#define FR_ASTR S(FR_8)    // *
#define FR_HASH S(FR_9)    // #
#define FR_AT   S(FR_0)    // @
#define FR_UNDS S(FR_SLSH) // _
#define FR_PLUS S(FR_EQL)  // =
#define FR_EXCL S(FR_1DK)  // !
#define FR_LCBR S(FR_LBRC) // {
#define FR_RCBR S(FR_RBRC) // }
#define FR_DQUO S(FR_QUOT) // "
#define FR_PIPE S(FR_BSLS) // |
#define FR_RABK S(FR_LABK) // >
#define FR_QUES S(FR_MINS) // ?
#define FR_COLN S(FR_DOT)  // :
#define FR_SCLN S(FR_COMM) // ;

//ALTGR  //Symbol layer
#define FRS_SUP1 ALGR(FR_1)    // 1
#define FRS_SUP2 ALGR(FR_2)    // ²
#define FRS_SUP3 ALGR(FR_3)    // 3
#define FRS_SUP4 ALGR(FR_4)    // 4
#define FRS_SUP5 ALGR(FR_5)    // 5
#define FRS_SUP6 ALGR(FR_6)    // 6
#define FRS_SUP7 ALGR(FR_7)    // 7
#define FRS_SUP8 ALGR(FR_8)    // 8
#define FRS_SUP9 ALGR(FR_9)    // 9
#define FRS_SUP0 ALGR(FR_0)    // 0
#define FRS_CIRC ALGR(FR_Q)    // ^
#define FRS_LABK ALGR(FR_C)    // <
#define FRS_RABK ALGR(FR_O)    // >
#define FRS_DLR  ALGR(FR_P)    // $
#define FRS_PERC ALGR(FR_W)    // %
#define FRS_AT   ALGR(FR_J)    // @
#define FRS_AMPR ALGR(FR_M)    // &
#define FRS_ASTR ALGR(FR_D)    // *
#define FRS_QUOT ALGR(FR_1DK)  // '
#define FRS_LSQU ALGR(FR_Y)    // `
#define FRS_LCBR ALGR(FR_A)    // {
#define FRS_LPRN ALGR(FR_S)    // (
#define FRS_RPRN ALGR(FR_E)    // )
#define FRS_RCBR ALGR(FR_N)    // }
#define FRS_EQL  ALGR(FR_F)    // F
#define FRS_BSLS ALGR(FR_L)    // (backslash)
#define FRS_PLUS ALGR(FR_R)    // +
#define FRS_MINS ALGR(FR_T)    // -
#define FRS_SLSH ALGR(FR_I)    // /
#define FRS_DQUO ALGR(FR_U)    // "
#define FRS_TILD ALGR(FR_Z)    // ~
#define FRS_LBRC ALGR(FR_X)    // [
#define FRS_RBRC ALGR(FR_MINS) // ]
#define FRS_UNDS ALGR(FR_V)    // _
#define FRS_HASH ALGR(FR_B)    // #
#define FRS_PIPE ALGR(FR_DOT)  // |
#define FRS_EXCL ALGR(FR_H)    // !
#define FRS_SCLN ALGR(FR_G)    // ;
#define FRS_COLN ALGR(FR_COMM) // :
#define FRS_QUES ALGR(FR_K)    // ?

//ALTGR  //Symbol layer //SHIFTED
// #define FRS_SUP1 ALGR(S(FR_1))    // 1?
// #define FRS_SUP2 ALGR(S(FR_2))    // 2?
// #define FRS_SUP3 ALGR(S(FR_3))    // 3?
// #define FRS_SUP4 ALGR(S(FR_4))    // 4?
// #define FRS_SUP5 ALGR(S(FR_5))    // 5?
// #define FRS_SUP6 ALGR(S(FR_6))    // 6?
// #define FRS_SUP7 ALGR(S(FR_7))    // 7?
// #define FRS_SUP8 ALGR(S(FR_8))    // 8?
// #define FRS_SUP9 ALGR(S(FR_9))    // 9?
// #define FRS_SUP0 ALGR(S(FR_0))    // 0?
#define FRS_DCIR  ALGR(S(FR_Q))    // ^ (dead)
#define FRS_LAKE  ALGR(S(FR_C))    // <=
#define FRS_RAKE  ALGR(S(FR_O))    // >=
#define FRS_CURR  ALGR(S(FR_P))    // ¤ (dead)
#define FRS_PERM  ALGR(S(FR_W))    // %%
#define FRS_RNGA  ALGR(S(FR_J))    // ° (dead)
#define FRS_MUL   ALGR(S(FR_D))    // ×
#define FRS_ACUT  ALGR(S(FR_1DK))  // ´ (dead)
#define FRS_GRV  ALGR(S(FR_Y))     // ` (dead)
#define FRS_CARN ALGR(S(FR_A))     // ˇ (dead)
#define FRS_RNGA ALGR(S(FR_N))     // ° (dead)
#define FRS_NEQL ALGR(S(FR_F))     // !=
// #define FRS_NORG ALGR(S(FR_L))  // TODO!! / dead
#define FRS_PLMN ALGR(S(FR_R))     // ±
#define FRS_MACR ALGR(S(FR_T))     // ¯ (dead)
#define FRS_DIV  ALGR(S(FR_I))     // ÷
#define FRS_DACU ALGR(S(FR_U))     // ˝ (dead)
#define FRS_DTIL ALGR(S(FR_Z))     // ~ (dead)
#define FRS_CEDL ALGR(S(FR_X))     // ¸ (dead)
#define FRS_OGON ALGR(S(FR_MINS))  // ˛ (dead)
// #define FRS_SCLN ALGR(S(FR_G))  // TODO cédille ronde dead
#define FRS_COLN ALGR(S(FR_COMM))  // :
#define FRS_BREV ALGR(S(FR_K))     // ˘ (dead)