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

//write mode default address
#define MCP4728_ADDRESS_W 0b01111100
//read mode default address        
#define MCP4728_ADDRESS_R 0b01111101

typedef enum{
    MCP_OK,
    MCP_FAIL
}TDef_MCP_Status;

//initialize MCP4728
TDef_MCP_Status mcpInit();
//send command to MCP4728
TDef_MCP_Status mcpWriteCommand(uint8_t command[], uint8_t len);
//transfer 144bits of data to MCP4728 display memory
TDef_MCP_Status mcpWriteDisplay(uint8_t data[18]);
//read data from MCP4728 display memory
TDef_MCP_Status mcpReadDisplay(uint8_t data[], uint8_t len, uint8_t addr);

#endif