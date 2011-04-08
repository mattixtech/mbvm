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

int main (int argc, const char * argv[])
{   
    unsigned int program[] = {0,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009};
    int size = sizeof(program)/sizeof(unsigned int);
    allocate_vm();    
    exec_program(program,size);
    return 0;
}