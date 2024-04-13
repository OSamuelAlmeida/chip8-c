#include "chip8/chip8.h"

#include <stdio.h>
#include <SDL2/SDL.h>

#define CHIP8_CPU_CLOCK_SPEED 700 / WINDOW_FPS

int chip8_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

void chip8_create(chip8_t *chip8)
{
    chip8_create_window(&chip8->window);
    chip8_create_ram(&chip8->ram);
    chip8_create_cpu(&chip8->cpu);
}

void chip8_destroy(chip8_t *chip8)
{
    chip8_destroy_window(&chip8->window);
    chip8_destroy_rom(&chip8->rom);
}

static void chip8_loop(chip8_window *window, void *data)
{
    chip8_t *chip8 = (chip8_t *)data;

    if (window->running)
    {
        chip8->cpu.delay_timer = chip8->cpu.delay_timer > 0 ? chip8->cpu.delay_timer - 1 : 0;
        chip8->cpu.sound_timer = chip8->cpu.sound_timer > 0 ? chip8->cpu.sound_timer - 1 : 0;

        for (int i = 0; i < CHIP8_CPU_CLOCK_SPEED; i++)
        {
            uint16_t opcode = (chip8->ram.data[chip8->cpu.pc] << 8) | chip8->ram.data[chip8->cpu.pc + 1];
            chip8_execute_opcode(&chip8->cpu, opcode, window, &chip8->ram);
        }
    }
    else
    {
        printf("Quitting...\n");
    }
}

void chip8_run(chip8_t *chip8, const char *rom_path)
{
    chip8_create_rom(&chip8->rom, rom_path);
    if (chip8_load_rom(&chip8->rom, &chip8->ram) != NULL)
        chip8_loop_window(&chip8->window, chip8_loop, chip8);
}