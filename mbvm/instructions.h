//
//  instructions.h
//  mbvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//
#include <stdint.h>

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define INSTR_EXIT                  0x00000000
#define INSTR_PRINT_SHORT_CHAR      0xFE000000
#define INSTR_PUSH_32               0xB0000000
#define INSTR_POP_32                0xB1000000
#define INSTR_PEEK_32               0xB2000000

void dec_instr(uint32_t instr);
void push(uint32_t data);
uint32_t pop();
uint32_t peek();
void print_short_char(char byte);
#endif