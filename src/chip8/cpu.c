#include "chip8/cpu.h"

#include <stdlib.h>
#include <string.h>

void chip8_create_cpu(chip8_cpu *cpu)
{
    cpu->I = 0;
    cpu->pc = 0x200;
    cpu->sp = 0;
    cpu->delay_timer = 0;
    cpu->sound_timer = 0;
    memset(cpu->stack, 0, sizeof(cpu->stack));
    memset(cpu->registers, 0, sizeof(cpu->registers));
}