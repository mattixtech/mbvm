/**
 * Project:     MBVM
 * File:        instructions.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include "instructions.h"
#include "instruction_utils.h"
#include "../system/system.h"
#include "../vm/vm.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * The 'EXIT' instruction.
 */
void instr_exit()
{
    if (debugging)
        printf("exit instruction reached, terminating...\n");

    //exit(0);
}

/**
 * The 'LOAD' instruction.
 * 
 * @param ic the instruction
 */
void instr_load(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_IMMEDIATE_B:
            *dr = ic.d2;
            break;
        case MODE_IMMEDIATE_W:
            *dr = ic.data;
            break;
        case MODE_DATA_32:
            *dr = get_dword(ram, incr_pc());
            break;
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            *dr = get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            *dr = get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            *dr = get_byte(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER:
            *dr = r[ic.d2];
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            *dr = get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            *dr = get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            *dr = get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr = get_byte(ram, mem_addr);
            break;
        default:
            unsupported_mode(ic.mode);
    }

    alter_sr();
}

/**
 * The 'STORE' instruction.
 * 
 * @param ic the instruction
 */
void instr_store(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            store_dword(ram, mem_addr, *dr);
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            store_word(ram, mem_addr, *dr);
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            store_byte(ram, mem_addr, *dr);
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, *dr);
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, *dr);
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER:
            r[ic.d2] = *dr;
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            store_dword(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            store_word(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            store_byte(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, *dr);
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, *dr);
            break;
        default:
            unsupported_mode(ic.mode);
    }

    alter_sr();
}

/**
 * The 'ADD' instruction.
 * 
 * @param ic the instruction
 */
void instr_add(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_IMMEDIATE_B:
            *dr += ic.d2;
            break;
        case MODE_IMMEDIATE_W:
            *dr += ic.data;
            break;
        case MODE_DATA_32:
            *dr += get_dword(ram, incr_pc());
            break;
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            *dr += get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            *dr += get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            *dr += get_byte(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER:
            *dr += r[ic.d2];
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            *dr += get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            *dr += get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            *dr += get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr += get_byte(ram, mem_addr);
            break;
        default:
            unsupported_mode(ic.mode);
    }

    alter_sr();
}

/**
 * The 'SUB' instruction.
 * 
 * @param ic the instruction
 */
void instr_sub(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_IMMEDIATE_B:
            *dr -= ic.d2;
            break;
        case MODE_IMMEDIATE_W:
            *dr -= ic.data;
            break;
        case MODE_DATA_32:
            *dr -= get_dword(ram, incr_pc());
            break;
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            *dr -= get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            *dr -= get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            *dr -= get_byte(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_dword(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_word(ram, mem_addr);
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER:
            *dr -= r[ic.d2];
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            *dr -= get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            *dr -= get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            *dr -= get_byte(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_dword(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_word(ram, mem_addr);
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            *dr -= get_byte(ram, mem_addr);
            break;
        default:
            unsupported_mode(ic.mode);
    }

    alter_sr();
}

/**
 * The 'PUSH' instruction.
 * 
 * @param ic the instruction
 */
void instr_push(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_IMMEDIATE_B:
            push(ic.d2);
            break;
        case MODE_IMMEDIATE_W:
            push(ic.data);
            break;
        case MODE_DATA_32:
            push(get_dword(ram, incr_pc()));
            break;
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            push(get_dword(ram, mem_addr));
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            push(get_word(ram, mem_addr));
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            push(get_byte(ram, mem_addr));
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            push(get_dword(ram, mem_addr));
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            push(get_word(ram, mem_addr));
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            push(get_byte(ram, mem_addr));
            break;
        case MODE_REGISTER:
            push(r[ic.d2]);
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            push(get_dword(ram, mem_addr));
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            push(get_word(ram, mem_addr));
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            push(get_byte(ram, mem_addr));
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            push(get_dword(ram, mem_addr));
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            push(get_word(ram, mem_addr));
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            push(get_byte(ram, mem_addr));
            break;
        default:
            unsupported_mode(ic.mode);
    }
}

/**
 * The 'POP' instruction.
 * 
 * @param ic the instruction
 */
void instr_pop(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            store_dword(ram, mem_addr, pop());
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            store_word(ram, mem_addr, pop());
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            store_byte(ram, mem_addr, pop());
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, pop());
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, pop());
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, pop());
            break;
        case MODE_REGISTER:
            r[ic.d2] = pop();
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            store_dword(ram, mem_addr, pop());
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            store_word(ram, mem_addr, pop());
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            store_byte(ram, mem_addr, pop());
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, pop());
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, pop());
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, pop());
            break;
        default:
            unsupported_mode(ic.mode);
    }
}

/**
 * The 'PEEK' instruction.
 * 
 * @param ic the instruction
 */
void instr_peek(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_DATA_32_ADDR:
            mem_addr = get_dword(ram, incr_pc());
            store_dword(ram, mem_addr, peek(0));
            break;
        case MODE_DATA_32_ADDR_W:
            mem_addr = get_dword(ram, incr_pc());
            store_word(ram, mem_addr, peek(0));
            break;
        case MODE_DATA_32_ADDR_B:
            mem_addr = get_dword(ram, incr_pc());
            store_byte(ram, mem_addr, peek(0));
            break;
        case MODE_DATA_32_INDR:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, peek(0));
            break;
        case MODE_DATA_32_INDR_W:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, peek(0));
            break;
        case MODE_DATA_32_INDR_B:
            mem_addr = get_dword(ram, incr_pc());
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER:
            r[ic.d2] = peek(0);
            break;
        case MODE_REGISTER_ADDR:
            mem_addr = r[ic.d2];
            store_dword(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER_ADDR_W:
            mem_addr = r[ic.d2];
            store_word(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER_ADDR_B:
            mem_addr = r[ic.d2];
            store_byte(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER_INDR:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_dword(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER_INDR_W:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_word(ram, mem_addr, peek(0));
            break;
        case MODE_REGISTER_INDR_B:
            mem_addr = r[ic.d2];
            mem_addr = get_dword(ram, mem_addr);
            store_byte(ram, mem_addr, peek(0));
            break;
        default:
            unsupported_mode(ic.mode);
    }
}

/**
 * The 'JMP' instruction.
 * 
 * @param ic the instruction
 */
void instr_jmp(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    // TODO: add the other jump modes
    mem_addr = get_dword(ram, incr_pc());

    // TODO: I don't think this will always be true
    if ((mem_addr % INSTRUCTION_SIZE) == 0)
    {
        switch (ic.mode)
        {
            case MODE_DEFAULT:
                // Point the pc to the jmp location
                pc = mem_addr - 4;
                break;
            case JUMP_MODE_JMPEQ:
                if (zb_tst())
                    // Point the pc to the jmp location
                    pc = mem_addr - 4;
                break;
            case JUMP_MODE_JMPNEQ:
                if (!zb_tst())
                    // Point the pc to the jmp location
                    pc = mem_addr - 4;
                break;
            default:
                unsupported_mode(ic.mode);
        }
    }
}

/**
 * Saves the current program state on the stack.
 */
void instr_function_call()
{
    // Push registers onto stack
    for (int i = 0; i < NUM_REGISTERS; i++)
        push(r[i]);

    push(pc);
    push(sr);
}

/**
 * Restores the program state from the stack.
 */
void instr_function_return()
{
    sr = (uint8_t) pop();
    pc = pop();

    // Restore registers from stack
    for (int i = NUM_REGISTERS - 1; i >= 0; i--)
        r[i] = pop();
}

/**
 * The 'PRINT' instruction.
 * 
 * @param ic the instruction
 */
void instr_adv_print(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    // Print has two modes
    // 1. print the char stored in the pr
    // 2. print the 0 terminated string located in the memory pointed to by pr
    switch (ic.mode)
    {
        case MODE_DEFAULT:
            print((char) *pr);
            break;
        case MODE_EXTRA:
            mem_addr = *pr;
            char p_byte = '\00';
            while ((p_byte = get_byte(ram, mem_addr++)))
                print(p_byte);

            break;
        default:
            unsupported_mode(ic.mode);
    }
}

/**
 * The 'SCAN' instruction.
 * 
 * @param ic the instruction
 */
void instr_adv_scan(struct instruction ic)
{
    // memory pointer
    uint32_t mem_addr;

    switch (ic.mode)
    {
        case MODE_DEFAULT:
            // Scan the character literal into pr
            scanf("%c", (char *) pr);
            break;
        case MODE_EXTRA:
            mem_addr = *pr;
            fgets((char *) (ram + mem_addr), *dr, stdin);
            break;
        default:
            unsupported_mode(ic.mode);
    }
}
