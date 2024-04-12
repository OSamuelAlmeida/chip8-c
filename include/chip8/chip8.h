#ifndef CHIP8_H
#define CHIP8_H

#include "chip8/window.h"
#include "chip8/cpu.h"
#include "chip8/ram.h"
#include "chip8/rom.h"

typedef struct
{
    chip8_window window;
    chip8_cpu cpu;
    chip8_ram ram;
    chip8_rom rom;
} chip8_t;

int chip8_init();
void chip8_create(chip8_t *chip8);
void chip8_destroy(chip8_t *chip8);

void chip8_run(chip8_t *chip8, const char *rom_path);

#endif