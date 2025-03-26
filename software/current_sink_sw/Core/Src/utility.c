/**
 * @file utility.c
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "utility.h"

 
TDefMCPStatus txMcp(uint8_t *data, uint8_t len){
  HAL_StatusTypeDef ret;
  uint8_t addr = 0;
  while(HAL_I2C_IsDeviceReady(&hi2c1, MCP4728_ADDRESS, 10, HAL_MAX_DELAY) != HAL_OK){};
  ret = HAL_I2C_Master_Transmit(&hi2c1, MCP4728_ADDRESS, data, len, 100);
  if(ret == HAL_OK){
    return MCP_OK;
  }
  else{
    return MCP_FAIL;
  }
}

TDefMCPStatus rxMcp(uint8_t *data, uint8_t len){
  HAL_StatusTypeDef ret;
  
  ret = HAL_I2C_Master_Receive(&hi2c1, MCP4728_ADDRESS, data, len, 100);
  if(ret == HAL_OK){
    return MCP_OK;
  }
  else{
    return MCP_FAIL;
  }
}