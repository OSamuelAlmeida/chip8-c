#ifndef CHIP8_ROM_H
#define CHIP8_ROM_H

#include <stdlib.h>
#include "chip8/ram.h"

typedef struct
{
    const char *path;
    char *data;
} chip8_rom;

chip8_rom *chip8_create_rom(const char *path);
void chip8_destroy_rom(chip8_rom *rom);

char *chip8_load_rom(chip8_rom *rom, chip8_ram *ram);

#endif