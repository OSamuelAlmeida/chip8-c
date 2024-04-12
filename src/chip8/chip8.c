#include "chip8/chip8.h"

#include <stdio.h>
#include <SDL2/SDL.h>

int chip8_init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

chip8 *chip8_create()
{
    chip8 *chip8_instance = malloc(sizeof(chip8));
    chip8_instance->window = chip8_create_window();
    chip8_instance->ram = chip8_create_ram();
    chip8_instance->cpu = chip8_create_cpu();

    return chip8_instance;
}

void chip8_destroy(chip8 *chip8_instance)
{
    chip8_destroy_window(chip8_instance->window);
    chip8_destroy_ram(chip8_instance->ram);
    chip8_destroy_rom(chip8_instance->rom);
    chip8_destroy_cpu(chip8_instance->cpu);
    free(chip8_instance);
}

static void chip8_loop(chip8_window *window)
{
    if (!window->running)
    {
        printf("Quitting...\n");
    }
}

void chip8_run(chip8 *chip8_instance, const char *rom_path)
{
    chip8_instance->rom = chip8_create_rom(rom_path);
    chip8_load_rom(chip8_instance->rom, chip8_instance->ram);
    chip8_loop_window(chip8_instance->window, chip8_loop);
}