/**
 * @file MCP4728.c
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "MCP4728.h"

TDefTransmitMCP *mcpTransmit;
TDefTransmitMCP *mcpReceive;
TDefCyclicBuffer mcp_buffer;
uint8_t memory_map[18];


TDefMCPStatus bufferAdd(uint8_t *data, uint8_t len){
  if((mcp_buffer.tail_idx + len) > BUFF_SIZE){
    return MCP_FAIL;
  }

  uint8_t idx = 0;
  for(uint8_t i=0; i < len; i++){
    idx = mcp_buffer.tail_idx;
    mcp_buffer.element[idx] = data[i];
    mcp_buffer.tail_idx++;
  }
  return MCP_OK;
}

TDefMCPStatus bufferClear(){
  mcp_buffer.tail_idx = 0;
  return MCP_OK;
}


TDefMCPStatus bufferTransmit(){
  if(mcpTransmit == 0){
    return MCP_FAIL;
  };

  TDefMCPStatus ret;
  ret = mcpTransmit(mcp_buffer.element, mcp_buffer.tail_idx);
  ret |= bufferClear();

  return ret;
}


/*TDefMCPStatus memoryMapInit(){
  memory_map[0][0] = 
}*/


TDefMCPStatus mcpInit(TDefTransmitMCP t_func, TDefReceiveMCP r_func){
  mcpTransmit = t_func;
  mcpReceive = r_func;

  TDefMCPStatus ret = MCP_OK;

  bufferClear();

  TdefICSET_Settings icset = {0};
  TdefMODESET_Settings modeset = {0};
  TdefDISCTL_Settings disctl = {0};
  TdefBLKCTL_Settings blkctl = {0};
  TdefAPCTL_Settings apctl = {0};

  //Initialization Sequence
  icset.CLK = INTERNAL_CLK; 
  icset.MEM_SEL = MEM_LOW;
  icset.RESET = EXEC_RESET;

  modeset.DISP_STAT = DISP_OFF;
  
  ret = mcpSetICSET(icset);
  ret |= mcpSetMODESET(modeset);
  ret |= mcpSetADSET(0x00);
  ret |= bufferTransmit();

  //Display on sequence
  icset.CLK = INTERNAL_CLK; 
  icset.MEM_SEL = MEM_LOW;
  icset.RESET = NO_RESET;

  disctl.FREQ_MODE = FREQ_80;
  disctl.INV = INV_LINE;
  disctl.POWER = POW_NORMAL;

  blkctl.BLINK_SET = BLINK_OFF;

  apctl.PIX_SET = PIX_NORMAL;

  modeset.DISP_STAT = DISP_ON;
  /*uint8_t data[18];
  for (uint8_t i = 0; i < 18; i++) {
      data[i] = 0xFF;
  }*/

  ret |= mcpSetICSET(icset);
  ret |= mcpSetDISCTL(disctl);
  ret |= mcpSetBLKCTL(blkctl);
  ret |= mcpSetAPCTL(apctl);
  ret |= mcpSetMODESET(modeset);
  //ret |= mcpWriteDisplay(data, 18, 0x00);
  ret |= bufferTransmit();

  return ret;
}


TDefMCPStatus mcpShutdown(){
  TDefMCPStatus ret;

  bufferClear();

  TdefICSET_Settings icset = {0};
  TdefMODESET_Settings modeset = {0};

  icset.CLK = INTERNAL_CLK; 
  icset.MEM_SEL = MEM_LOW;
  icset.RESET = NO_RESET;

  modeset.DISP_STAT = DISP_OFF;

  ret = mcpSetICSET(icset);
  ret |= mcpSetMODESET(modeset);

  return ret;
}


TDefMCPStatus mcpWriteCommandDisplay(uint8_t command, TDef_CommandDisplay sett){
  if(mcpTransmit == 0){
    return MCP_FAIL;
  };

  if(sett == MCP_RAM_WRITE){
    command = command & ~(1<<7);
  }
  else{
    command = command | (1<<7);
  }

  return bufferAdd(&command, 1);
}


TDefMCPStatus mcpWriteDisplay(uint8_t *data, uint8_t len, uint8_t addr){
  if(mcpTransmit == 0){
    return MCP_FAIL;
  };

  TDefMCPStatus ret;
  ret = bufferAdd(&addr, 1);
  ret |= bufferAdd(data, len);

  return ret;
}


TDefMCPStatus mcpReadData(uint8_t *data, uint8_t len){
  if(mcpReceive == 0){
    return MCP_FAIL;
  };

  return mcpTransmit(data, len);
}


TDefMCPStatus mcpSetADSET(uint8_t addr){
  TdefICSET_Settings ICSET = {0};

  if(addr & (1<<5)){
    ICSET.MEM_SEL = MEM_HIGH;
    mcpSetICSET(ICSET);
    addr = addr & ~(1<<5);
  }

  addr = SET_RAM_WRITE(addr);
  return bufferAdd(&addr, 1);
}


TDefMCPStatus mcpSetICSET(TdefICSET_Settings sett){
  sett._PADDING = 0b11101;
  TdefICSET icset;
  icset.settings = sett;

  return bufferAdd(&icset.raw, 1);
}


TDefMCPStatus mcpSetDISCTL(TdefDISCTL_Settings sett){
  sett._PADDING = 0b101;
  TdefDISCTL disctl;

  disctl.settings = sett;

  return bufferAdd(&disctl.raw, 1);
}


TDefMCPStatus mcpSetMODESET(TdefMODESET_Settings sett){
  sett._PADDING0 = 0b000;
  sett._PADDING1 = 0b1100;
  TdefMODESET modset;

  modset.settings = sett;

  return bufferAdd(&modset.raw, 1);
}


TDefMCPStatus mcpSetBLKCTL(TdefBLKCTL_Settings sett){
  sett._PADDING = 0b11110;
  TdefBLKCTL blkctl;

  blkctl.settings = sett;

  return bufferAdd(&blkctl.raw, 1);
}


TDefMCPStatus mcpSetAPCTL(TdefAPCTL_Settings sett){
  sett._PADDING = 0b111111;
  TdefAPCTL apctl;

  apctl.settings = sett;

  return bufferAdd(&apctl.raw, 1);
}