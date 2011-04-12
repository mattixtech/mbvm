//
//  system.h
//  mbvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//
#include <stdint.h>
#ifndef SYSTEM_H
#define SYSTEM_H

#define DEBUG_STATE 1

void exec(uint32_t);
void disp_image(uint32_t*, int);
void dump_state();
void store_dword(uint8_t*, uint32_t, uint32_t);
void store_word(uint8_t*, uint32_t, uint16_t);
void store_byte(uint8_t*, uint32_t, uint8_t);
uint32_t get_dword(uint8_t*, uint32_t);
uint16_t get_word(uint8_t*, uint32_t);
uint8_t get_byte(uint8_t*, uint32_t);
uint32_t incr_pc();
#endif