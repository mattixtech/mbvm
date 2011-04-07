//
//  vm.h
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#ifndef VM_H
#define VM_H

#define RAM_SIZE 1024
#define STACK_SIZE 256
#define NUM_REGISTERS 8
#define REGISTER_SIZE 4

unsigned int *ram;
unsigned int *r;
unsigned int *stack;

unsigned int sp;
unsigned int pc;

void allocate_vm();

void exec_program();
#endif