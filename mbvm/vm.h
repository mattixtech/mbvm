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

#define RAM_SIZE 1024
#define STACK_SIZE 256
#define NUM_REGISTERS 8
#define REGISTER_SIZE 4

uint32_t *ram;
uint32_t *r;
uint32_t *stack;
uint32_t prev_instr;

uint32_t sp;
uint32_t pc;

uint8_t sr;

void allocate_vm();
void copy_memory(uint32_t*, uint32_t*,int);
void exec_program(uint32_t[],int);
#endif