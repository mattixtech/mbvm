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
#include "system/system.h"
#include "test/test_util.h"
#include "vm/vm.h"

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
 * @return the exit code for this program
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
