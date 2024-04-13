#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H

#include <SDL2/SDL.h>

extern const SDL_Scancode CHIP8_KEYMAP[16];

int chip8_is_key_pressed(uint8_t key);

#endif