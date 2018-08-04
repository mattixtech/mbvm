/**
 * Project:     MBVM
 * File:        test_instructions.h
 * Author:      Matthew Brooks
 * Created:     2018-07-25
 */

#ifndef TEST_INSTRUCTIONS_H
#define TEST_INSTRUCTIONS_H
#define DUMMY_VALUE_8 0xAB
#define DUMMY_VALUE_16 0xABAB
#define DUMMY_VALUE_32 0xABABABAB
#define TEST_REGISTER 5
int init_instructions_test_suite();
int clean_instructions_test_suite();
void test_instr_exit();
void test_instr_push();
#endif