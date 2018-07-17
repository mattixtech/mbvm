/**
 * Project:     MBVM
 * File:        instructions.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include "instructions.h"
#include "vm.h"
#include "system.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Decodes and executes instruction.
 */
void dec_instr(uint32_t instr)
{
	unsigned char op    = (char) ((instr & 0xFF000000) >> 24); 	// op is the most significant byte of the instruction
	unsigned char mode  = (char) ((instr & 0x00FF0000) >> 16); 	// mode is the second most significant byte of the instruction
	unsigned char d1    = (char) ((instr & 0x0000FF00) >> 8); 	// d1 is the second least significant byte of the instruction
	unsigned char d2    = (char) (instr & 0x000000FF); 			// d2 is the least significant byte of the instruction
	uint16_t data = (instr & 0x0000FFFF); 						// data is the least significant 2 bytes of the instruction
	uint32_t mem_addr; 											// memory pointer
	uint32_t mem_data;											// memory content

	// Regular Instructions...

	// Switch based on the operation
	switch (op)
	{
	case INSTR_EXIT:
		if (debugging)
			printf("exit instruction reached, terminating...\n");

		exit(0);
		break;

	case INSTR_LOAD:
		switch (mode)
		{
		case MODE_IMMEDIATE_B:
			*dr = d2;
			break;
		case MODE_IMMEDIATE_W:
			*dr = data;
			break;
		case MODE_DATA_32:
			*dr = get_dword(ram, incr_pc());
			break;
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			*dr = get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			*dr = get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			*dr = get_byte(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER:
			*dr = r[d2];
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			*dr = get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			*dr = get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			*dr = get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr = get_byte(ram, mem_addr);
			break;
		default:
			unsupported_mode(mode);
		}

		alter_sr();
		break;

	case INSTR_STORE:
		switch (mode)
		{
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			store_dword(ram, mem_addr, *dr);
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			store_word(ram, mem_addr, *dr);
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			store_byte(ram, mem_addr, *dr);
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, *dr);
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, *dr);
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER:
			r[d2] = *dr;
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			store_dword(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			store_word(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			store_byte(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, *dr);
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, *dr);
			break;
		default:
			unsupported_mode(mode);
		}

		alter_sr();
		break;

	case INSTR_ADD:
		switch (mode)
		{
		case MODE_IMMEDIATE_B:
			*dr += d2;
			break;
		case MODE_IMMEDIATE_W:
			*dr += data;
			break;
		case MODE_DATA_32:
			*dr += get_dword(ram, incr_pc());
			break;
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			*dr += get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			*dr += get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			*dr += get_byte(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER:
			*dr += r[d2];
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			*dr += get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			*dr += get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			*dr += get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr += get_byte(ram, mem_addr);
			break;
		default:
			unsupported_mode(mode);
		}

		alter_sr();
		break;

	case INSTR_SUB:
		switch (mode)
		{
		case MODE_IMMEDIATE_B:
			*dr -= d2;
			break;
		case MODE_IMMEDIATE_W:
			*dr -= data;
			break;
		case MODE_DATA_32:
			*dr -= get_dword(ram, incr_pc());
			break;
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			*dr -= get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			*dr -= get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			*dr -= get_byte(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_dword(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_word(ram, mem_addr);
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER:
			*dr -= r[d2];
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			*dr -= get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			*dr -= get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			*dr -= get_byte(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_dword(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_word(ram, mem_addr);
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			*dr -= get_byte(ram, mem_addr);
			break;
		default:
			unsupported_mode(mode);
		}

		alter_sr();
		break;

	case INSTR_PUSH:
		switch (mode)
		{
		case MODE_IMMEDIATE_B:
			push(d2);
			break;
		case MODE_IMMEDIATE_W:
			push(data);
			break;
		case MODE_DATA_32:
			push(get_dword(ram, incr_pc()));
			break;
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			push(get_dword(ram, mem_addr));
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			push(get_word(ram, mem_addr));
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			push(get_byte(ram, mem_addr));
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			push(get_dword(ram, mem_addr));
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			push(get_word(ram, mem_addr));
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			push(get_byte(ram, mem_addr));
			break;
		case MODE_REGISTER:
			push(r[d2]);
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			push(get_dword(ram, mem_addr));
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			push(get_word(ram, mem_addr));
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			push(get_byte(ram, mem_addr));
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			push(get_dword(ram, mem_addr));
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			push(get_word(ram, mem_addr));
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			push(get_byte(ram, mem_addr));
			break;
		default:
			unsupported_mode(mode);
		}

		break;

	case INSTR_POP:
		switch (mode)
		{
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			store_dword(ram, mem_addr, pop());
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			store_word(ram, mem_addr, pop());
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			store_byte(ram, mem_addr, pop());
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, pop());
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, pop());
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, pop());
			break;
		case MODE_REGISTER:
			r[d2] = pop();
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			store_dword(ram, mem_addr, pop());
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			store_word(ram, mem_addr, pop());
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			store_byte(ram, mem_addr, pop());
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, pop());
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, pop());
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, pop());
			break;
		default:
			unsupported_mode(mode);
		}

		break;

	case INSTR_PEEK:
		switch (mode)
		{
		case MODE_DATA_32_ADDR:
			mem_addr = get_dword(ram, incr_pc());
			store_dword(ram, mem_addr, peek(0));
			break;
		case MODE_DATA_32_ADDR_W:
			mem_addr = get_dword(ram, incr_pc());
			store_word(ram, mem_addr, peek(0));
			break;
		case MODE_DATA_32_ADDR_B:
			mem_addr = get_dword(ram, incr_pc());
			store_byte(ram, mem_addr, peek(0));
			break;
		case MODE_DATA_32_INDR:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, peek(0));
			break;
		case MODE_DATA_32_INDR_W:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, peek(0));
			break;
		case MODE_DATA_32_INDR_B:
			mem_addr = get_dword(ram, incr_pc());
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER:
			r[d2] = peek(0);
			break;
		case MODE_REGISTER_ADDR:
			mem_addr = r[d2];
			store_dword(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER_ADDR_W:
			mem_addr = r[d2];
			store_word(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER_ADDR_B:
			mem_addr = r[d2];
			store_byte(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER_INDR:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_dword(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER_INDR_W:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_word(ram, mem_addr, peek(0));
			break;
		case MODE_REGISTER_INDR_B:
			mem_addr = r[d2];
			mem_addr = get_dword(ram, mem_addr);
			store_byte(ram, mem_addr, peek(0));
			break;
		default:
			unsupported_mode(mode);
		}

		break;

	case INSTR_JMP:
		// TODO: add the other jump modes
		mem_addr = get_dword(ram, incr_pc());

		if ((mem_addr % INSTRUCTION_SIZE) == 0)
		{
			switch (mode)
			{
			case MODE_DEFAULT:
				pc = mem_addr - 4; 		// Point the pc to the jmp location
				break;
			case JUMP_MODE_JMPEQ:
				if (zb_tst())
					pc = mem_addr - 4; 	// Point the pc to the jmp location
				break;
			case JUMP_MODE_JMPNEQ:
				if ( ! zb_tst())
					pc = mem_addr - 4;	// Point the pc to the jmp location
				break;
			default:
				unsupported_mode(mode);
			}
		}

		break;

	case INSTR_FCAL:
		function_call();
		break;

	case INSTR_FRET:
		function_return();
		break;

	// Advanced Instructions...

	// Print has two modes
	// 1. print the char stored in the pr
	// 2. print the 0 terminated string located in the memory pointed to by pr
	case ADV_INSTR_PRINT:
		switch (mode)
		{
		case MODE_DEFAULT:
			print((char) *pr);
			break;
		case MODE_EXTRA:
			mem_addr = *pr;
			char p_byte = '\00';
			while ((p_byte = get_byte(ram, mem_addr++)))
				print(p_byte);

			break;
		default:
			unsupported_mode(mode);
		}

		break;

	case ADV_INSTR_SCAN:
		switch (mode)
		{
		case MODE_DEFAULT:
			scanf("%c", (char *)pr); // Scan the character literal into pr
			break;
		case MODE_EXTRA:
			mem_addr = *pr;
			fgets(ram + mem_addr, *dr, stdin);
			break;
		default:
			unsupported_mode(mode);
		}
		break;
	}
}

/**
 *
 */
void unsupported_mode(unsigned char mode)
{
	printf("ERROR: Unuspported mode.\n");
	exit(1);
}

/**
 * Saves the current program state on the stack.
 */
void function_call()
{
	// Push registers onto stack
	for (int i = 0; i < NUM_REGISTERS; i++)
		push(r[i]);

	push(pc);
	push(sr);
}

/**
 * Restores the program state from the stack.
 */
void function_return()
{
	sr = pop();
	pc = pop();

	// Restore registers from stack
	for (int i = NUM_REGISTERS - 1; i >= 0; i--)
		r[i] = pop();
}

/**
 * Alters the status register based on the outcome of an executed instruction.
 */
void alter_sr()
{
	if (*dr == 0)
		zb_on();
	else
		zb_off();
}

/**
 * Turns on the zero bit of the status register.
 */
void zb_on()
{
	sr |= 0x01;
}

/*
 * Turns off the zero bit of the status register.
 */
void zb_off()
{
	sr &= ~0x01;
}

/*
 * Tests the zero bit of the status register.
 */
int zb_tst()
{
	uint8_t tst = sr & 0x01;

	if (tst == 0x01)
		return 1;

	return 0;
}

/**
 * Prints the raw char data.
 */
void print(char data)
{
	printf("%c", data);
}

/**
 * Pushes the 4byte data block onto the stack and realigns the sp.
 */
void push(uint32_t data)
{
	stack[sp++] = data;
}

/**
 * Pops the 4byte data block off of the stack and realigns the sp.
 */
uint32_t pop() {
	return stack[--sp];
}

/**
 * Returns the 4byte data block from the stack at depth.
 */
uint32_t peek(int depth)
{
	// Bounds check to make sure the stack is at least 'depth' high
	if (sp > 0 && (depth + 1 <= sp))
		return stack[sp - (depth + 1)];
	else
		return 0;
}
