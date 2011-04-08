//
//  vm.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "vm.h"
#include "system.h"
#include "instructions.h"

#include <stdlib.h>
#include <stdio.h>

void allocate_vm(){
    ram     = malloc(RAM_SIZE);
    r       = malloc(NUM_REGISTERS*REGISTER_SIZE);
    stack   = malloc(STACK_SIZE);
    sp      = 0;
    pc      = 0;
}

void copy_memory(unsigned int *source, unsigned int *destination,int num_chunks){
    //TODO there is no bounds checking here
    for(int i=0;i<num_chunks;i++)
        *(destination+i) = *(source+i);
}
void exec_program(unsigned int program[],int size){
    copy_memory(program, ram, size);
    while(pc<size){
        exec(ram[pc]);
    }
    
    for(int i=0;i<size;i++)
        printf("%u",pop());
    
}