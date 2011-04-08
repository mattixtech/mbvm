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
    uint32_t program[] = {0xFE010001,0xFE02AABB,0xFE010003,0xFE010004,0xFE010005,0xB0030000,0xFFEEFFEE,
        0xB0030000,0xABCDABCD,0xB0060000,0xFE060000,0x00000000};
    int size = sizeof(program)/sizeof(uint32_t);
    allocate_vm();    
    exec_program(program,size);
    return 0;
}