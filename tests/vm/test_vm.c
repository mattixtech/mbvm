/**
 * Project:     MBVM
 * File:        test_vm.c
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#include <CUnit/Basic.h>

#include "../test_utils.h"
#include "../../src/instructions/instructions.h"
#include "../../src/io/load.h"
#include "../../src/system/system.h"
#include "../../src/util/util.h"
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
    allocate();

    // We don't need to test a TON of ram...
    int num_instructions = (configured_ram_size / 2 > 1000)
                           ? 1000
                           : configured_ram_size / 2;
    uint32_t instruction_array[num_instructions];

    for (int i = 0; i < num_instructions; i++)
    {
        uint8_t *p_ram = ram + (i * INSTRUCTION_SIZE);
        instruction_array[i] = create_instruction(i, i, i, i);
        *((uint32_t *) p_ram) = instruction_array[i];
    }

    // Find the next available ram
    int used_ram = INSTRUCTION_SIZE * num_instructions;
    uint8_t *p_dest = ram + used_ram;
    CU_ASSERT(0 == copy_memory(ram, p_dest, num_instructions));
    int failed_match = 0;

    // Check the memory where we copied to and verify it is the same as the
    // source data
    for (int i = 0; i < num_instructions; i++)
    {
        if ((((uint32_t *) p_dest)[i] != instruction_array[i]))
        {
            failed_match = 1;
            break;
        }
    }

    CU_ASSERT(0 == failed_match);

    // Check that we can't write past our allocated RAM
    CU_ASSERT(1 == copy_memory(ram, p_dest + configured_ram_size,
                               num_instructions));
    deallocate();
}

/**
 * Tests 'exec_program()'.
 */
void test_exec_program()
{
    allocate();
    uint32_t test_instructions[2] = {
            create_instruction(INSTR_NOP, EMPTY_BYTE, EMPTY_BYTE, EMPTY_BYTE),
            create_instruction(INSTR_EXIT, EMPTY_BYTE, EMPTY_BYTE, EMPTY_BYTE)};
    load_program(test_instructions,
                 sizeof(test_instructions) / sizeof(test_instructions[0]),
                 flash);
    exec_program();
    // TODO: Maybe there is a better way to test this
    // This is a very trivial test just to check that the pc was incremented
    // after executing a no op
    CU_ASSERT(0 != pc);
    deallocate();
}