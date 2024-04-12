#ifndef CHIP8_H
#define CHIP8_H

#include "chip8/window.h"

typedef struct
{
    chip8_window *window;
} chip8;

int chip8_init();
chip8 *chip8_create();
void chip8_destroy(chip8 *chip8);

void chip8_run(chip8 *chip8);

#endif