#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// see https://en.wikipedia.org/wiki/Reset_vector#:~:text=address%20stored%20at-,0xFFFC%20and%200xFFFD,-.

#define MEM_SIZE 0x64000  // bytes
#define RST_VECT 0xFCFD   // reset vector - initial value of PC is stored here
#define ZER_PG   0x000    // 0x000 - 0x0FF
#define STA_PG   0x100    // 0x100 - 0x1F
#define SCR      0x200    // 0x200 - 0x2FF (for testing publicly available 6502 assembly)

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

void  initialiseCPU(struct mos6502* cpu);
void  executeInstruction(uint8_t opcode);
void  reset(uint16_t vector);
void  cycle();
FILE* openBinary(const char* filename);

#endif
