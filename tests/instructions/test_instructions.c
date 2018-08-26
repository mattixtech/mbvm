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
static const uint32_t IMMEDIATE = 0;
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
 * A utility function to avoid duplication when testing push() implementations.
 *
 * @param pop_value TODO
 * @param push_mode TODO
 * @param storage_location TODO
 * @param source_location TODO
 */
void
push_test_util(uint32_t pop_value, uint8_t push_mode, uint32_t storage_location,
               int source_location)
{
    allocate();

    if (storage_location != IMMEDIATE)
    {
        if (storage_location == NEXT2_INSTR)
            store_dword(ram, NEXT_INSTR, NEXT2_INSTR);

        if (source_location == SOURCE_IMMEDIATE &&
            storage_location == NEXT3_INSTR)
        {
            store_dword(ram, NEXT_INSTR, NEXT2_INSTR);
            store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);
        }
        else if (source_location == SOURCE_REGISTER)
            r[TEST_REGISTER] = NEXT_INSTR;
    }

    switch (pop_value)
    {
        case DUMMY_VALUE_8:
            if (source_location == SOURCE_IMMEDIATE)
            {
                store_byte(ram, storage_location, DUMMY_VALUE_8);
                exec(create_instruction(INSTR_PUSH, push_mode, EMPTY_BYTE,
                                        DUMMY_VALUE_8));
            }
            else if (source_location == SOURCE_REGISTER)
            {
                if (storage_location == IMMEDIATE)
                    r[TEST_REGISTER] = DUMMY_VALUE_8;
                else
                    store_byte(ram, storage_location, DUMMY_VALUE_8);
            }
            break;
        case DUMMY_VALUE_16:
            if (source_location == SOURCE_IMMEDIATE)
            {
                store_word(ram, storage_location, DUMMY_VALUE_16);
                exec(create_instruction(INSTR_PUSH, push_mode, DUMMY_VALUE_8,
                                        DUMMY_VALUE_8));
            }
            else if (source_location == SOURCE_REGISTER)
            {
                if (storage_location == IMMEDIATE)
                    r[TEST_REGISTER] = DUMMY_VALUE_16;
                else
                    store_word(ram, storage_location, DUMMY_VALUE_16);
            }
            break;
        case DUMMY_VALUE_32:
            if (source_location == SOURCE_IMMEDIATE)
            {
                store_dword(ram, storage_location, DUMMY_VALUE_32);
                exec(create_instruction(INSTR_PUSH, push_mode, EMPTY_BYTE,
                                        EMPTY_BYTE));
            }
            else if (source_location == SOURCE_REGISTER)
            {
                if (storage_location == IMMEDIATE)
                    r[TEST_REGISTER] = DUMMY_VALUE_32;
                else
                    store_dword(ram, storage_location, DUMMY_VALUE_32);
            }
            break;
        default:
        CU_FAIL("Invalid pop_value");
    }

    if (source_location == SOURCE_REGISTER)
        exec(create_instruction(INSTR_PUSH, push_mode, EMPTY_BYTE,
                                TEST_REGISTER));

    CU_ASSERT(pop_value == pop());
    deallocate();
}

/**
 * A utility function to avoid duplication when testing pop() implementations.
 *
 * @param push_value TODO
 * @param pop_mode TODO
 * @param storage_location TODO
 * @param source_location TODO
 */
void
pop_test_util(uint32_t push_value, uint8_t pop_mode, uint32_t storage_location,
              int source_location)
{
    allocate();
    push(push_value);

    if (source_location == SOURCE_IMMEDIATE)
    {
        store_dword(ram, NEXT_INSTR, NEXT2_INSTR);

        if (storage_location == NEXT3_INSTR)
            store_dword(ram, NEXT2_INSTR, NEXT3_INSTR);

        exec(create_instruction(INSTR_POP, pop_mode, EMPTY_BYTE,
                                EMPTY_BYTE));
    }
    else
    {
        //  We can point the register to next instruction by default
        r[TEST_REGISTER] = NEXT_INSTR;

        if (storage_location == NEXT2_INSTR)
            store_dword(ram, NEXT_INSTR, NEXT2_INSTR);

        exec(create_instruction(INSTR_POP, pop_mode, EMPTY_BYTE,
                                TEST_REGISTER));
    }

    if (storage_location == REGISTER_LOCATION)
    {
        CU_ASSERT(push_value == r[TEST_REGISTER]);
    }
    else
    {
        switch (push_value)
        {
            case DUMMY_VALUE_32:
            CU_ASSERT(push_value == get_dword(ram, storage_location));
                break;
            case DUMMY_VALUE_16:
            CU_ASSERT(push_value == get_word(ram, storage_location));
                break;
            case DUMMY_VALUE_8:
            CU_ASSERT(push_value == get_byte(ram, storage_location));
                break;
            default:
            CU_FAIL("Invalid push_value");
        }
    }

    deallocate();
}

/**
 * Tests 'isntr_push()'.
 */
void test_instr_push()
{
    push_test_util(DUMMY_VALUE_8, MODE_IMMEDIATE_B, IMMEDIATE,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_16, MODE_IMMEDIATE_W, IMMEDIATE,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_32, MODE_DATA_32, NEXT_INSTR, SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_32, MODE_DATA_32_ADDR, NEXT2_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_16, MODE_DATA_32_ADDR_W, NEXT2_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_8, MODE_DATA_32_ADDR_B, NEXT2_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_32, MODE_DATA_32_INDR, NEXT3_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_16, MODE_DATA_32_INDR_W, NEXT3_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_8, MODE_DATA_32_INDR_B, NEXT3_INSTR,
                   SOURCE_IMMEDIATE);
    push_test_util(DUMMY_VALUE_32, MODE_REGISTER, IMMEDIATE,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_32, MODE_REGISTER_ADDR, NEXT_INSTR,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_16, MODE_REGISTER_ADDR_W, NEXT_INSTR,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_8, MODE_REGISTER_ADDR_B, NEXT_INSTR,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_32, MODE_REGISTER_INDR, NEXT2_INSTR,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_16, MODE_REGISTER_INDR_W, NEXT2_INSTR,
                   SOURCE_REGISTER);
    push_test_util(DUMMY_VALUE_8, MODE_REGISTER_INDR_B, NEXT2_INSTR,
                   SOURCE_REGISTER);
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
