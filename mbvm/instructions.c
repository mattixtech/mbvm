//
//  instructions.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "instructions.h"
#include "vm.h"

/*
 *
 */
void dec_instr(unsigned int instr){
    
}

/*
 *
 */
void push(unsigned int data){
    stack[sp++] = data;
}

/*
 *
 */
unsigned int pop(){
    return stack[--sp];
}

/*
 *
 */
unsigned int peek(){
    return stack[sp];
}