#ifndef CHIP8_H
#define CHIP8_H

#include "chip8/window.h"
#include "chip8/cpu.h"
#include "chip8/ram.h"
#include "chip8/rom.h"

typedef struct
{
    chip8_window *window;
    chip8_cpu *cpu;
    chip8_ram *ram;
    chip8_rom *rom;
} chip8;

int chip8_init();
chip8 *chip8_create();
void chip8_destroy(chip8 *chip8);

void chip8_run(chip8 *chip8, const char *rom_path);

#endif