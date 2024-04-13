#include "chip8/keyboard.h"

int chip8_is_key_pressed(uint8_t key)
{
    return SDL_GetKeyboardState(NULL)[CHIP8_KEYMAP[key]];
}