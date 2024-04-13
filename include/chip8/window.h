#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
#define WINDOW_FPS 60.0
#define CHIP8_DISPLAY_WIDTH 64
#define CHIP8_DISPLAY_HEIGHT 32

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    int running;
    int draw;
    uint32_t pixels[CHIP8_DISPLAY_WIDTH * CHIP8_DISPLAY_HEIGHT];
} chip8_window;

typedef void (*chip8_window_loop_func)(chip8_window *window, void *data);

void chip8_create_window(chip8_window *window);
void chip8_destroy_window(chip8_window *window);

void chip8_loop_window(chip8_window *window, chip8_window_loop_func func, void *data);
void chip8_clear_pixels(chip8_window *window);

void chip8_draw_sprite(chip8_window *window, uint8_t *sprite, uint8_t x, uint8_t y, uint8_t n, uint8_t *vf);

#endif