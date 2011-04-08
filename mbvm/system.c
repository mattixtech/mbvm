//
//  system.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "system.h"
#include "vm.h"
#include "instructions.h"

#include <stdio.h>
#include <stdint.h>

void exec(uint32_t programCode){
    dec_instr(programCode);
    prev_instr = programCode;
    pc++;
}

/*
 *Dumps the machine's state for debugging purposes
 */
void dump_state(){
    printf("\nlast instr: 0x%x\n",prev_instr);
    printf("r0: 0x%x, r1: 0x%x, r2: 0x%x, r3: 0x%x, r4: 0x%x, r5: 0x%x, r6: 0x%x, r7: 0x%x\n",
           r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7]);
    printf("pc: 0x%x, sp: 0x%x\n",pc,sp);
    printf("stack:");
    int start = sp-1;
    for(int i=start;i>=0;i--)
        printf(" 0x%x",stack[i]);
    printf("\n");
    printf("next instr: 0x%x\n\n",ram[pc]);
        
}