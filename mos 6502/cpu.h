#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define MEM_SIZE 0x64000  // bytes
#define ZERO_PG  0x000    // 0x000 - 0x0FF
#define STACK_PG 0x100    // 0x100 - 0x1FF
#define SCREEN   0x200    // 0x200 - 0x2FF (for testing publicly available 6502 assembly)

struct mos6502 {
    uint8_t  A;     // accumulator
    uint8_t  X;     // index register X
    uint8_t  Y;     // index register Y
    uint8_t  P;     // processor status flag bits           \
                       (N, V, reserved, B, D, I, Z, C)      \
                       (sign, overflow, -, break, bcd, interrupt, zero, carry)
    uint8_t  S;     // stack pointer
    uint16_t PC;    // program counter

    uint8_t* stack;
    uint8_t  memory[MEM_SIZE];

    // EMULATOR FLAGS
    bool     paused;
    uint8_t  speed;
};


#endif
