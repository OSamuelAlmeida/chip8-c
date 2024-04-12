#include "chip8/ram.h"

chip8_ram *chip8_create_ram()
{
    chip8_ram *ram = malloc(sizeof(chip8_ram));
    return ram;
}

void chip8_destroy_ram(chip8_ram *ram)
{
    free(ram);
}

void chip8_set_ram(chip8_ram *ram, uint16_t address, uint8_t value)
{
    ram->data[address] = value;
}
