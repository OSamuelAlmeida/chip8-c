#include "chip8/cpu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chip8/keyboard.h"

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
    uint16_t n = opcode & 0x000F;
    uint16_t nn = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;
    uint16_t x = (opcode & 0x0F00) >> 8;
    uint16_t y = (opcode & 0x00F0) >> 4;
    uint8_t tmp = 0;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        if (opcode == 0x00E0)
            chip8_clear_pixels(window);
        else if (opcode == 0x00EE)
            cpu->pc = cpu->stack[--cpu->sp];
        break;
    case 0x1000:
        cpu->pc = nnn;
        break;
    case 0x2000:
        cpu->stack[cpu->sp++] = cpu->pc;
        cpu->pc = nnn;
        break;
    case 0x3000:
        if (cpu->registers[x] == nn)
            cpu->pc += 2;
        break;
    case 0x4000:
        if (cpu->registers[x] != nn)
            cpu->pc += 2;
        break;
    case 0x5000:
        if (cpu->registers[x] == cpu->registers[y])
            cpu->pc += 2;
        break;
    case 0x6000:
        cpu->registers[x] = nn;
        break;
    case 0x7000:
        cpu->registers[x] += nn;
        break;
    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0000:
            cpu->registers[x] = cpu->registers[y];
            break;
        case 0x0001:
            cpu->registers[x] |= cpu->registers[y];
            cpu->registers[0xF] = 0;
            break;
        case 0x0002:
            cpu->registers[x] &= cpu->registers[y];
            cpu->registers[0xF] = 0;
            break;
        case 0x0003:
            cpu->registers[x] ^= cpu->registers[y];
            cpu->registers[0xF] = 0;
            break;
        case 0x0004:
            tmp = cpu->registers[x];
            cpu->registers[x] += cpu->registers[y];
            cpu->registers[0xF] = tmp > cpu->registers[x];
            break;
        case 0x0005:
            tmp = cpu->registers[x];
            cpu->registers[x] -= cpu->registers[y];
            cpu->registers[0xF] = tmp >= cpu->registers[y];
            break;
        case 0x0006:
            cpu->registers[x] = cpu->registers[y] >> 1;
            cpu->registers[0xF] = cpu->registers[y] & 0x1;
            break;
        case 0x0007:
            tmp = cpu->registers[y];
            cpu->registers[x] = cpu->registers[y] - cpu->registers[x];
            cpu->registers[0xF] = tmp > cpu->registers[x];
            break;
        case 0x000E:
            cpu->registers[x] = cpu->registers[y] << 1;
            cpu->registers[0xF] = cpu->registers[y] >> 7;
            break;
        }
        break;
    case 0x9000:
        if (cpu->registers[x] != cpu->registers[y])
            cpu->pc += 2;
        break;
    case 0xA000:
        cpu->I = opcode & 0x0FFF;
        break;
    case 0xB000:
        cpu->pc = cpu->registers[0] + nnn;
        break;
    case 0xC000:
        cpu->registers[x] = nn & (rand() % 255);
        break;
    case 0xD000:
        chip8_draw_sprite(window, &ram->data[cpu->I], cpu->registers[x], cpu->registers[y], n, &cpu->registers[0xF]);
        break;
    case 0xE000:
        switch (opcode & 0x00FF)
        {
        case 0x009E:
            if (chip8_is_key_pressed(cpu->registers[x]))
                cpu->pc += 2;
            break;
        case 0x00A1:
            if (!chip8_is_key_pressed(cpu->registers[x]))
                cpu->pc += 2;
            break;
        }
        break;
    case 0xF000:
        switch (opcode & 0x00FF)
        {
        case 0x0007:
            cpu->registers[x] = cpu->delay_timer;
            break;
        case 0x000A:
            cpu->pc -= 2;
            for (int i = 0; i < 16; i++)
            {
                if (chip8_is_key_pressed(i))
                {
                    cpu->registers[x] = i;
                    cpu->pc += 2;
                    break;
                }
            }
            break;
        case 0x0015:
            cpu->delay_timer = cpu->registers[x];
            break;
        case 0x0018:
            cpu->sound_timer = cpu->registers[x];
            break;
        case 0x001E:
            cpu->I += cpu->registers[x];
            break;
        case 0x0029:
            cpu->I = cpu->registers[x] * 5;
            break;
        case 0x0033:
            ram->data[cpu->I] = cpu->registers[x] / 100;
            ram->data[cpu->I + 1] = (cpu->registers[x] / 10) % 10;
            ram->data[cpu->I + 2] = cpu->registers[x] % 10;
            break;
        case 0x0055:
            for (int i = 0; i <= x; i++)
                ram->data[cpu->I + i] = cpu->registers[i];
            cpu->I++;
            break;
        case 0x0065:
            for (int i = 0; i <= x; i++)
                cpu->registers[i] = ram->data[cpu->I + i];
            cpu->I++;
            break;
        }
        break;
    default:
        printf("Unknown opcode: 0x%X\n", opcode);
    }
}