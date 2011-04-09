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
    incr_pc();
}

/*
 *returns the 4byte block found in loc @ image_addr
 */
uint32_t get_block(uint8_t* loc, uint32_t image_addr){
    uint32_t b0 = loc[image_addr+0]<<24;
    uint32_t b1 = loc[image_addr+1]<<16;
    uint32_t b2 = loc[image_addr+2]<<8;
    uint32_t b3 = loc[image_addr+3];
    return 0x00000000 | b0 | b1 | b2 | b3;
}

/*
 *returns the 2byte word found in loc @ image_addr
 */
uint16_t get_word(uint8_t* loc, uint32_t image_addr){
    uint16_t b0 = loc[image_addr+0]<<8;
    uint8_t b1 = loc[image_addr+1];
    return 0x0000 | b0 | b1;
}

/*
 *returns the byte found in loc @ image_addr
 */
uint8_t get_byte(uint8_t* loc, uint32_t image_addr){
    uint8_t b = loc[image_addr];
    return 0x00 | b;
}

/*
 *points the pc to the next 4 byte block and returns the incremented pc
 */
uint32_t incr_pc(){
    pc += 4;
    return pc;
}

/*
 *dumps the machine's state for debugging purposes
 */
void dump_state(){
    printf("\nlast instr: 0x%x\n",prev_instr);
    printf("r0: 0x%x, r1: 0x%x, r2: 0x%x, r3: 0x%x, r4: 0x%x, r5: 0x%x, r6: 0x%x, r7: 0x%x\n",
           r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7]);
    printf("pc: 0x%x, sp: 0x%x, sr: 0x%x\n",pc,sp,sr);
    printf("stack:");
    int start = sp-1;
    for(int i=start;i>=0;i--)
        printf(" 0x%x",stack[i]);
    printf("\n");
    printf("next instr: 0x%x\n\n",get_block(ram, pc));
        
}