/**
 * Project:     MBVM
 * File:        main.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "instructions.h"
#include "system.h"

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

/**
 * Creates an instruction from 'instruction parts'.
 * 
 * @param instr the instruction code
 * @param mode the instruction mode
 * @param d1 the first data byte
 * @param d2 the second data byte
 */
uint32_t create_instruction(unsigned char instr, unsigned char mode,
                            unsigned char d1, unsigned char d2)
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
            0x01010010,
            0x020A0009,
            0xFEFF0000,
            0x00000000,
            0x68656C6C, // The string 'hello world\n'
            0x6F20776F,
            0x726C640A,
        };

    // Load it
    load_program(program, sizeof(program) / sizeof(program[0]), flash);
}

/**
 * The main().
 */
int main(int argc, const char *argv[])
{
    // Simple argument validation
    if (argc < 2 || argc > 3)
    {
        puts("Usage: mbvm [-d] <program file>");

        return 1;
    }

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-d") == 0)
            debugging = 1;
    //printf("%s\n",argv[i-1]);

    // Create the virtual machine in RAM
    allocate_vm();
    // TODO: load in the program specified via command line
    load_test_app();
    // Pass the program to the virtual machine and begin executing
    exec_program();
    // Free all the memory we allocated
    deallocate_vm();

    return 0;
}
