/**
 * Project:     MBVM
 * File:        test_instructions.c
 * Author:      Matthew Brooks
 * Created:     2018-07-24
 */

#include <CUnit/Basic.h>

#include "test_instructions.h"
#include "../test_utils.h"
#include "../../src/util/util.h"
#include "../../src/instructions/instructions.h"
#include "../../src/instructions/instruction_utils.h"
#include "../../src/system/system.h"
#include "../../src/vm/vm.h"

/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_instructions_test_suite()
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_instructions_test_suite()
{
    return 0;
}

/**
 * Tests 'isntr_exit()'.
 */
void test_instr_exit()
{
    allocate();
    CU_ASSERT(1 == exec(create_instruction(INSTR_EXIT, EMPTY_BYTE, EMPTY_BYTE,
                                           EMPTY_BYTE)));
    deallocate();
}

/**
 * Tests 'isntr_push()'.
 */
void test_instr_push()
{
    // MODE_IMMEDIATE_B
    allocate();
    exec(create_instruction(INSTR_PUSH, MODE_IMMEDIATE_B, EMPTY_BYTE,
                            DUMMY_VALUE_8));
    CU_ASSERT(DUMMY_VALUE_8 == pop());
    deallocate();
    // MODE_IMMEDIATE_W
    allocate();
    exec(create_instruction(INSTR_PUSH, MODE_IMMEDIATE_W, DUMMY_VALUE_8,
                            DUMMY_VALUE_8));
    CU_ASSERT(DUMMY_VALUE_16 == pop());
    deallocate();
    // MODE_DATA_32
    allocate();
    *((uint32_t *) (ram + INSTRUCTION_SIZE)) = DUMMY_VALUE_32;
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();
    // MODE_DATA_32_ADDR
    allocate();
//    *((uint32_t *)(ram + INSTRUCTION_SIZE)) = INSTRUCTION_SIZE * 2;
//    *((uint32_t *) (ram + (INSTRUCTION_SIZE * 2))) = DUMMY_VALUE_32;
//    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_ADDR, EMPTY_BYTE,
//                            EMPTY_BYTE));
//    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();
}

// TODO: Add the rest
