//
//  vm.h
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include <stdint.h>

#ifndef VM_H
#define VM_H

//ram 1MB
#define RAM_SIZE 1048576

//stack 64KB
#define STACK_SIZE 65536

#define PROGRAM_SPACE 983040
#define NUM_REGISTERS 8
#define REGISTER_SIZE 4

uint8_t *ram;
uint32_t *r;
uint32_t *stack;
uint32_t prev_instr;

uint32_t sp;
uint32_t pc;

uint8_t sr;

void allocate_vm();
void copy_memory(uint32_t*, uint8_t*,int);
void exec_program(uint32_t[],int);
#endif