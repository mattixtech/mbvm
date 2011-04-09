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
#define INSTR_NOP                   0xFF

#define INSTR_PUSH                  0xB0
#define INSTR_POP                   0xB1
#define INSTR_PEEK                  0xB2

#define INSTR_MOV                   0x01
#define INSTR_ADD                   0x02
#define INSTR_SUB                   0x03

#define ADV_INSTR_PRINT             0xFE

#define MODE_IMMEDIATE_B            0x01
#define MODE_IMMEDIATE_W            0x02
#define MODE_DATA_32                0x03
#define MODE_DATA_32_ADDR           0x04
#define MODE_DATA_32_ADDR_B         0x05
#define MODE_DATA_32_ADDR_W         0x06
#define MODE_DATA_32_INDR           0x07
#define MODE_DATA_32_INDR_B         0x08
#define MODE_DATA_32_INDR_W         0x09
#define MODE_REGISTER               0x0A
#define MODE_REGISTER_ADDR          0x0B
#define MODE_REGISTER_ADDR_B        0x0C
#define MODE_REGISTER_ADDR_W        0x0D
#define MODE_REGISTER_INDR          0x0E
#define MODE_REGISTER_INDR_B        0x0F
#define MODE_REGISTER_INDR_W        0x10

void dec_instr(uint32_t);
void push(uint32_t);
uint32_t pop();
uint32_t peek();
void print(char);
#endif