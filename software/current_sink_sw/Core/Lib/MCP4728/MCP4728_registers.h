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

/**
 * @brief Determines wherher command is being sent or RAM write request
 * 
 */
typedef enum
{
  MCP_RAM_WRITE,
  MCP_COMMAND
} TDef_CommandDisplay;



//All flags below for ICSET register
///Use internal clock 
#define INTERNAL_CLK 0x0
///Use external clock on OSCIN pin
#define EXTERNAL_CLK 0x1
///Default case when reset is not requested
#define NO_RESET 0x0
///When set, MCP reset will occur
#define EXEC_RESET 0x1
///Access to low memory bytes
#define MEM_LOW 0x0
///Access to high memory bytes
#define MEM_HIGH 0x1
///Assigned to padding to specify ICSET address
#define _ICSET_CONST_ADDR 0b1011

///structure for accessing ICSET fields
typedef struct
{
  uint8_t CLK: 1;
  uint8_t RESET: 1;
  uint8_t MEM_SEL: 1;
  uint8_t _PADDING: 5;
} TdefICSET_Settings;

///union for allowing individual / full access to ICSET register
typedef union{
  TdefICSET_Settings settings;
  uint8_t raw;
} TdefICSET;


//All flags below for DISCTL register
//Power saving mode selection - see datasheet
#define POW_SAVE_1  0b00
#define POW_SAVE_2  0b01
#define POW_NORMAL  0b10
#define POW_HIGH    0b11
///Refer to datasheet for driving waveform - line inversion
#define INV_LINE    0b0
///Refer to datasheet for driving waveform - frame inversion
#define INV_FRAME   0b1
///Operation frequency 80Hz | external clock / 512
#define FREQ_80     0b00
///Operation frequency 71Hz | external clock / 576
#define FREQ_PS71   0b01
///Operation frequency 64Hz | external clock / 648
#define FREQ_PS64   0b10
///Operation frequency 53Hz | external clock / 768
#define FREQ_PS53   0b11

///structure for accessing DISCTL fields
typedef struct
{
  uint8_t POWER: 2;
  uint8_t INV: 1;
  uint8_t FREQ_MODE: 2;
  uint8_t _PADDING: 3;
} TdefDISCTL_Settings;

///union for allowing individual / full access to DISCTL register
typedef union{
  TdefDISCTL_Settings settings;
  uint8_t raw;
} TdefDISCTL;


//All flags below for MODESET register
///Turn display OFF
#define DISP_OFF 0b0
///Turn display ON
#define DISP_ON 0b1

///structure for accessing MODESET fields
typedef struct
{
  uint8_t _PADDING0: 3;
  uint8_t DISP_STAT: 1;
  uint8_t _PADDING1: 4;
} TdefMODESET_Settings;

///union for allowing individual / full access to MODESET register
typedef union{
  TdefMODESET_Settings settings;
  uint8_t raw;
} TdefMODESET;


//All flags below for BLKCTL register
///No blinking
#define BLINK_OFF   0b000
///Blinking - 0.5Hz freqeuncy
#define BLINK_0_5   0b001
///Blinking - 1Hz freqeuncy
#define BLINK_1     0b010
///Blinking - 2Hz freqeuncy
#define BLINK_2     0b011
///Blinking - 0.3Hz freqeuncy
#define BLINK_0_3   0b100
///Blinking - 0.2Hz freqeuncy
#define BLINK_0_2   0b101

///structure for accessing BLKCTL fields
typedef struct
{
  uint8_t BLINK_SET: 3;
  uint8_t _PADDING: 5;
} TdefBLKCTL_Settings;

///union for allowing individual / full access to BLKCTL register
typedef union{
  TdefBLKCTL_Settings settings;
  uint8_t raw;
} TdefBLKCTL;


//All flags below for APCTL register
///Normal pixel acces mode
#define PIX_NORMAL    0b00
///Turn on all pixels
#define ALL_PIX_ON    0b10
///Turn off all pixels
#define ALL_PIX_OFF   0b01

///structure for accessing APCTL fields
typedef struct
{
  uint8_t PIX_SET: 2;
  uint8_t _PADDING: 6;
} TdefAPCTL_Settings;

///union for allowing individual / full access to APCTL register
typedef union{
  TdefAPCTL_Settings settings;
  uint8_t raw;
} TdefAPCTL;


#endif