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
void dump_state();
uint32_t get_block(uint8_t*, uint32_t);
uint16_t get_word(uint8_t*, uint32_t);
uint8_t get_byte(uint8_t*, uint32_t);
uint32_t incr_pc();
#endif