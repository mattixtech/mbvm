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
 *decodes and executes instruction
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
    
    //memory pointer
    uint32_t mem_addr;
    
    //memory content
    uint32_t mem_data;
    
    //switch based on the operation
    switch(op){      
        case INSTR_EXIT:
            if(DEBUG_STATE){
                printf("exit instruction reached, terminating...\n");
            }
            exit(0); 
            break;
            
        case INSTR_LOAD:
            switch(mode){
                case MODE_IMMEDIATE_B:
                    *dr = d2;
                    break;
                case MODE_IMMEDIATE_W:
                    *dr = data;
                    break;
                case MODE_DATA_32:
                    *dr = get_block(ram, incr_pc());
                    break;
                case MODE_DATA_32_ADDR:
                    mem_addr = get_block(ram, incr_pc());
                    *dr = get_block(ram,mem_addr);
                    break;
                case MODE_DATA_32_ADDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    *dr = get_word(ram,mem_addr);
                    break;  
                case MODE_DATA_32_ADDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    *dr = get_byte(ram,mem_addr);
                    break;
                case MODE_DATA_32_INDR:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_block(ram,mem_addr);
                    break;
                case MODE_DATA_32_INDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_word(ram,mem_addr);
                    break;
                case MODE_DATA_32_INDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_byte(ram,mem_addr);
                    break;
                case MODE_REGISTER:
                    *dr = r[d2]; 
                    break;
                case MODE_REGISTER_ADDR:
                    mem_addr = r[d2];
                    *dr = get_block(ram,mem_addr);
                    break;
                case MODE_REGISTER_ADDR_W:
                    mem_addr = r[d2];
                    *dr = get_word(ram,mem_addr);
                    break;  
                case MODE_REGISTER_ADDR_B:
                    mem_addr = r[d2];
                    *dr = get_byte(ram,mem_addr);
                    break;
                case MODE_REGISTER_INDR:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_block(ram,mem_addr);
                    break;
                case MODE_REGISTER_INDR_W:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_word(ram,mem_addr);
                    break;
                case MODE_REGISTER_INDR_B:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    *dr = get_byte(ram,mem_addr);
                    break;
            }break;
        
        case INSTR_STORE:
            switch(mode){
                case MODE_DATA_32_ADDR:
                    mem_addr = get_block(ram, incr_pc());
                    store_block(ram, mem_addr,*dr);
                    break;
                case MODE_DATA_32_ADDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    store_word(ram, mem_addr,*dr);
                    break;  
                case MODE_DATA_32_ADDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    store_byte(ram, mem_addr,*dr);
                    break;
                case MODE_DATA_32_INDR:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_block(ram, mem_addr,*dr);
                    break;
                case MODE_DATA_32_INDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_word(ram, mem_addr,*dr);
                    break;
                case MODE_DATA_32_INDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_byte(ram, mem_addr,*dr);
                    break;
                case MODE_REGISTER:
                    r[d2] = *dr; 
                    break;
                case MODE_REGISTER_ADDR:
                    mem_addr = r[d2];
                    store_block(ram, mem_addr,*dr);
                    break;
                case MODE_REGISTER_ADDR_W:
                    mem_addr = r[d2];
                    store_word(ram, mem_addr,*dr);
                    break;  
                case MODE_REGISTER_ADDR_B:
                    mem_addr = r[d2];
                    store_byte(ram, mem_addr,*dr);
                    break;
                case MODE_REGISTER_INDR:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_block(ram, mem_addr,*dr);
                    break;
                case MODE_REGISTER_INDR_W:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_word(ram, mem_addr,*dr);
                    break;
                case MODE_REGISTER_INDR_B:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_byte(ram, mem_addr,*dr);
                    break;
            }break;           
        
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
                case MODE_DATA_32_INDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    push(get_word(ram,mem_addr));
                    break;
                case MODE_DATA_32_INDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    push(get_byte(ram,mem_addr));
                    break;
                case MODE_REGISTER:
                    push(r[d2]); 
                    break;
                case MODE_REGISTER_ADDR:
                    mem_addr = r[d2];
                    push(get_block(ram,mem_addr));
                    break;
                case MODE_REGISTER_ADDR_W:
                    mem_addr = r[d2];
                    push(get_word(ram,mem_addr));
                    break;  
                case MODE_REGISTER_ADDR_B:
                    mem_addr = r[d2];
                    push(get_byte(ram,mem_addr));
                    break;
                case MODE_REGISTER_INDR:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    push(get_block(ram,mem_addr));
                    break;
                case MODE_REGISTER_INDR_W:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    push(get_word(ram,mem_addr));
                    break;
                case MODE_REGISTER_INDR_B:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    push(get_byte(ram,mem_addr));
                    break;
            }break;
            
        case INSTR_POP:
            switch(mode){
                case MODE_DATA_32_ADDR:
                    mem_addr = get_block(ram, incr_pc());
                    store_block(ram,mem_addr,pop());
                    break;
                case MODE_DATA_32_ADDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    store_word(ram,mem_addr,pop());
                    break;  
                case MODE_DATA_32_ADDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    store_byte(ram,mem_addr,pop());
                    break;
                case MODE_DATA_32_INDR:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_block(ram,mem_addr,pop());
                    break;
                case MODE_DATA_32_INDR_W:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_word(ram,mem_addr,pop());
                    break;
                case MODE_DATA_32_INDR_B:
                    mem_addr = get_block(ram, incr_pc());
                    mem_addr = get_block(ram, mem_addr);
                    store_byte(ram,mem_addr,pop());
                    break;
                case MODE_REGISTER:
                    r[d2] = pop();
                    break;
                case MODE_REGISTER_ADDR:
                    mem_addr = r[d2];
                    store_block(ram,mem_addr,pop());
                    break;
                case MODE_REGISTER_ADDR_W:
                    mem_addr = r[d2];
                    store_word(ram,mem_addr,pop());
                    break;  
                case MODE_REGISTER_ADDR_B:
                    mem_addr = r[d2];
                    store_byte(ram,mem_addr,pop());
                    break;
                case MODE_REGISTER_INDR:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_block(ram,mem_addr,pop());
                    break;
                case MODE_REGISTER_INDR_W:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_word(ram,mem_addr,pop());
                    break;
                case MODE_REGISTER_INDR_B:
                    mem_addr = r[d2];
                    mem_addr = get_block(ram, mem_addr);
                    store_byte(ram,mem_addr,pop());
                    break;
            }break;

            
        //jump instructions
        case INSTR_JMP:
            mem_addr = get_block(ram, incr_pc());
            if((mem_addr % INSTRUCTION_SIZE) == 0){
                pc = mem_addr-4; //point the pc to the jmp location
                                 //dec_instr(get_block(ram,pc)); //restart the instruction cycle at the new pc
            }
            break;
            
        case INSTR_CMP:
            
            break;
            
        //print has two modes
        //it can either print the char stored in the pr
        //or print the 0 terminated string located in
        //memory pointed to by pr
        case ADV_INSTR_PRINT:
            switch(mode){
                case MODE_DEFAULT:
                    print((char) *pr);
                    break;
                case MODE_EXTRA:
                    mem_addr = *pr;
                    char p_byte = '\00';
                    while((p_byte = get_byte(ram,mem_addr++))){
                        print(p_byte);
                    }
                    break;
            }
            break;            
    }
}

/*
 *prints the raw char data
 */
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
 *returns the 4byte data block from the stack at depth
 */
uint32_t peek(int depth){
    //bounds check to make sure the stack is at least depth high
    if(sp > 0 && (depth+1 <= sp))
        return stack[sp-(depth+1)];
    else
        return 0;
}