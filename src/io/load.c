/**
 * Project:     MBVM
 * File:        load.c
 * Author:      Matthew Brooks
 * Created:     2018-07-23
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <memory.h>

#include "../util/util.h"
#include "../vm/vm.h"

/**
 * Load the given program into the given memory destination.
 *
 * @param program the program
 * @param size the size of the program in 4 byte words
 * @param destination the memory destination
 */
void load_program(uint32_t program[], int size, uint32_t *destination)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = program[i];
        flash_allocated++;
    }
}

/**
 * Load the file into program array that can be copied to flash.
 *
 * @param file_name the file name to load
 */
int load_file(const char *file_name)
{
    // TODO: This is all first pass, seems to be working but can probably be
    // cleaned up
    int fd;
    uint8_t buf;

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
        return 1;

    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if ((fd = open(file_name, O_RDONLY)) < 0)
        return 1;

    uint8_t file_bytes[sz];
    memset(file_bytes, 0, sizeof(file_bytes));

    int i = 0;
    while (read(fd, &buf, 1) > 0)
    {
        file_bytes[i++] = buf;
    }

    uint32_t program[(sz + INSTRUCTION_SIZE - 1) / INSTRUCTION_SIZE];
    memset(program, 0, sizeof(program));
    int count = 0;

    for (int j = 0; j < sz; j += 4)
    {
        // Only part of the flash memory is instructions. What follows is
        // arbitrary data and does not necessarily fit in a 4 byte instruction.
        // We will put it in one anyway and just 0-out the excess.
        uint8_t instr_type = file_bytes[j];
        uint8_t instr_mode = (j + 1) < sz ? file_bytes[j + 1] : (uint8_t) 0;
        uint8_t instr_d1 = (j + 2) < sz ? file_bytes[j + 2] : (uint8_t) 0;
        uint8_t instr_d2 = (j + 3) < sz ? file_bytes[j + 3] : (uint8_t) 0;
        program[count++] = create_instruction(instr_type, instr_mode,
                                              instr_d1, instr_d2);
    }

    load_program(program, sizeof(program) / sizeof(program[0]), flash);

    return 0;
}