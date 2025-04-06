/**
 * @file MCP4728_user.c
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "MCP4728.h"

/**
 * @brief Provides mapping from segment / digit to memory address of MCP
 * 
 * @param digit Sigit being set (start with 1 NOT 0!) 
 * @param segment Segement to be turned on 
 * @return uint8_t returns the bit address of the segment in MCP memory
 */
uint8_t segmentAddressBit(uint8_t digit, uint16_t segment){
  switch(segment){
      case SEG_A:
      return 141-((digit-1)*8);
      case SEG_B:
      return 142-((digit-1)*8);
      case SEG_C:
      return 143-((digit-1)*8);
      case SEG_DOT:
      return 144-((digit-1)*8);
      case SEG_D:
      return 8+((digit-1)*8);
      case SEG_E:
      return 7+((digit-1)*8);
      case SEG_F:
      return 6+((digit-1)*8);
      case SEG_G:
      return 138-((digit-1)*8);
      case SEG_H:
      return 137-((digit-1)*8);
      case SEG_I:
      return 1+((digit-1)*8);
      case SEG_J:
      return 2+((digit-1)*8);
      case SEG_K:
      return 3+((digit-1)*8);
      case SEG_L:
      return 4+((digit-1)*8);
      case SEG_AP:
      return 5+((digit-1)*8);
      case SEG_M:
      return 140-((digit-1)*8);
      case SEG_N:
      return 139-((digit-1)*8);
  }
  return 255;
  }
  
  