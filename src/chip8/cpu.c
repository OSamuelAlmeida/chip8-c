#include "chip8/cpu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHIP8_INSTRUCTIONS_PER_SECOND 700

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

void chip8_execute_opcode(chip8_cpu *cpu, uint16_t opcode, chip8_window *window, chip8_ram *ram)
{
    cpu->pc += 2;
    uint8_t n = opcode & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    uint8_t nnn = opcode & 0x0FFF;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        if (opcode == 0x00E0)
        {
            chip8_clear_pixels(window);
        }
        break;
    case 0x1000:
        cpu->pc = nnn;
        break;
    case 0x2000:
        break;
    case 0x3000:
        break;
    case 0x4000:
        break;
    case 0x5000:
        break;
    case 0x6000:
        cpu->registers[x] = nn;
        break;
    case 0x7000:
        cpu->registers[x] += nn;
        break;
    case 0x8000:
        break;
    case 0x9000:
        break;
    case 0xA000:
        cpu->I = opcode & 0x0FFF;
        break;
    case 0xB000:
        break;
    case 0xC000:
        break;
    case 0xD000:
        chip8_draw_sprite(window, &ram->data[cpu->I], cpu->registers[x], cpu->registers[y], n, &cpu->registers[0xF]);
        break;
    case 0xE000:
        break;
    case 0xF000:
        break;
    default:
        printf("Unknown opcode: 0x%X\n", opcode);
    }
}