#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdlib.h>

typedef struct
{
    uint16_t opcode;
    uint8_t registers[16];
    uint16_t I;
    uint16_t pc;
    uint16_t sp;
    uint8_t stack[16];
    uint8_t delay_timer;
    uint8_t sound_timer;
} chip8_cpu;

void chip8_create_cpu(chip8_cpu *cpu);

#endif