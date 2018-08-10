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
                    .op = (uint8_t) ((instr & 0xFF000000) >> 24),
                    // mode is the second most significant byte of the
                    // instruction
                    .mode = (uint8_t) ((instr & 0x00FF0000) >> 16),
                    // d1 is the second least significant byte of the
                    // instruction
                    .d1 = (uint8_t) ((instr & 0x0000FF00) >> 8),
                    // d2 is the least significant byte of the instruction
                    .d2 = (uint8_t) (instr & 0x000000FF),
                    // data is the least significant 2 bytes of the instruction
                    .data = (instr & 0x0000FFFF),
            };

    return ic;
}

/**
 * Executes an instruction.
 * 
 * @return TODO
 */
int exec_instr(struct instruction ic)
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

            return 1;
        case INSTR_NOOP:
            return 0;
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

    return 0;
}

/**
 * Process an instruction by decoding it and then executing it.
 * 
 * @return TODO
 */
int process_instr(uint32_t instr)
{
    return exec_instr(dec_instr(instr));
}