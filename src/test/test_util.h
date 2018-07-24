/**
 * Project:     MBVM
 * File:        test_util.h
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>

#ifndef TEST_UTIL_H
#define TEST_UTIL_H
uint32_t create_instruction(unsigned char instr, unsigned char mode,
                            unsigned char d1, unsigned char d2);
void load_test_app();
#endif