#ifndef CHIP8_RAM_H
#define CHIP8_RAM_H

#include <stdlib.h>

#define CHIP8_RAM_SIZE 4096

typedef struct
{
    uint8_t data[CHIP8_RAM_SIZE];
} chip8_ram;

void chip8_create_ram(chip8_ram *ram);

void chip8_set_ram(chip8_ram *ram, uint16_t address, uint8_t value);

#endif