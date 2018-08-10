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

// The instruction locations for the successive instructions after our push
// to help with addressing and indirection
static const uint32_t NEXT_INSTR = INSTRUCTION_SIZE;
static const uint32_t NEXT2_INSTR = INSTRUCTION_SIZE * 2;
static const uint32_t NEXT3_INSTR = INSTRUCTION_SIZE * 3;
static const int SOURCE_IMMEDIATE = 1;
static const int SOURCE_REGISTER = 2;
static const uint32_t REGISTER_LOCATION = 0x0A000000;

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
 * Tests 'instr_noop'
 */
void test_instr_noop()
{
    allocate();
    exec(create_instruction(INSTR_NOOP, EMPTY_BYTE, EMPTY_BYTE, EMPTY_BYTE));
    // TODO: Not sure what to test here, just checking that the PC
    // was incremented for now
    CU_ASSERT(INSTRUCTION_SIZE == pc);
    deallocate();
}

/**
 * Tests 'isntr_push()'.
 */
void test_instr_push()
{
    // TODO: Create a util function similiar to pop_test_util()

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

/**
 * A utility function to avoid duplication when testing pop() implementations.
 */
void pop_test_util(uint32_t push_value, uint8_t pop_mode, uint32_t get_location,
                   int source)
{
    allocate();
    push(push_value);

    if (source == SOURCE_IMMEDIATE)
    {
        store_dword(ram, NEXT_INSTR, NEXT2_INSTR);

        if (get_location == NEXT3_INSTR)
            store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);

        exec(create_instruction(INSTR_POP, pop_mode, EMPTY_BYTE,
                                EMPTY_BYTE));
    }
    else
    {
        //  We can point the register to next instruction by default
        r[TEST_REGISTER] = NEXT_INSTR;

        if (get_location == NEXT2_INSTR)
            store_dword(ram, NEXT_INSTR, NEXT2_INSTR);

        exec(create_instruction(INSTR_POP, pop_mode, EMPTY_BYTE,
                                TEST_REGISTER));
    }

    if (get_location == REGISTER_LOCATION)
    {
        CU_ASSERT(push_value == r[TEST_REGISTER]);
    }
    else
    {
        switch (push_value)
        {
            case DUMMY_VALUE_32:
            CU_ASSERT(push_value == get_dword(ram, get_location));
                break;
            case DUMMY_VALUE_16:
            CU_ASSERT(push_value == get_word(ram, get_location));
                break;
            case DUMMY_VALUE_8:
            CU_ASSERT(push_value == get_byte(ram, get_location));
                break;
            default:
            CU_FAIL("Invalid push_value");
        }
    }

    deallocate();
}

/**
 * Tests 'isntr_pop()'.
 */
void test_instr_pop()
{
    pop_test_util(DUMMY_VALUE_32, MODE_DATA_32_ADDR, NEXT2_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_16, MODE_DATA_32_ADDR_W, NEXT2_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_8, MODE_DATA_32_ADDR_B, NEXT2_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_32, MODE_DATA_32_INDR, NEXT3_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_16, MODE_DATA_32_INDR_W, NEXT3_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_8, MODE_DATA_32_INDR_B, NEXT3_INSTR,
                  SOURCE_IMMEDIATE);
    pop_test_util(DUMMY_VALUE_32, MODE_REGISTER, REGISTER_LOCATION,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_32, MODE_REGISTER_ADDR, NEXT_INSTR,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_16, MODE_REGISTER_ADDR_W, NEXT_INSTR,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_8, MODE_REGISTER_ADDR_B, NEXT_INSTR,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_32, MODE_REGISTER_INDR, NEXT2_INSTR,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_16, MODE_REGISTER_INDR_W, NEXT2_INSTR,
                  SOURCE_REGISTER);
    pop_test_util(DUMMY_VALUE_8, MODE_REGISTER_INDR_B, NEXT2_INSTR,
                  SOURCE_REGISTER);
}

// TODO: Add the rest
