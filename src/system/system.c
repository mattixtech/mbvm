/**
 * Project:     MBVM
 * File:        system.c
 * Author:      Matthew Brooks
 * Created:     2011-04-07
 */

#include "system.h"
#include "../vm/vm.h"
#include "../instructions/instruction_exec.h"

#include <stdio.h>
#include <stdint.h>

/**
 * Executes an instruction.
 *
 * @param programCode TODO
 * @return TODO
 */
int exec(uint32_t programCode)
{
    if (0 != process_instr(programCode))
        return 1;
    prev_instr = programCode;
    incr_pc();

    return 0;
}

/**
 * Returns the 4 byte block found in loc @ image_addr.
 *
 * @param loc TODO
 * @param image_addr TODO
 */
uint32_t get_dword(uint8_t *loc, uint32_t image_addr)
{
    uint32_t b0 = loc[image_addr + 0] << 24;
    uint32_t b1 = loc[image_addr + 1] << 16;
    uint32_t b2 = loc[image_addr + 2] << 8;
    uint32_t b3 = loc[image_addr + 3];

    return 0x00000000 | b0 | b1 | b2 | b3;
}

/**
 * Stores a 4 byte value into a memory location.
 */
void store_dword(uint8_t *loc, uint32_t index, uint32_t block)
{
    *(loc + index + 0) = (block & 0xFF000000) >> 24;
    *(loc + index + 1) = (block & 0x00FF0000) >> 16;
    *(loc + index + 2) = (block & 0x0000FF00) >> 8;
    *(loc + index + 3) = (block & 0x000000FF);
}

/**
 * Stores a 2 byte value into a memory location.
 */
void store_word(uint8_t *loc, uint32_t index, uint16_t word)
{
    *(loc + index + 0) = (word & 0xFF00) >> 8;
    *(loc + index + 1) = (word & 0x00FF);
}

/**
 * Stores a byte value into a memory location.
 */
void store_byte(uint8_t *loc, uint32_t index, uint8_t byte)
{
    *(loc + index) = byte;
}

/**
 * Returns the 2 byte word found in loc @ image_addr.
 */
uint16_t get_word(uint8_t *loc, uint32_t image_addr)
{
    uint16_t b0 = loc[image_addr + 0] << 8;
    uint8_t b1 = loc[image_addr + 1];

    return 0x0000 | b0 | b1;
}

/**
 * Returns the byte found in loc @ image_addr.
 */
uint8_t get_byte(uint8_t *loc, uint32_t image_addr)
{
    uint8_t b = loc[image_addr];

    return 0x00 | b;
}

/**
 * Points the pc to the next 4 byte block and returns the incremented pc.
 */
uint32_t incr_pc()
{
    pc += INSTRUCTION_SIZE;

    return pc;
}

/**
 * Get the location of useable RAM which is the starting address of RAM offset
 * by the size of allocated flash.
 */
uint32_t offset_ram_for_flash(uint32_t mem_addr)
{
    return (flash_allocated * INSTRUCTION_SIZE) + mem_addr;
}

/**
 * Displays the contents of flash memory.
 */
void disp_image(uint32_t *image, int blocks)
{
    if (debugging)
    {
        printf("\nFLASH Image:\n");

        for (int i = 0; i < blocks; i++)
        {
            // Take the 4 bytes in image[i] and get a char pointer to them
            unsigned char *chars = (unsigned char *) &image[i];
            printf("0x%X \t" FORMAT_HEX_4_BYTE "\t%c%c%c%c\n",
                   i * INSTRUCTION_SIZE, image[i], chars[3], chars[2], chars[1],
                   chars[0]);
        }
    }
}

/**
 * Dumps the machine's state for debugging purposes.
 */
void dump_state()
{
    if (debugging)
    {
        printf("\ninstr: " FORMAT_HEX_4_BYTE "\n", prev_instr);
        printf("r0: 0x%X, r1: 0x%X, r2: 0x%X, r3: 0x%X, r4: 0x%X, r5: 0x%X,"
               " r6: 0x%X, r7: 0x%X, ",
               r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7]);
        printf("sr: 0x%X, dr: 0x%X, pr: 0x%X\n", sr, *dr, *pr);
        printf("pc: 0x%X, sp: 0x%X, zb: %d\n", pc, sp, sr & 0x01);
        printf("stack:");
        int start = sp - 1;

        for (int i = start; i >= 0; i--)
            printf(" " FORMAT_HEX_4_BYTE, stack[i]);

        printf("\n");

        // This iterates through ALL of the RAM allocated to the VM and for any
        // byte that isn't 0 it prints out the hext value for that byte along
        // with its address relative to the VM
        printf("RAM explorer:\n");
        int printed_contents = 0;

        for (int i = flash_allocated * INSTRUCTION_SIZE;
             i < ((int) configured_ram_size); i++)
        {
            char ram_contents = *(ram + i);

            if (ram_contents != 0)
            {
                if (printed_contents != 0)
                    printf(",");
                printf(FORMAT_HEX_4_BYTE ":" FORMAT_HEX_4_BYTE, i,
                       ram_contents);
                printed_contents = 1;
            }
        }

        printf("\n");
        printf("next instr: " FORMAT_HEX_4_BYTE ", following block: " FORMAT_HEX_4_BYTE "\n\n",
               get_dword(ram, pc), get_dword(ram, pc + 4));
    }
}
