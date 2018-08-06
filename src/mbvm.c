/**
 * Project:     MBVM
 * File:        mbvm.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions/instructions.h"
#include "io/load.h"
#include "system/system.h"
#include "util/util.h"
#include "vm/vm.h"

static const char *file_name;

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
    if (argc > 2)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
            debugging = 1;
            file_name = argv[2];
        }
    }else
        file_name = argv[1];

    return 0;
}

/**
 * The main().
 * 
 * @param argc the number of arguments
 * @param argv the array of arguments
 * @return the exit code for this program
 */
int main(int argc, const char *argv[])
{
    if (parse_args(argc, argv) != 0)
        return EXIT_FAILURE;

    // Create the virtual machine in RAM
    // TODO: Take VM init values as command line arguments
    allocate_vm(DEFAULT_RAM_SIZE, DEFAULT_FLASH_SIZE, NUM_REGISTERS,
                REGISTER_SIZE, DEFAULT_STACK_SIZE);

    // Load from the file
    if (0 != load_file(file_name))
    {
        printf("ERROR: Failed to open file '%s'.", file_name);
        return EXIT_FAILURE;
    }

    // Pass the program to the virtual machine and begin executing
    exec_program();
    // Free all the memory we allocated
    deallocate_vm();

    return EXIT_SUCCESS;
}
