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
    uint32_t op = instr & 0xFF000000;
    switch(op){
    case INSTR_EXIT:
        exit(0); break;
    case INSTR_PUSH_32:
        push(ram[++pc]); break;
    case INSTR_POP_32:
        pop(); break;
    case INSTR_PRINT_SHORT_CHAR:
        print_short_char((char)(instr & 0x000000FF)); break;
    }
}

void print_short_char(char byte){
    printf("%d\n",byte);
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