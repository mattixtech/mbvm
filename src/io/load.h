/**
 * Project:     MBVM
 * File:        load.h
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>

#ifndef LOAD_H
#define LOAD_H
void load_program(uint32_t program[], int size, uint32_t *destination);
#endif