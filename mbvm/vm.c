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
#include <stdint.h>

void allocate_vm(){
    ram     = malloc(RAM_SIZE);
    r       = malloc(NUM_REGISTERS*REGISTER_SIZE);
    stack   = malloc(STACK_SIZE);
    sp      = 0;
    pc      = 0;
    sr      = 0;
}

void copy_memory(uint32_t *source, uint32_t *destination,int num_chunks){
    //TODO there is no bounds checking here
    for(int i=0;i<num_chunks;i++)
        *(destination+i) = *(source+i);
}
void exec_program(uint32_t program[],int size){
    //copy the contents of the program to this VM's RAM
    copy_memory(program, ram, size);
    
    //this loop executes until the exit instruction is encountered
    while(1){
        exec(ram[pc]);
        dump_state();
    }    
}