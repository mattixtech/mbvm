//
//  instructions.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "instructions.h"
#include "vm.h"

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
    
    //switch based on the operation
    switch(op){
    case INSTR_EXIT:
        exit(0); break;
    case INSTR_PUSH:
            switch(mode){
                case MODE_IMMEDIATE_B:
                    break;
                case MODE_IMMEDIATE_W:
                   break;
                case MODE_DATA_32:
                    push(ram[++pc]); break;
                case MODE_REGISTER:
                    push(r[d2]); break;
            }break;        
    case INSTR_POP:
        pop(); break;
    case INSTR_PRINT:
            switch(mode){
                case MODE_IMMEDIATE_B:
                    print_byte(d2); break;
                case MODE_IMMEDIATE_W:
                    print_word(data); break;
                case MODE_DATA_32:
                    print_32(ram[++pc]); break;
                case MODE_REGISTER:
                    print_32(r[d2]); break;
            }break;
    }
}

void print_byte(uint8_t byte){
    printf("%x\n",byte);
}

void print_word(uint16_t word){
    printf("%x\n",word);
}

void print_32(uint32_t data){
    printf("%x\n",data);
}

/*
 *
 */
void push(uint32_t data){
    stack[sp++] = data;
}

/*
 *
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