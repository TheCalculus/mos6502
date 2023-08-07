#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define MEM_SIZE 0x64000  // bytes
#define ZERO_PG  0x0000   // 0x0000 - 0x00FF
#define STACK_PG 0x0100   // 0x0100 - 0x01FF

struct mos6502 {
    uint8_t  A;     // accumulator
    uint8_t  X;     // index register X
    uint8_t  Y;     // index register Y
    uint8_t  P;     // processor status flag bits (N, V, reserved, B, D, I, Z, C)
    uint8_t  S;     // stack pointer
    uint16_t PC;    // program counter

    uint8_t* stack;
    uint8_t  memory[MEM_SIZE];

    // EMULATOR FLAGS
    bool     paused;
    uint8_t  speed;
};


#endif
