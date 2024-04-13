#include "chip8/window.h"

#include <string.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
#define WINDOW_FPS 60.0

void chip8_create_window(chip8_window *window)
{
    window->window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    window->renderer = SDL_CreateRenderer(window->window, -1, 0);
    window->texture = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, CHIP8_DISPLAY_WIDTH, CHIP8_DISPLAY_HEIGHT);
    window->running = 0;
    memset(window->pixels, 0, sizeof(window->pixels));
}

static void chip8_handle_events(chip8_window *window)
{
    while (SDL_PollEvent(&window->event))
    {
        if (window->event.type == SDL_QUIT)
        {
            window->running = 0;
        }
    }
}

static void chip8_clear_window(chip8_window *window)
{
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
}

void chip8_loop_window(chip8_window *window, chip8_window_loop_func func, void *data)
{
    uint32_t ticks = SDL_GetTicks();

    window->running = 1;

    while (window->running)
    {
        if (SDL_GetTicks() - ticks >= 1000 / WINDOW_FPS)
        {
            chip8_handle_events(window);
            func(window, data);

            SDL_UpdateTexture(window->texture, NULL, window->pixels, CHIP8_DISPLAY_WIDTH * sizeof(uint32_t));
            SDL_RenderCopy(window->renderer, window->texture, NULL, NULL);
            SDL_RenderPresent(window->renderer);

            chip8_clear_window(window);

            ticks = SDL_GetTicks();
        }
    }
}

void chip8_destroy_window(chip8_window *window)
{
    SDL_DestroyTexture(window->texture);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
}