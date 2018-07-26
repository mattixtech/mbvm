/**
 * Project:     MBVM
 * File:        test_registry.c
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#include <CUnit/Basic.h>

#include "instructions/test_instructions.h"
#include "vm/test_vm.h"

/**
 * The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add the test suite for instructions
    pSuite = CU_add_suite("Instructions Test Suite",
                          init_instructions_test_suite,
                          clean_instructions_test_suite);
    // Add the tests
    CU_add_test(pSuite, "test of instr_exit()", test_instr_exit);

    // Add the test suite for vm
    pSuite = CU_add_suite("VM Test Suite",
                          init_vm_test_suite,
                          clean_vm_test_suite);
    // Add the tests
    CU_add_test(pSuite, "test of allocate_vm()", test_allocate_vm);
    CU_add_test(pSuite, "test of deallocate_vm()", test_deallocate_vm);
    CU_add_test(pSuite, "test of copy_memory()", test_copy_memory);
    CU_add_test(pSuite, "test of exec_program()", test_exec_program);

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}