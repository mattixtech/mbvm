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
