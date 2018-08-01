/**
 * Project:     MBVM
 * File:        test_system.c
 * Author:      Matthew Brooks
 * Created:     2018-07-27
 */

#include <CUnit/Basic.h>

#ifndef TEST_SYSTEM_H
#define TEST_SYSTEM_H
#define DUMMY_OFFSET 10
int init_system_test_suite();
int clean_system_test_suite();
void test_store_get_dword();
void test_store_get_word();
void test_store_get_byte();
void test_incr_pc();
#endif