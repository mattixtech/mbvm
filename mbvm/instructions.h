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

//Basic instructions
#define INSTR_EXIT                  0x00
#define INSTR_NOP                   0xFF

#define INSTR_PUSH                  0xA0
#define INSTR_POP                   0xA1
#define INSTR_PEEK                  0xA2

#define INSTR_LOAD                  0x01
#define INSTR_STORE                 0x02
#define INSTR_ADD                   0x03
#define INSTR_SUB                   0x04

#define INSTR_JMP                   0x10
#define INSTR_JMPZ                  0x11
#define INSTR_JMPNZ                 0x12
#define INSTR_JMPEQ                 0x11
#define INSTR_JMPNEQ                0x12

#define INSTR_CMP                   0x20

//Advanced instructions
#define ADV_INSTR_PRINT             0xFE

//Instruction modes
#define MODE_DEFAULT                0x00
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
#define MODE_EXTRA                  0xFF

void dec_instr(uint32_t);
void push(uint32_t);
uint32_t pop();
uint32_t peek();
void print(char);
#endif