/**
 * Project:     MBVM
 * File:        test_utils.c
 * Author:      Matthew Brooks
 * Created:     2018-07-31
 */

#include "test_utils.h"
#include "../src/vm/vm.h"

/**
 * Calls allocate_vm() with defaults.
 */
void allocate()
{
    // Initialize the pointers to NULL so we can test that they get initialized
    ram = NULL;
    flash = NULL;
    r = NULL;
    stack = NULL;

    allocate_vm(DEFAULT_RAM_SIZE, DEFAULT_FLASH_SIZE, NUM_REGISTERS,
                REGISTER_SIZE, DEFAULT_STACK_SIZE);
}

/**
 * Calls deallocate_vm().
 */
void deallocate()
{
    deallocate_vm();
}