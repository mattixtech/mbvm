/**
 * Project:     MBVM
 * File:        system.h
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdint.h>
#ifndef SYSTEM_H
#define SYSTEM_H

uint8_t debugging;
void exec(uint32_t);
void disp_image(uint32_t*, int);
void dump_state();
void store_dword(uint8_t*, uint32_t, uint32_t);
void store_word(uint8_t*, uint32_t, uint16_t);
void store_byte(uint8_t*, uint32_t, uint8_t);
uint32_t get_dword(uint8_t*, uint32_t);
uint16_t get_word(uint8_t*, uint32_t);
uint8_t get_byte(uint8_t*, uint32_t);
uint32_t incr_pc();
#endif
