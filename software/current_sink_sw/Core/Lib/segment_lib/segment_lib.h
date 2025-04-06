/**
 * @file segment_lib.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SEGMENT_LIB_H
#define SEGMENT_LIB_H

#include "inttypes.h"

#define _BV(x) (1<<x)
#define DISP_MAX (uint32_t)99999999
#define DISP_MIN (uint32_t)0

#define SEG_ON 0b1

#define SEG_A _BV(0)
#define SEG_B _BV(1)
#define SEG_C _BV(2)
#define SEG_D _BV(3)
#define SEG_E _BV(4)
#define SEG_F _BV(5)
#define SEG_G _BV(6)
#define SEG_H _BV(7)
#define SEG_I _BV(8)
#define SEG_J _BV(9)
#define SEG_K _BV(10)
#define SEG_L _BV(11)
#define SEG_M _BV(12)
#define SEG_N _BV(13)
#define SEG_AP _BV(14)
#define SEG_DOT _BV(15)


typedef struct{
    uint8_t A: 1;
    uint8_t B: 1;
    uint8_t C: 1;
    uint8_t D: 1;
    uint8_t E: 1;
    uint8_t F: 1;
    uint8_t G: 1;
    uint8_t H: 1;
    uint8_t I: 1;
    uint8_t J: 1;
    uint8_t K: 1;
    uint8_t L: 1;
    uint8_t M: 1;
    uint8_t N: 1;
    uint8_t AP: 1;
    uint8_t DOT: 1;
}segment_names;


typedef union{
    uint16_t segments;
    segment_names segment;
}Tdef_segement;

extern Tdef_segement alphabet[];

void initSegements();
uint8_t segmentAddressBit(uint8_t digit, uint16_t segment);

 #endif