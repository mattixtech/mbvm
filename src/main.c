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
 * Load a hardcoded test program.
 */
void load_test_app()
{
	// Create a program to load into the virtual machine
	// uint32_t program[] =
	// {
	// 	0x01010005,	// LOAD.ib	0x05 	(Load immediate byte 0x05 into dr)
	// 	0x020A0000, // STORE.r	0x00 	(Store into register 0x00 contents of dr)
	// 	0x030A0000, // ADD.r	0x00 	(Add contents of register 0x00 with contents of dr)
	// 	0x020A0009, // STORE.r	0x09	(Store into pr the contents of dr)
	// 	0xFE000000, // PRINT	--		(Print the pr)
	// 	0x020A0000, // STORE.r	0x00 	(Store into register 0x00 contents of dr)
	// 	0x04010009, // SUB.ib	0x09 	(Subtract 0x09 from contents of dr)
	// 	0x020A0000, // STORE.r	0x00 	(Store into register 0x00 contents of dr)
	// 	0x020A0009, // STORE.r	0x09	(Store into pr the contents of dr)
	// 	0xFE000000, // PRINT	--		(Print the pr)
	// 	//0xFD000000, // SCAN		--		(Scan into the pr)
	// 	0x0101000B,	// LOAD.ib	0x0B 	(Load immediate byte 0x0B into dr)
	// 	0xFDFF0000, // SCAN		--		(...)
	// 	0xFF000000, // NOOP
	// 	0x00000000, // Exit
	// };

	uint32_t program[] =
	{
		0x0101000B,	// LOAD.ib	0x0B 	(Load immediate byte 0x0B into dr)
		0xFDFF0000, // SCAN		--		(...)
		0x00000000, // Exit
	};

	load_program(program, sizeof(program) / sizeof(program[0]), flash); // Load it
}

/**
 * The main().
 */
int main (int argc, const char * argv[])
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

	allocate_vm(); 		// Create the virtual machine in RAM
	load_test_app(); 	// TODO: load in the program specified via command line
	exec_program(); 	// Pass the program to the virtual machine and begin executing
	deallocate_vm(); 	// Free all the memory we allocated

	return 0;
}
