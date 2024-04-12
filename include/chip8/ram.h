#ifndef CHIP8_RAM_H
#define CHIP8_RAM_H

#include <stdlib.h>

typedef struct
{
    uint8_t data[4096];
} chip8_ram;

chip8_ram *chip8_create_ram();
void chip8_destroy_ram(chip8_ram *ram);

void chip8_set_ram(chip8_ram *ram, uint16_t address, uint8_t value);

#endif