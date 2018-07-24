/**
 * Project:     MBVM
 * File:        instruction_utils.h
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>

#ifndef INSTRUCTION_UTILS_H
#define INSTRUCTION_UTILS_H
void alter_sr();
void zb_on();
void zb_off();
int zb_tst();
void push(uint32_t);
uint32_t pop();
uint32_t peek();
void print(char);
void unsupported_mode(unsigned char);
#endif