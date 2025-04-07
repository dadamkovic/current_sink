/**
 * @file utility.h
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef UTILITY_H
#define UTILITY_H

#include "i2c.h"
#include "MCP4728.h"

TDefMCPStatus txMcp(uint8_t *data, uint8_t len);
TDefMCPStatus rxMcp(uint8_t *data, uint8_t len);

uint32_t handleEncoder(uint32_t cnt);
uint32_t add_s(uint32_t num, uint32_t add, uint32_t max);
uint32_t sub_s(uint32_t num, uint32_t dec, uint32_t min);

#endif