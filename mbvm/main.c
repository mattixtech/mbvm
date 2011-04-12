//
//  main.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "instructions.h"
#include "system.h"

void test();

//create a program to load into the virtual machine
uint32_t program[] = {
    0x01010000,
    0xFF000000,
    0x01010001,
    0xFF000000,
    0x00000000,
};

void load_program(uint32_t program[], uint32_t *destination, int size){
    for(int i=0;i<size;i++){
        destination[i] = program[i];
        flash_allocated++;
    }
}

int main (int argc, const char * argv[])
{
    test();
    
    //determine how many 4 byte words are in the program
    int size = sizeof(program)/sizeof(uint32_t);
    
    //create the virtual machine in RAM
    allocate_vm();
    
    //load hard-coded program
    load_program(program,flash,size);
    
    //pass the program to the virtual machine and begin executing
    exec_program();
    
    return 0;
}

void test(){
    /*uint8_t *t = malloc(4);
    
    uint32_t move = 0xDDBBCCAA;
    uint8_t stored = move & 0x000000FF;
    
    *(t) = 0xAABBCCDD;
    
    uint8_t t0 = *(t);
    uint8_t t1 = *(t+1);
    uint8_t t2 = *(t+2);
    uint8_t t3 = *(t+3);*/
    
}