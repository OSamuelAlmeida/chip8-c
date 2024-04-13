#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdlib.h>

#include "chip8/window.h"
#include "chip8/ram.h"

typedef struct
{
    uint8_t registers[16];
    uint16_t I;
    uint16_t pc;
    uint16_t sp;
    uint8_t stack[16];
    uint8_t delay_timer;
    uint8_t sound_timer;
} chip8_cpu;

void chip8_create_cpu(chip8_cpu *cpu);
void chip8_execute_opcode(chip8_cpu *cpu, uint16_t opcode, chip8_window *window, chip8_ram *ram);

#endif