#include "chip8/window.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

chip8_window *chip8_create_window()
{
    chip8_window *window = malloc(sizeof(chip8_window));

    window->window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    window->renderer = SDL_CreateRenderer(window->window, -1, 0);
    window->running = 0;

    return window;
}

static void chip8_handle_event(chip8_window *window)
{
    SDL_PollEvent(&window->event);
    if (window->event.type == SDL_QUIT)
    {
        window->running = 0;
    }
}

static void chip8_clear_window(chip8_window *window)
{
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
}

void chip8_window_loop(chip8_window *window, chip8_window_loop_func func)
{
    window->running = 1;

    while (window->running)
    {
        chip8_handle_event(window);
        func(window);
        chip8_clear_window(window);
    }
}

void chip8_destroy_window(chip8_window *window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}