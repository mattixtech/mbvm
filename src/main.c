/* 
 * Project:     MBVM
 * File:        main.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "instructions.h"
#include "system.h"

void test();

//create a program to load into the virtual machine
uint32_t program[] = {
    0x01010005,
    0x020A0000,
    0x01010005,
    0x030A0000,
    0x020A0000,
    0x010A0000,
    0x04010009,
    0x020A0000,
    0x00000000,
    0x00000000
};

void load_program(uint32_t program[], uint32_t *destination, int size){
    for(int i=0;i<size;i++){
        destination[i] = program[i];
        flash_allocated++;
    }
}

int main (int argc, const char * argv[])
{    
    if(argc < 2)
    {
        puts("Usage: mbvm [-d] <program file>");
        return 1;
    }
    int i;
    for(i=1;i<argc;i++){        
        if(strcmp(argv[i],"-d") == 0){
            debugging = 1;
        }
    }
    //printf("%s\n",argv[i-1]);
    
    //determine how many 4 byte words are in the program
    int size = sizeof(program)/sizeof(uint32_t);
    
    //create the virtual machine in RAM
    allocate_vm();
    
    //load hard-coded program
    load_program(program,flash,size);
    
    //pass the program to the virtual machine and begin executing
    exec_program();
    
    //release VM memory
    deallocate_vm();
    
    return 0;
}