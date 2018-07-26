/**
 * Project:     MBVM
 * File:        test_vm.c
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#include <CUnit/Basic.h>

#include "../../src/vm/vm.h"

/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_vm_test_suite()
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_vm_test_suite()
{
    return 0;
}

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
 * Calls deallocate_vm();
 */
void deallocate()
{
    deallocate_vm();
}

/**
 * Tests 'allocate_vm()'.
 */
void test_allocate_vm()
{
    allocate();
    // Check the basic attributes of the VM
    CU_ASSERT(ram != NULL && configured_ram_size == DEFAULT_RAM_SIZE);
    CU_ASSERT(flash != NULL && configured_flash_size == DEFAULT_FLASH_SIZE);
    CU_ASSERT(r != NULL && configured_num_registers == NUM_REGISTERS);
    CU_ASSERT(stack != NULL && configured_stack_size == DEFAULT_STACK_SIZE);
    deallocate();
}

/**
 * Tests 'allocate_vm()'.
 */
void test_deallocate_vm()
{
    allocate();
    deallocate();

    CU_ASSERT(ram == NULL);
    CU_ASSERT(flash == NULL);
    CU_ASSERT(r == NULL);
    CU_ASSERT(stack == NULL);
    CU_ASSERT(dr == NULL);
    CU_ASSERT(pr == NULL);
    CU_ASSERT(sp == 0);
    CU_ASSERT(pc == 0);
    CU_ASSERT(sr == 0);
}

/**
 * Tests 'copy_memory()'.
 */
void test_copy_memory()
{
    // TODO
}

/**
 * Tests 'exec_program()'.
 */
void test_exec_program()
{
    // TODO
}