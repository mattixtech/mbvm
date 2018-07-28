/**
 * Project:     MBVM
 * File:        vm.h
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include <stdint.h>

#ifndef VM_H
#define VM_H

// RAM 10MB
#define DEFAULT_RAM_SIZE (1024 * 1024 * 10)

// Flash 100MB
#define DEFAULT_FLASH_SIZE (1024 * 1024 * 10)

// Stack 64KB
#define DEFAULT_STACK_SIZE (64 * 1024)

#define INSTRUCTION_SIZE 4
#define NUM_REGISTERS 10
#define REGISTER_SIZE 4

#define DATA_REGISTER 8
#define PRINT_REGISTER 9

unsigned int configured_ram_size;
unsigned int configured_flash_size;
unsigned int configured_num_registers;
unsigned int configured_stack_size;

uint8_t *ram;
uint32_t *flash;
uint32_t *r;
uint32_t *stack;
uint32_t prev_instr;

uint32_t sp;
uint32_t pc;

/**
 * SR schematic:
 * 7 6  5 4 3 2 1 0
 * bit 0: zero bit, will be on if the previous instruction yielded a zero result
 * bit 1:
 */
uint8_t sr;

uint32_t *dr;
uint32_t *pr;
uint32_t flash_allocated;
void allocate_vm(unsigned int, unsigned int, unsigned int, unsigned int,
                 unsigned int);
void deallocate_vm();
int copy_memory(uint8_t *, uint8_t *, int);
void exec_program();
#endif
