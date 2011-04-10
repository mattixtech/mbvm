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

/*
 *allocates the virtual machine's attributes
 */
void allocate_vm(){
    ram     = malloc(RAM_SIZE);
    r       = malloc(NUM_REGISTERS*REGISTER_SIZE);
    stack   = (uint32_t*) (ram + (RAM_SIZE - STACK_SIZE));// + PROGRAM_SPACE;
    sp      = 0;
    pc      = 0;
    sr      = 0;
    
    //point the pr
    pr      = r+PRINT_REGISTER;
    
    if(DEBUG_STATE){
        printf("VM Allocation:\n");
        printf("RAM size:   %dMB, starting address: 0x%x\n",RAM_SIZE/(1024*1024),ram);
        printf("STACK size:  %dKB, starting address: 0x%x\n",STACK_SIZE/(1024),stack);
        printf("Special Registers: pr=r%d\n",PRINT_REGISTER);
    }
}

/*
 *copies 4byte blocks of memory from source to byte addressable destination
 */
void copy_memory(uint32_t *source, uint8_t *destination, int num_blocks){
    //TODO there is no bounds checking here
    for(int i=0;i<num_blocks;i++){
        //memory is byte addressable but the program image is
        //composed of 4byte instructions and 4byte data
        //so here it is split into bytes and copied
        *(destination)      = (*(source+i) & 0xFF000000)>>24;
        *(destination+1)    = (*(source+i) & 0x00FF0000)>>16;
        *(destination+2)    = (*(source+i) & 0x0000FF00)>>8;
        *(destination+3)    = (*(source+i) & 0x000000FF);        
        
        //increment destination counter to next 4byte block
        destination += 4;
    }
}

/*
 *begins executing program image
 */
void exec_program(uint32_t program[],int size){
    
    //print the entire program image
    disp_image(program,size);
    
    //copy the contents of the program to this VM's RAM
    copy_memory(program, ram, size);
    
    printf("\nExecuting...\n");
    //this loop executes until the exit instruction is encountered
    dump_state();
    while(1){
        //get the next 4byte block instruction from ram @ pc
        uint32_t next_instr = get_block(ram,pc);
        
        //execute the instruction received
        exec(next_instr);
        
        //dump state for debug purposes
        dump_state();
    }    
}