/**
 * Project:     MBVM
 * File:        util.h
 * Author:      Matthew Brooks
 * Created:     2018-07-26
 */

#include <stdint.h>

#ifndef UTIL_H
#define UTIL_H
uint32_t create_instruction(unsigned char instr, unsigned char mode,
                            unsigned char d1, unsigned char d2);
void load_test_app();
#endif