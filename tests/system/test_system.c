/**
 * Project:     MBVM
 * File:        test_system.c
 * Author:      Matthew Brooks
 * Created:     2018-07-27
 */

#include <CUnit/Basic.h>

#include "test_system.h"
#include "../test_utils.h"
#include "../../src/system/system.h"
#include "../../src/vm/vm.h"

/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_system_test_suite()
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_system_test_suite()
{
    return 0;
}

/**
 * Tests 'store_dword()' and 'get_dword()'.
 */
void test_store_get_dword()
{
    allocate();
    uint32_t dummy_value = 0xFF00FF00;
    store_dword(ram, DUMMY_OFFSET, dummy_value);
    CU_ASSERT(dummy_value == get_dword(ram, DUMMY_OFFSET));
    deallocate();
}

/**
 * Tests 'store_word()' and 'get_word()'.
 */
void test_store_get_word()
{
    allocate();
    uint16_t dummy_value = 0xFF00;
    store_word(ram, DUMMY_OFFSET, dummy_value);
    CU_ASSERT(dummy_value == get_word(ram, DUMMY_OFFSET));
    deallocate();
}

/**
 * Tests 'store_byte()' and 'get_byte()'.
 */
void test_store_get_byte()
{
    allocate();
    uint8_t dummy_value = 0xAB;
    store_byte(ram, DUMMY_OFFSET, dummy_value);
    CU_ASSERT(dummy_value == get_byte(ram, DUMMY_OFFSET));
    deallocate();
}

/**
 * Tests 'incr_pc()'.
 */
void test_incr_pc()
{
    allocate();
    incr_pc();
    CU_ASSERT(INSTRUCTION_SIZE == pc);
    deallocate();
}
