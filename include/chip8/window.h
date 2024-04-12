#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int running;
} chip8_window;

typedef void (*chip8_window_loop_func)(chip8_window *window);

chip8_window *chip8_create_window();

void chip8_window_loop(chip8_window *window, chip8_window_loop_func func);

void chip8_destroy_window(chip8_window *window);

#endif