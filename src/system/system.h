/**
 * Project:     MBVM
 * File:        system.h
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdint.h>

#ifndef SYSTEM_H
#define SYSTEM_H
#define EMPTY_BYTE 0x00
#define FORMAT_HEX_4_BYTE "0x%08X"
uint8_t debugging;
int exec(uint32_t);
void disp_image(uint32_t *, int);
void dump_state();
void store_dword(uint8_t *, uint32_t, uint32_t);
void store_word(uint8_t *, uint32_t, uint16_t);
void store_byte(uint8_t *, uint32_t, uint8_t);
uint32_t get_dword(uint8_t *, uint32_t);
uint16_t get_word(uint8_t *, uint32_t);
uint8_t get_byte(uint8_t *, uint32_t);
// TODO: Unused
uint32_t offset_ram_for_flash(uint32_t);
uint32_t incr_pc();
#endif
