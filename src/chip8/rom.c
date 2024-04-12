#include "chip8/rom.h"

#include <stdlib.h>
#include <stdio.h>

#define ROM_LOAD_ADDRESS 0x200

chip8_rom *chip8_create_rom(const char *path)
{
    chip8_rom *rom = malloc(sizeof(chip8_rom));
    rom->path = path;
    return rom;
}

void chip8_destroy_rom(chip8_rom *rom)
{
    free(rom->data);
    free(rom);
}

char *chip8_load_rom(chip8_rom *rom, chip8_ram *ram)
{
    free(rom->data);

    FILE *fp = fopen(rom->path, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", rom->path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    rom->data = malloc(size + 1);

    fread(rom->data, 1, size, fp);
    fclose(fp);

    for (size_t i = 0; i < size; i++)
    {
        chip8_set_ram(ram, ROM_LOAD_ADDRESS + i, rom->data[i]);
    }

    rom->data[size] = '\0';

    return rom->data;
}