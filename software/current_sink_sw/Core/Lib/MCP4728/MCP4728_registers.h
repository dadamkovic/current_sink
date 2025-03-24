/**
 * @file MCP4728_registers.h
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MCP4728_REGISTERS_H
#define MCP4728_REGISTERS_H

#include "inttypes.h"


typedef enum
{
  MCP_DISPLAY,
  MCP_COMMAND
} TDef_CommandDisplay;




#define INTERNAL_CLK 0b0
#define EXTERNAL_CLK 0b1
#define NO_RESET 0b0
#define EXEC_RESET 0b1
#define MEM_LOW 0b0
#define MEM_HIGH 0b1
#define _ICSET_CONST_ADDR 0b1011

typedef struct
{
  uint8_t CLK: 1;
  uint8_t RESET: 1;
  uint8_t MEM_SEL: 1;
  uint8_t _PADDING: 5;
} TdefICSET_Settings;

typedef union{
  TdefICSET_Settings fields;
  uint8_t raw;
} TdefICSET;

#define POW_SAVE_1  0b00
#define POW_SAVE_2  0b01
#define POW_NORMAL  0b10
#define POW_HIGH    0b11
#define INV_LINE    0b0
#define INV_FRAME   0b1
#define FREQ_80     0b00
#define FREQ_PS71   0b01
#define FREQ_PS64   0b10
#define FREQ_PS53   0b11

typedef struct
{
  uint8_t POWER: 2;
  uint8_t INV: 1;
  uint8_t FREQ_MODE: 2;
  uint8_t _PADDING: 3;
} TdefDISCTL_Settings;

typedef union{
  TdefDISCTL_Settings fields;
  uint8_t raw;
} TdefDISCTL;


#endif