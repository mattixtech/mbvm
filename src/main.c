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
 * @param destination the memory destination
 */
void load_program(uint32_t program[], uint32_t *destination)
{
	// Determine how many 4 byte words are in the program.
	int size = sizeof(program) / sizeof(uint32_t);

	for (int i = 0; i < size; i++)
	{
		destination[i] = program[i];
		flash_allocated++;
	}
}

/**
 * Load a hardcoded test program.
 */
void load_test_app()
{
	// Create a program to load into the virtual machine.
	uint32_t program[] =
	{
		0x01010005,
		0x020A0000,
		0x01010005,
		0x030A0000,
		0x020A0000,
		0x010A0000,
		0x04010009,
		0x020A0000,
		0x00000000,
		0x00000000
	};

	load_program(program, flash); // Load it.
}

/**
 * The main().
 */
int main (int argc, const char * argv[])
{
	// Simple argument validation.
	if (argc < 2 || argc > 3)
	{
		puts("Usage: mbvm [-d] <program file>");

		return 1;
	}

	for (int i = 1; i < argc; i++)
		if (strcmp(argv[i], "-d") == 0)
			debugging = 1;
	//printf("%s\n",argv[i-1]);

	allocate_vm(); 		// Create the virtual machine in RAM.
	load_test_app(); 	// TODO: load in the program specified via command line.
	exec_program(); 	// Pass the program to the virtual machine and begin executing.
	deallocate_vm(); 	// Free all the memory we allocated.

	return 0;
}
