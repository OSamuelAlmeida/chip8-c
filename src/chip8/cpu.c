#include "chip8/cpu.h"

#include <stdlib.h>

chip8_cpu *chip8_create_cpu()
{
    chip8_cpu *cpu = malloc(sizeof(chip8_cpu));
    cpu->registers = calloc(16, sizeof(uint8_t));
    cpu->I = 0;
    cpu->pc = 0x200;
    cpu->sp = 0;
    cpu->stack = calloc(16, sizeof(uint16_t));
    cpu->delay_timer = 0;
    cpu->sound_timer = 0;

    return cpu;
}

void chip8_destroy_cpu(chip8_cpu *cpu)
{
    free(cpu->registers);
    free(cpu->stack);
    free(cpu);
}