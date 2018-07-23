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
            create_instruction(INSTR_LOAD, MODE_IMMEDIATE_B, EMPTY_BYTE, 0x10),
            create_instruction(INSTR_STORE, MODE_REGISTER, EMPTY_BYTE, 0x09),
            create_instruction(ADV_INSTR_PRINT, MODE_EXTRA, EMPTY_BYTE,
                               EMPTY_BYTE),
            create_instruction(INSTR_EXIT, EMPTY_BYTE, EMPTY_BYTE, EMPTY_BYTE),
            0x68656C6C, // The string 'hello world\n'
            0x6F20776F,
            0x726C640A,
        };

    // Load it
    load_program(program, sizeof(program) / sizeof(program[0]), flash);
}

/**
 * Check the command line arguments.
 * 
 * @param argc the number of arguments
 * @param argv the array of arguments
 * @return whether or not args were parsed successfully
 */
int parse_args(int argc, const char *argv[])
{
    // Simple argument validation
    if (argc < 2 || argc > 3)
    {
        puts("Usage: mbvm [-d] <program file>");

        return 1;
    }

    // Turn on debugging if -d switch was provided as command line arg
    if (argc > 1)
        if (strcmp(argv[1], "-d") == 0)
            debugging = 1;

    return 0;
}

/**
 * The main().
 * 
 * @param argc the number of arguments
 * @param argv the array of arguments
 */
int main(int argc, const char *argv[])
{
    if (parse_args(argc, argv) != 0)
        return 1;

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
