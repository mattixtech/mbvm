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

#define INSTR_EXIT                  0x00
#define INSTR_PRINT                 0xFE
#define INSTR_PUSH                  0xB0
#define INSTR_POP                   0xB1
#define INSTR_PEEK                  0xB2

#define MODE_IMMEDIATE_B            0x01
#define MODE_IMMEDIATE_W            0x02
#define MODE_DATA_32                0x03
#define MODE_ADDR                   0x04
#define MODE_INDR_ADDR              0x05
#define MODE_REGISTER               0x06

void dec_instr(uint32_t instr);
void push(uint32_t data);
uint32_t pop();
uint32_t peek();
void print_byte(uint8_t byte);
void print_word(uint16_t word);
#endif