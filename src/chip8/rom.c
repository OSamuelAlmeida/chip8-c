#include "chip8/rom.h"

#include <stdlib.h>
#include <stdio.h>

#define ROM_LOAD_ADDRESS 0x200

void chip8_create_rom(chip8_rom *rom, const char *path)
{
    rom->path = path;
}

void chip8_destroy_rom(chip8_rom *rom)
{
    free(rom->data);
}

char *chip8_load_rom(chip8_rom *rom, chip8_ram *ram)
{
    FILE *fp = fopen(rom->path, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", rom->path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    rom->data = calloc(size + 1, sizeof(uint8_t));

    fread(rom->data, 1, size, fp);
    fclose(fp);

    for (size_t i = 0; i < size; i++)
    {
        chip8_set_ram(ram, ROM_LOAD_ADDRESS + i, rom->data[i]);
    }

    rom->data[size] = '\0';

    return rom->data;
}