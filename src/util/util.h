/**
 * Project:     MBVM
 * File:        util.h
 * Author:      Matthew Brooks
 * Created:     2018-07-26
 */

#include <stdint.h>

#ifndef UTIL_H
#define UTIL_H
uint32_t create_instruction(uint8_t instr, uint8_t mode, uint8_t d1,
                            uint8_t d2);
void load_test_app();
#endif