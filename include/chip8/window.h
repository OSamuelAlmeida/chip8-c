#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define CHIP8_DISPLAY_WIDTH 64
#define CHIP8_DISPLAY_HEIGHT 32

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    int running;
    uint32_t *pixels;
} chip8_window;

typedef void (*chip8_window_loop_func)(chip8_window *window);

chip8_window *chip8_create_window();

void chip8_loop_window(chip8_window *window, chip8_window_loop_func func);

void chip8_destroy_window(chip8_window *window);

#endif