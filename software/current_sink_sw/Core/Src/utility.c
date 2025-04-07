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

/**
 * @brief Transmit function wrapper for MCP
 * 
 * @param data Pointer to data to be transmitted
 * @param len Length of data to be transmitted
 * @return TDefMCPStatus 
 */
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


/**
 * @brief Receive function wrapper for MCP
 * 
 * @param data Pointer to memory for received data
 * @param len Length of received data
 * @return TDefMCPStatus 
 */
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


uint32_t handleEncoder(uint32_t cnt){
  GPIO_PinState enc_a, enc_b, enc_sw = GPIO_PIN_RESET;
  static uint32_t inc = 1;
  HAL_Delay(5);
  enc_a = HAL_GPIO_ReadPin(ENCODER_A_GPIO_Port, ENCODER_A_Pin);
  enc_b = HAL_GPIO_ReadPin(ENCODER_B_GPIO_Port, ENCODER_B_Pin);
  enc_sw = HAL_GPIO_ReadPin(ENCODER_SW_GPIO_Port, ENCODER_SW_Pin);

  if(enc_sw == GPIO_PIN_RESET){
    inc *= 10;
    HAL_Delay(300);
    return cnt;
  }

  if(enc_a == GPIO_PIN_SET){
      if(enc_b == GPIO_PIN_RESET){
        cnt = add_s(cnt, inc, DISP_MAX);
      }
      else{
        cnt = sub_s(cnt, inc, DISP_MIN);
      }
  }

  if(enc_a == GPIO_PIN_RESET){
    if(enc_b == GPIO_PIN_RESET){
      cnt = sub_s(cnt, inc, DISP_MIN);
    }
    else{
      cnt = add_s(cnt, inc, DISP_MAX);
    }
  }

  return cnt;
}

uint32_t add_s(uint32_t num, uint32_t add, uint32_t max){
  return ((num + add) >= max) ? max : (num + add);
}

uint32_t sub_s(uint32_t num, uint32_t dec, uint32_t min){
  return ((num - dec) >= num || (num - dec) <= min) ? min : (num - dec);
}