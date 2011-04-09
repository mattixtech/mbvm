//
//  instructions.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "instructions.h"
#include "vm.h"
#include "system.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
 *
 */
void dec_instr(uint32_t instr){
    //op is the most significant byte of the instruction
    unsigned char op    = (char) ((instr & 0xFF000000)>>24);
    
    //mode is the second most significant byte of the instruction
    unsigned char mode  = (char) ((instr & 0x00FF0000)>>16);
    
    //d1 is the second least significant byte of the instruction
    unsigned char d1    = (char) ((instr & 0x0000FF00)>>8);
    
    //d2 is the least significant byte of the instruction
    unsigned char d2    = (char) (instr & 0x000000FF);
    
    //data is the least significant 2 bytes of the instruction
    uint16_t data = (instr & 0x0000FFFF);
    
    uint32_t mem_addr;
    uint32_t mem_data;
    
    //switch based on the operation
    switch(op){
    case INSTR_EXIT:
        exit(0); 
        break;
    case INSTR_PUSH:
            switch(mode){
                case MODE_IMMEDIATE_B:
                    push(d2);
                    break;
                case MODE_IMMEDIATE_W:
                    push(data);
                   break;
                case MODE_DATA_32:
                    push(get_block(ram, incr_pc()));
                    break;
                case MODE_DATA_32_ADDR:
                    mem_addr = get_block(ram, incr_pc());
                    push(get_block(ram,mem_addr));
                    break;
                case MODE_DATA_32_ADDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    push(get_word(ram,mem_addr));
                    break;  
                case MODE_DATA_32_ADDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    push(get_byte(ram,mem_addr));
                    break;
                case MODE_DATA_32_INDR:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    push(get_block(ram,mem_addr));
                    break;
                case MODE_REGISTER:
                    push(r[d2]); 
                    break;
            }break;        
    case INSTR_POP:
        pop(); 
        break;
    case INSTR_PRINT:
            switch(mode){
                case MODE_IMMEDIATE_B:
                    print(d2);
                    break;
                case MODE_IMMEDIATE_W:
                    print(d1);
                    print(d2);
                    break;
                case MODE_DATA_32:
                    print(get_block(ram, incr_pc()));
                    break;
                case MODE_REGISTER:
                    print(r[d2]);
                    break;
            }break;
    }
}

void print(char data){
    printf("%c",data);
}

/*
 *pushes the 4byte data block onto the stack and realigns the sp
 */
void push(uint32_t data){
    stack[sp++] = data;
}

/*
 *pops the 4byte data block off of the stack and realigns the sp
 */
uint32_t pop(){
    return stack[--sp];
}

/*
 *
 */
uint32_t peek(int depth){
    if(sp > 0)
        return stack[sp-(depth+1)];
    else
        return 0;
}