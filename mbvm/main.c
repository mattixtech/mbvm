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

//create a program to load into the virtual machine
uint32_t program[] = {
    0xB0070000,
    0x0000000C,
    0x00000000,
    0x00000010,
    0xBBAABBAA
};

int main (int argc, const char * argv[])
{
    //determine how many 4 byte words are in the program
    int size = sizeof(program)/sizeof(uint32_t);
    
    //create the virtual machine in RAM
    allocate_vm();
    
    //pass the program to the virtual machine and begin executing
    exec_program(program,size);
    
    return 0;
}