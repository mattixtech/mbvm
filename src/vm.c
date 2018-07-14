/* 
 * Project:     MBVM
 * File:        vm.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

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
    flash   = malloc(FLASH_SIZE);
    r       = malloc(NUM_REGISTERS*REGISTER_SIZE);
    stack   = (uint32_t*) (ram + (RAM_SIZE - STACK_SIZE));// + PROGRAM_SPACE;
    sp      = 0;
    pc      = 0;
    sr      = 0;    
    dr      = r+DATA_REGISTER;
    pr      = r+PRINT_REGISTER;
    
    flash_allocated = 0;
    
    if(debugging){
        printf("MBVM INIT\n");
        printf("FLASH size:   %dMB, starting address: 0x%X\n",FLASH_SIZE/(1024*1024),(unsigned int) flash);
        printf("RAM size:   %dMB, starting address: 0x%X\n",RAM_SIZE/(1024*1024),(unsigned int) ram);
        printf("STACK size:  %dKB, starting address: 0x%X\n",STACK_SIZE/(1024),(unsigned int) stack);
    }
}

/*
 *release all the memory used by the VM
 */
void deallocate_vm(){
    free(ram);
    free(flash);
    free(r);
}

/*
 *copies 4byte blocks of memory from source to byte addressable destination
 */
void copy_memory(uint32_t *source, uint8_t *destination, int num_dwords){
    //TODO there is no bounds checking here
    for(int i=0;i<num_dwords;i++){
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
    
    if(debugging)
        printf("\nCopied FLASH image to RAM...\n");
}

/*
 *begins executing program image
 */
void exec_program(){
    
    if(debugging)
        printf("FLASH has %d DWORDS allocated\n",flash_allocated);
    //print the entire program image
    disp_image(flash,flash_allocated);
    
    //copy the contents of the program to this VM's RAM
    copy_memory(flash, ram, flash_allocated);
    if(debugging)
        printf("\nExecuting...\n");
    //this loop executes until the exit instruction is encountered
    dump_state();
    while(1){
        //get the next 4byte block instruction from ram @ pc
        uint32_t next_instr = get_dword(ram,pc);
        
        //execute the instruction received
        exec(next_instr);
        
        //dump state for debug purposes
        dump_state();
    }    
}