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

    // The instruction locations for the successive instructions after our push
    // to help with addressing and indirection
    const int NEXT_INSTR = INSTRUCTION_SIZE;
    const int NEXT2_INSTR = INSTRUCTION_SIZE * 2;
    const int NEXT3_INSTR = INSTRUCTION_SIZE * 3;

    // MODE_DATA_32_ADDR
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store a dummy value in ram[instr*2]
    store_dword(ram, NEXT2_INSTR, DUMMY_VALUE_32);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_ADDR, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();

    // MODE_DATA_32_ADDR_W
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store a dummy value in ram[instr*2]
    store_word(ram, NEXT2_INSTR, DUMMY_VALUE_16);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_ADDR_W, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_16 == pop());
    deallocate();

    // MODE_DATA_32_ADDR_B
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store a dummy value in ram[instr*2]
    store_byte(ram, NEXT2_INSTR, DUMMY_VALUE_8);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_ADDR_B, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_8 == pop());
    deallocate();

    // MODE_DATA_32_INDR
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store address 3*instr in ram[instr*2]
    store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);
    // Store a dummy value in ram[instr*4]
    store_dword(ram, NEXT3_INSTR, DUMMY_VALUE_32);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_INDR, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();

    // MODE_DATA_32_INDR_W
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store address 3*instr in ram[instr*2]
    store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);
    // Store a dummy value in ram[instr*4]
    store_word(ram, NEXT3_INSTR, DUMMY_VALUE_16);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_INDR_W, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_16 == pop());
    deallocate();

    // MODE_DATA_32_INDR_B
    allocate();
    // Store address 2*instr in the next instruction (ram[instr])
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    // Store address 3*instr in ram[instr*2]
    store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);
    // Store a dummy value in ram[instr*4]
    store_byte(ram, NEXT3_INSTR, DUMMY_VALUE_8);
    exec(create_instruction(INSTR_PUSH, MODE_DATA_32_INDR_B, EMPTY_BYTE,
                            EMPTY_BYTE));
    CU_ASSERT(DUMMY_VALUE_8 == pop());
    deallocate();

    // MODE_REGISTER
    allocate();
    r[TEST_REGISTER] = DUMMY_VALUE_32;
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();

    // MODE_REGISTER_ADDR
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    // Store the dummy value in that next instruction
    store_dword(ram, NEXT_INSTR, DUMMY_VALUE_32);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_ADDR, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();

    // MODE_REGISTER_ADDR_W
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    // Store the dummy value in that next instruction
    store_word(ram, NEXT_INSTR, DUMMY_VALUE_16);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_ADDR_W, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_16 == pop());
    deallocate();

    // MODE_REGISTER_ADDR_B
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    // Store the dummy value in that next instruction
    store_byte(ram, NEXT_INSTR, DUMMY_VALUE_8);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_ADDR_B, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_8 == pop());
    deallocate();

    // MODE_REGISTER_INDR
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    store_dword(ram, NEXT2_INSTR, DUMMY_VALUE_32);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_INDR, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_32 == pop());
    deallocate();

    // MODE_REGISTER_INDR_W
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    store_word(ram, NEXT2_INSTR, DUMMY_VALUE_16);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_INDR_W, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_16 == pop());
    deallocate();

    // MODE_REGISTER_INDR_B
    allocate();
    // Point register to next instruction
    r[TEST_REGISTER] = NEXT_INSTR;
    store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
    store_byte(ram, NEXT2_INSTR, DUMMY_VALUE_8);
    exec(create_instruction(INSTR_PUSH, MODE_REGISTER_INDR_B, EMPTY_BYTE,
                            TEST_REGISTER));
    CU_ASSERT(DUMMY_VALUE_8 == pop());
    deallocate();
}

// TODO: Add the rest
