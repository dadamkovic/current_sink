/**
 * @file MCP4728.h
 * @author Daniel (daniel@techcraftblog.com)
 * @brief
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef MCP4728_H
#define MCP4728_H

#include "inttypes.h"
#include "MCP4728_registers.h"

// write mode default address
#define MCP4728_ADDRESS_W 0b01111100
// read mode default address
#define MCP4728_ADDRESS_R 0b01111101

typedef enum
{
  MCP_OK,
  MCP_FAIL
} TDefMCPStatus;

/// @brief selects the write / read mode for a command
typedef enum
{
  MCP_WRITE,
  MCP_READ
} TDef_WriteMode;




// initialize MCP4728
TDefMCPStatus mcpInit();
// send command to MCP4728
TDefMCPStatus mcpWriteCommand(void *command);
// transfer 144bits of data to MCP4728 display memory
TDefMCPStatus mcpWriteDisplay(uint8_t data[18], uint8_t addr);
// read data from MCP4728 display memory
TDefMCPStatus mcpReadData(uint8_t data[], uint8_t len, uint8_t addr);
TDefMCPStatus mcpSetAddress(uint8_t addr);
TDefMCPStatus mcpSetICSET(TdefICSET_Settings sett);
TDefMCPStatus mcpSetDISCTL(TdefDISCTL_Settings sett);
TDefMCPStatus mcpSetADSET(uint8_t addr);
#endif