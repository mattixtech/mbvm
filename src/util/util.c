/**
 * Project:     MBVM
 * File:        util.c
 * Author:      Matthew Brooks
 * Created:     2018-07-26
 */

#include <stdint.h>

#include "../instructions/instructions.h"
#include "../io/load.h"
#include "../system/system.h"
#include "../vm/vm.h"

/**
 * Creates an instruction from 'instruction parts'.
 * 
 * @param instr the instruction code
 * @param mode the instruction mode
 * @param d1 the first data byte
 * @param d2 the second data byte
 * @return the 4-byte instruction
 */
uint32_t create_instruction(uint8_t instr, uint8_t mode,
                            uint8_t d1, uint8_t d2)
{
    // TODO: There is probably a better way to do this...
    uint32_t instruction = 0x00000000;
    instruction = (instruction ^ (instr & 0x000000FF) << 24);
    instruction = (instruction ^ (mode & 0x000000FF) << 16);
    instruction = (instruction ^ (d1 & 0x000000FF) << 8);
    instruction = (instruction ^ (d2 & 0x000000FF));

    return instruction;
}

/**
 * Load a hardcoded test program.
 */
void load_test_app()
{
    // Hello world...
    uint32_t program[] =
        {
            create_instruction(INSTR_LOAD, MODE_IMMEDIATE_B, EMPTY_BYTE, 0x10),
            create_instruction(INSTR_STORE, MODE_REGISTER, EMPTY_BYTE, 0x09),
            create_instruction(ADV_INSTR_PRINT, MODE_EXTRA, EMPTY_BYTE,
                               EMPTY_BYTE),
            create_instruction(INSTR_EXIT, EMPTY_BYTE, EMPTY_BYTE, EMPTY_BYTE),
            0x68656C6C, // The string 'hello world\n'
            0x6F20776F,
            0x726C640A};

    // Load it
    load_program(program, sizeof(program) / sizeof(program[0]), flash);
}