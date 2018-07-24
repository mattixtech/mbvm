/**
 * Project:     MBVM
 * File:        instruction_utils.c
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdlib.h>
#include <stdio.h>

#include "instruction_utils.h"
#include "../vm/vm.h"

/**
 * Prints an error messages for unsupported mode and exits.
 */
void unsupported_mode(unsigned char mode)
{
    printf("ERROR: Unuspported mode '0x%X'.\n", mode);
    exit(1);
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
 * 
 * @return 1 if the sr is set, 0 otherwise
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
 * 
 * @param data the char to print
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
uint32_t pop()
{
    return stack[--sp];
}

/**
 * Returns the 4byte data block from the stack at depth.
 * 
 * @param depth the depth
 */
uint32_t peek(uint32_t depth)
{
    // Bounds check to make sure the stack is at least 'depth' high
    if (sp > 0 && (depth + 1 <= sp))
        return stack[sp - (depth + 1)];
    else
        return 0;
}