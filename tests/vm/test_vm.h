/**
 * Project:     MBVM
 * File:        test_vm.h
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#ifndef TEST_VM_H
#define TEST_VM_H
int init_vm_test_suite();
int clean_vm_test_suite();
void test_allocate_vm();
void test_deallocate_vm();
void test_copy_memory();
void test_exec_program();
#endif
