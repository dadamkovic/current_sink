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
#include "segment_lib.h"

// write mode default address
#define MCP4728_ADDRESS (0b00111110<<1)
#define BUFF_SIZE 64

#define SET_RAM_WRITE(x) (x & ~(1<<7))
#define SET_COMMAND(x) (x & ~(1<<7))

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


typedef TDefMCPStatus TDefTransmitMCP(uint8_t *data, uint8_t len);
typedef TDefMCPStatus TDefReceiveMCP(uint8_t *data, uint8_t len);

typedef struct{
  uint8_t element[BUFF_SIZE];
  uint8_t tail_idx;
}TDefCyclicBuffer;

extern TDefTransmitMCP *mcpTransmit;
extern TDefTransmitMCP *mcpReceive;
extern TDefCyclicBuffer mcp_buffer;
//extern uint8_t memory_map[8][16];

//TDefMCPStatus memoryMapInit();

TDefMCPStatus bufferAdd(uint8_t *data, uint8_t len);
TDefMCPStatus bufferClear();
TDefMCPStatus bufferTransmit();

TDefMCPStatus mcpInit(TDefTransmitMCP *t_func, TDefReceiveMCP *r_func);
TDefMCPStatus mcpShutdown();
TDefMCPStatus mcpWriteCommandDisplay(uint8_t command, TDef_CommandDisplay sett);
TDefMCPStatus mcpWriteDisplay(uint8_t *data, uint8_t len, uint8_t addr);
TDefMCPStatus mcpReadData(uint8_t *data, uint8_t len);
TDefMCPStatus mcpSetICSET(TdefICSET_Settings sett);
TDefMCPStatus mcpSetDISCTL(TdefDISCTL_Settings sett);
TDefMCPStatus mcpSetADSET(uint8_t addr);
TDefMCPStatus mcpSetMODESET(TdefMODESET_Settings sett);
TDefMCPStatus mcpSetBLKCTL(TdefBLKCTL_Settings sett);
TDefMCPStatus mcpSetAPCTL(TdefAPCTL_Settings sett);


#endif