/**
 * Project:     MBVM
 * File:        vm.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include "vm.h"
#include "../system/system.h"
#include "../instructions/instructions.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * Allocates the virtual machine's attributes.
 * 
 * @param ram_size the amount of ram to allocate
 * @param flash_size the amount of flash to allocate
 * @param num_registers the number of registers to allocate
 * @param register_size the size of a register
 * @param stack_size the amount of stack to allocate
 */
void allocate_vm(unsigned int ram_size, unsigned int flash_size,
                 unsigned int num_registers, unsigned int register_size,
                 unsigned int stack_size)
{
    ram = malloc(ram_size);
    flash = malloc(flash_size);
    r = malloc(num_registers * register_size);
    stack = (uint32_t *)(ram + (ram_size - stack_size)); //+ PROGRAM_SPACE;
    sp = 0;
    pc = 0;
    sr = 0;
    dr = r + DATA_REGISTER;
    pr = r + PRINT_REGISTER;

    flash_allocated = 0;

    if (debugging)
    {
        printf("MBVM INIT\n");
        printf("FLASH size: %dMB, @ %p\n",
               flash_size / (1024 * 1024), flash);
        printf("RAM size:   %dMB, @ %p\n",
               ram_size / (1024 * 1024), ram);
        printf("STACK size: %dKB, @ %p\n\n",
               stack_size / (1024), stack);
    }

    // These are set mainly for testing purposes
    configured_ram_size = ram_size;
    configured_flash_size = flash_size;
    configured_num_registers = num_registers;
    configured_stack_size = stack_size;
}

/**
 * Release all the memory used by the VM.
 */
void deallocate_vm()
{
    free(ram);
    ram = NULL;
    free(flash);
    flash = NULL;
    free(r);
    r = NULL;

    stack = NULL;
    sp = 0;
    pc = 0;
    sr = 0;
    dr = NULL;
    pr = NULL;
}

/**
 * Copies 4 byte blocks of memory from source to byte addressable destination.
 * 
 * @param source the pointer to the ram source address
 * @param destination the pointer to the ram destination address
 * @param num_dwords the number of dwords to copy
 * @return 0 if memory could be copied 1 otherwise
 */
int copy_memory(uint8_t *source, uint8_t *destination, int num_dwords)
{
    uint8_t *p_end_of_ram = ram + configured_ram_size;
    int ram_being_allocated = num_dwords * INSTRUCTION_SIZE;

    if ((destination + ram_being_allocated) < p_end_of_ram)
    {
        for (int i = 0; i < num_dwords; i++)
        {
            // Memory is byte addressable but the program image is composed of 4
            // byte instructions and 4 byte data so here it is split into bytes
            // and copied
            *(destination) = (*((uint32_t *)source + i) & 0xFF000000) >> 24;
            *(destination + 1) = (*((uint32_t *)source + i) & 0x00FF0000) >> 16;
            *(destination + 2) = (*((uint32_t *)source + i) & 0x0000FF00) >> 8;
            *(destination + 3) = (*((uint32_t *)source + i) & 0x000000FF);

            // Increment destination counter to next 4 byte block
            destination += INSTRUCTION_SIZE;
        }

        return 0;
    }

    if (debugging)
        printf("\nCopied FLASH image to RAM...\n");

    return 1;
}

/**
 * Begins executing program image.
 */
void exec_program()
{
    if (debugging)
        printf("FLASH has %d DWORDS allocated\n", flash_allocated);

    // Print the entire program image
    disp_image(flash, flash_allocated);
    // Copy the contents of the program to this VM's RAM
    if (0 != copy_memory((uint8_t *)flash, ram, flash_allocated))
    {
        printf("\nERROR: Memory copy failed!\n");
        exit(1);
    }

    if (debugging)
        printf("\nExecuting...\n");

    // This loop executes until the exit instruction is encountered
    while (1)
    {
        // Get the next 4byte block instruction from ram @ pc
        uint32_t next_instr = get_dword(ram, pc);
        // Execute the instruction received
        if (0 != exec(next_instr))
            break;
        // Dump state for debug purposes
        dump_state();
    }
}
