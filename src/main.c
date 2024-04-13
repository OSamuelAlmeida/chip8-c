#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "chip8/chip8.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <rom_path>\n", argv[0]);
        return -1;
    }

    if (chip8_init() < 0)
    {
        fprintf(stderr, "Chip-8 failed to initialize!");
        return -1;
    }

    chip8_t chip8;
    chip8_create(&chip8);
    chip8_run(&chip8, argv[1]);
    chip8_destroy(&chip8);

    return 0;
}