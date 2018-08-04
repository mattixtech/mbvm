/**
 * Project:     MBVM
 * File:        test_registry.c
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#include <CUnit/Basic.h>

#include "instructions/test_instructions.h"
#include "system/test_system.h"
#include "vm/test_vm.h"

/**
 * Adds the 'instructions' test suite to the test registry.
 *
 * @param p_suite the test suite pointer
 */
void add_instructions_tests(CU_pSuite p_suite)
{
    // Add the test suite for instructions
    p_suite = CU_add_suite("Instructions Test Suite",
                           init_instructions_test_suite,
                           clean_instructions_test_suite);
    // Add the tests
    CU_add_test(p_suite, "test of instr_exit()", test_instr_exit);
    CU_add_test(p_suite, "test of instr_push()", test_instr_push);
    // TODO: Add the rest
}

/**
 * Adds the 'vm' test suite to the test registry.
 *
 * @param p_suite the test suite pointer
 */
void add_vm_tests(CU_pSuite p_suite)
{
    // Add the test suite for vm
    p_suite = CU_add_suite("VM Test Suite",
                           init_vm_test_suite,
                           clean_vm_test_suite);
    // Add the tests
    CU_add_test(p_suite, "test of allocate_vm()", test_allocate_vm);
    CU_add_test(p_suite, "test of deallocate_vm()", test_deallocate_vm);
    CU_add_test(p_suite, "test of copy_memory()", test_copy_memory);
    CU_add_test(p_suite, "test of exec_program()", test_exec_program);
}

/**
 * Adds the 'system' test suite to the test registry.
 *
 * @param p_suite the test suite pointer
 */
void add_system_tests(CU_pSuite p_suite)
{
    // Add the test suite for system
    p_suite = CU_add_suite("System Test Suite",
                           init_system_test_suite,
                           clean_system_test_suite);

    // Add the tests
    CU_add_test(p_suite, "test of store_dword() and get_dword()",
                test_store_get_dword);
    CU_add_test(p_suite, "test of store_word() and get_word()",
                test_store_get_word);
    CU_add_test(p_suite, "test of store_byte() and get_byte()",
                test_store_get_byte);
    CU_add_test(p_suite, "test of test_incr_pc()", test_incr_pc);
}

/**
 * The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    CU_pSuite p_suite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    add_instructions_tests(p_suite);
    add_vm_tests(p_suite);
    add_system_tests(p_suite);

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}