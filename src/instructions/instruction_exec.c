/**
 * Project:     MBVM
 * File:        instruction_exec.c
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>

#include "instructions.h"

/**
 * Decodes an instruction.
 * 
 * @return the decoded instruction
 */
struct instruction dec_instr(uint32_t instr)
{
    struct instruction ic =
        {
            // op is the most significant byte of the instruction
            .op = (char)((instr & 0xFF000000) >> 24),
            // mode is the second most significant byte of the instruction
            .mode = (char)((instr & 0x00FF0000) >> 16),
            // d1 is the second least significant byte of the instruction
            .d1 = (char)((instr & 0x0000FF00) >> 8),
            // d2 is the least significant byte of the instruction
            .d2 = (char)(instr & 0x000000FF),
            // data is the least significant 2 bytes of the instruction
            .data = (instr & 0x0000FFFF),
        };

    return ic;
}

/**
 * Executes an instruction.
 */
void exec_instr(struct instruction ic)
{
    // memory content
    // TODO: Unused
    // uint32_t mem_data;

    // Switch based on the operation
    switch (ic.op)
    {
        // Regular Instructions...
    case INSTR_EXIT:
        instr_exit();
        break;
    case INSTR_LOAD:
        instr_load(ic);
        break;
    case INSTR_STORE:
        instr_store(ic);
        break;
    case INSTR_ADD:
        instr_add(ic);
        break;
    case INSTR_SUB:
        instr_sub(ic);
        break;
    case INSTR_PUSH:
        instr_push(ic);
        break;
    case INSTR_POP:
        instr_pop(ic);
        break;
    case INSTR_PEEK:
        instr_peek(ic);
        break;
    case INSTR_JMP:
        instr_jmp(ic);
        break;
    case INSTR_FCAL:
        instr_function_call();
        break;
    case INSTR_FRET:
        instr_function_return();
        break;
        // Advanced Instructions...
    case ADV_INSTR_PRINT:
        instr_adv_print(ic);
        break;
    case ADV_INSTR_SCAN:
        instr_adv_scan(ic);
        break;
    }
}

/**
 * Process an instruction by decoding it and then executing it.
 */
void process_instr(uint32_t instr)
{
    exec_instr(dec_instr(instr));
}