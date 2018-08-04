/**
 * Project:     MBVM
 * File:        test_utils.h
 * Author:      Matthew Brooks
 * Created:     2018-07-31
 */

#include <stdint.h>

#ifndef TEST_UTILS_H
#define TEST_UTILS_H
void allocate();
void deallocate();
void exec_with_fresh_vm(uint32_t);
#ifndef NULL
#define NULL (void *)0
#endif
#endif
