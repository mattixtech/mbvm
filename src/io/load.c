/**
 * Project:     MBVM
 * File:        load.c
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>

#include "../vm/vm.h"

/**
 * Load the given program into the given memory destination.
 *
 * @param program the program
 * @param size the size of the program in 4 byte words
 * @param destination the memory destination
 */
void load_program(uint32_t program[], int size, uint32_t *destination)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = program[i];
        flash_allocated++;
    }
}