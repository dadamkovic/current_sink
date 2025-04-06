/**
 * @file segment_lib.c
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "segment_lib.h"


Tdef_segement alphabet[128];

/**
 * @brief Initializes all segment data
 * 
 */
void initSegements(){

    //apostrophe
    alphabet[39].segments = SEG_AP;
    //signs
    alphabet[45].segments = SEG_G | SEG_K;
    alphabet[46].segments = SEG_DOT;
    alphabet[43].segments = SEG_I | SEG_M | SEG_G | SEG_K;
    alphabet[47].segments = SEG_N | SEG_J;

    //numbers 0 - 9
    alphabet[48].segments = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_N | SEG_J;                 //0
    alphabet[49].segments = SEG_B | SEG_C | SEG_J;                                         //1
    alphabet[50].segments = SEG_A | SEG_B | SEG_K | SEG_G | SEG_E | SEG_D;                 //2
    alphabet[51].segments = SEG_A | SEG_B | SEG_K | SEG_C | SEG_D;                         //3
    alphabet[52].segments = SEG_F | SEG_G | SEG_K | SEG_B | SEG_C;                         //4
    alphabet[53].segments = SEG_A | SEG_F | SEG_G | SEG_K | SEG_C | SEG_D;                 //5
    alphabet[54].segments = SEG_A | SEG_F | SEG_G | SEG_K | SEG_C | SEG_D | SEG_E;         //6
    alphabet[55].segments = SEG_A | SEG_B | SEG_K | SEG_C;                                 //7
    alphabet[56].segments = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_K; //8 
    alphabet[57].segments = SEG_A | SEG_B | SEG_C | SEG_F | SEG_G | SEG_K;                 //9                                                                                                                                            

    //capital letters A - Z
    alphabet[65].segments = SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G | SEG_K;
    alphabet[66].segments = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_K;
    alphabet[67].segments = SEG_A | SEG_D | SEG_E | SEG_F;
    alphabet[68].segments = SEG_C | SEG_D | SEG_E | SEG_B | SEG_G | SEG_K;
    alphabet[69].segments = SEG_A | SEG_D | SEG_E | SEG_F | SEG_G;
    alphabet[70].segments = SEG_A | SEG_E | SEG_F | SEG_G;
    alphabet[71].segments = SEG_A | SEG_F | SEG_G | SEG_K | SEG_C | SEG_D | SEG_E;
    alphabet[72].segments = SEG_B | SEG_C | SEG_E | SEG_F | SEG_G | SEG_K;
    alphabet[73].segments = SEG_A | SEG_I | SEG_M | SEG_D;
    alphabet[74].segments = SEG_B | SEG_C | SEG_D | SEG_E;
    alphabet[75].segments = SEG_E | SEG_F | SEG_G | SEG_J | SEG_L;
    alphabet[76].segments = SEG_E | SEG_F | SEG_D;
    alphabet[77].segments = SEG_E | SEG_F | SEG_B | SEG_C | SEG_H | SEG_J;
    alphabet[78].segments = SEG_E | SEG_F | SEG_B | SEG_C | SEG_H | SEG_L;
    alphabet[79].segments = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
    alphabet[80].segments = SEG_A | SEG_B | SEG_E | SEG_F | SEG_G | SEG_K;
    alphabet[81].segments = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_L;
    alphabet[82].segments = SEG_A | SEG_B | SEG_E | SEG_F | SEG_G | SEG_K | SEG_L;
    alphabet[83].segments = SEG_A | SEG_F | SEG_G | SEG_K | SEG_C | SEG_D;
    alphabet[84].segments = SEG_A | SEG_I | SEG_M;
    alphabet[85].segments = SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
    alphabet[86].segments = SEG_F | SEG_E | SEG_N | SEG_J;
    alphabet[87].segments = SEG_F | SEG_E | SEG_N | SEG_I | SEG_L | SEG_C | SEG_B;
    alphabet[88].segments = SEG_H | SEG_L | SEG_N | SEG_J;
    alphabet[89].segments = SEG_H | SEG_J | SEG_M;
    alphabet[90].segments = SEG_A | SEG_J | SEG_N | SEG_D;

    //lowercase
    alphabet[109].segments = SEG_E | SEG_G | SEG_M | SEG_K | SEG_C;
}

