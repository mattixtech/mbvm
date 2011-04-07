//
//  vm.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "vm.h"
#include "system.h"

#include <stdlib.h>

void allocate_vm(){
    ram     = malloc(RAM_SIZE);
    r       = malloc(NUM_REGISTERS*REGISTER_SIZE);
    stack   = malloc(STACK_SIZE);
    sp      = 0;
    pc      = 0;
}

void exec_program(){
    ram[0] = 0x0001;
    ram[1] = 0x0002;
    ram[2] = 0x0003;
    ram[3] = 0x0004;
    
    while(pc<4){
        exec(ram[pc]);
    }
    
}