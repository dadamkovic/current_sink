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

/// @brief Declaration of transmit function pointer
TDefTransmitMCP *mcpTransmit;
/// @brief Declaration of receive function pointer
TDefTransmitMCP *mcpReceive;
/// @brief Declaration of buffer for holding data to be sent to MCP
TDefCyclicBuffer mcp_buffer;
/// @brief Declaration of segment memory
static uint8_t memory_map[18];


/**
 * @brief Add data into send buffer
 * 
 * @param data Pointer to data
 * @param len Length of data to be added
 * @return TDefMCPStatus 
 */
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

/**
 * @brief Clears all data in the buffer
 * 
 * @return TDefMCPStatus 
 */
TDefMCPStatus bufferClear(){
  mcp_buffer.tail_idx = 0;
  return MCP_OK;
}

/**
 * @brief Transmits all data in the buffer to MCP
 * 
 * @return TDefMCPStatus 
 */
TDefMCPStatus bufferTransmit(){
  if(mcpTransmit == 0){
    return MCP_FAIL;
  };

  TDefMCPStatus ret;
  ret = mcpTransmit(mcp_buffer.element, mcp_buffer.tail_idx);
  ret |= bufferClear();

  return ret;
}

/**
 * @brief To be defined by the user depending on segement mapping
 * 
 */
__attribute__((weak)) uint8_t segmentAddressBit(uint8_t digit, uint16_t segment){
  (void)(digit);
  (void)(segment);
  return 0xff;
}

/**
 * @brief Setups memory data based on the user supplied segment information
 * 
 * @param data 
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetMemoryMap(Tdef_segement *data){
  uint8_t memory_bit = 0;

  for(uint8_t idx=0; idx<MAX_DIGITS; idx++){
    for(uint8_t jdx=0; jdx<MAX_SEGMENTS; jdx++){

      if(data[idx].segments & (1<<jdx)){
        memory_bit = segmentAddressBit(idx+1, (1<<jdx));
        if(memory_bit%8 != 0){
          memory_map[(memory_bit-1)/8] |= (1<<((memory_bit%8)-1)); 
        }
        else{
          memory_map[(memory_bit-1)/8] |= (1<<7); 
        }
      }
    }
  }

  return MCP_OK;
}


/**
 * @brief Sets every memory bit to 0
 * 
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpClearMemoryMap(){
  for(uint8_t idx=0; idx<18; idx++){
    memory_map[idx] = 0x00;
  }

  return MCP_OK;
}


/**
 * @brief Writes ASCII string to the display
 * 
 * @param str Pointer to data to be written
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpWriteString(uint8_t *str){
  Tdef_segement segments[MAX_DIGITS];
  uint8_t seg_idx = 0, str_idx = 0;
  mcpClearMemoryMap();

  while(seg_idx < MAX_DIGITS){
    //Apostrophe gets written before character
    if(str[str_idx] == '\''){
      //move on to the next character
      str_idx++;
      segments[seg_idx] = alphabet[str[str_idx]];
      segments[seg_idx].segment.AP |= SEG_ON;
    }
    //If not apostophe then write character
    else{
      segments[seg_idx] = alphabet[str[str_idx]];
    }
    
    //Dot gets written before character
    if(str[str_idx+1] == '.'){
      segments[seg_idx].segment.DOT |= SEG_ON;
      //move on to the next character
      str_idx++;
    }
    
    //Move on to the next digin & character
    str_idx++;
    seg_idx++;
  }

  //Setup memory map 
  mcpSetMemoryMap(segments);
  //Write memoery to display
  mcpWriteDisplay(memory_map, 18, 0x00);
  return bufferTransmit();
}


/**
 * @brief Write a 'raw' number to the display
 * 
 * @param num Numbmer to be written (empty placess padded with 0s)
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpWriteNumber(uint32_t num){
  uint8_t digit;
  Tdef_segement segments[8];


  mcpClearMemoryMap();

  for(uint8_t i=0; i<8; i++){
    digit = num % 10;
    num = num / 10;
    segments[7-i] = alphabet[digit + 48];
  }

  mcpSetMemoryMap(segments);
  mcpWriteDisplay(memory_map, 18, 0x00);
  return bufferTransmit();
}


/**
 * @brief Initialize the MCP chip
 * 
 * @param t_func Function to be called for transmitting data
 * @param r_func Function to be called fof receiving data
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpInit(TDefTransmitMCP t_func, TDefReceiveMCP r_func){
  mcpTransmit = t_func;
  mcpReceive = r_func;

  TDefMCPStatus ret = MCP_OK;

  //make sure there is nothing in the transmit buffer
  bufferClear();

  //setup all registers
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

  //load up the send transmit with all settings
  ret |= mcpSetICSET(icset);
  ret |= mcpSetDISCTL(disctl);
  ret |= mcpSetBLKCTL(blkctl);
  ret |= mcpSetAPCTL(apctl);
  ret |= mcpSetMODESET(modeset);

  //transmit the buffer to MCP
  ret |= bufferTransmit();

  return ret;
}


/**
 * @brief Turns off the MCP
 * 
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpShutdown(){
  TDefMCPStatus ret;

  //make sure there is nothing in the transmit buffer
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


/**
 * @brief Adds write flag to command and adds the command to the queue be send
 * 
 * @param command Commnad to be send
 * @param sett Flag to determine if command or data is to be send
 * @return TDefMCPStatus 
 */
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


/**
 * @brief Writes the data buffer to the MCP
 * 
 * @param data Memory to be written to the MCP
 * @param len Ammount of data to be written
 * @param addr Address where to write the data
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpWriteDisplay(uint8_t *data, uint8_t len, uint8_t addr){
  //make sure the MCP is initialized
  if(mcpTransmit == 0){
    return MCP_FAIL;
  };

  TDefMCPStatus ret;
  //send the address where data will be written
  ret = bufferAdd(&addr, 1);
  //send the data to be written
  ret |= bufferAdd(data, len);

  return ret;
}


/**
 * @brief Receive data from the MCP
 * 
 * @param data Pointer to the data to be received
 * @param len AMount of data to be received
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpReadData(uint8_t *data, uint8_t len){
  if(mcpReceive == 0){
    return MCP_FAIL;
  };

  return mcpReceive(data, len);
}


/**
 * @brief Set the ADSET register
 * 
 * @param addr Address to be setup
 * @return TDefMCPStatus 
 */
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


/**
 * @brief Add setup data for ICSET to transmit buffer
 * 
 * @param sett ICSET settings
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetICSET(TdefICSET_Settings sett){
  sett._PADDING = 0x1D; //0b11101;
  TdefICSET icset;
  icset.settings = sett;

  return bufferAdd(&icset.raw, 1);
}


/**
 * @brief Add setup data for DISCTL to transmit buffer
 * 
 * @param sett Setup data for DISCTL to transmit buffer
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetDISCTL(TdefDISCTL_Settings sett){
  sett._PADDING = 0x5;  //0b101;
  TdefDISCTL disctl;

  disctl.settings = sett;

  return bufferAdd(&disctl.raw, 1);
}


/**
 * @brief Add setup data for MODESET to transmit buffer
 * 
 * @param sett Setup data for MODESET to transmit buffer
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetMODESET(TdefMODESET_Settings sett){
  sett._PADDING0 = 0x00;  //0b000;
  sett._PADDING1 = 0xC;   //0b1100;
  TdefMODESET modset;

  modset.settings = sett;

  return bufferAdd(&modset.raw, 1);
}


/**
 * @brief Add setup data for BLKCTL to transmit buffer
 * 
 * @param sett Setup data for BLKCTL to transmit buffer
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetBLKCTL(TdefBLKCTL_Settings sett){
  sett._PADDING = 0x1E; //0b11110;
  TdefBLKCTL blkctl;

  blkctl.settings = sett;

  return bufferAdd(&blkctl.raw, 1);
}


/**
 * @brief Add setup data for APCTL to transmit buffer
 * 
 * @param sett Setup data for APCTL to transmit buffer
 * @return TDefMCPStatus 
 */
TDefMCPStatus mcpSetAPCTL(TdefAPCTL_Settings sett){
  sett._PADDING = 0x3F; // 0b111111;
  TdefAPCTL apctl;

  apctl.settings = sett;

  return bufferAdd(&apctl.raw, 1);
}