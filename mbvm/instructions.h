//
//  instructions.h
//  mbvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void dec_instr(unsigned int instr);
void push(unsigned int data);
unsigned int pop();
unsigned int peek();

#endif