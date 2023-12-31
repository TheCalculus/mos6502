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

// yes i know i can write it as 1 << ...
#define PS_SIGN  0b10000000
#define PS_OVER  0b01000000
#define PS_RESV  0b00100000
#define PS_BRAK  0b00010000
#define PS_BCD   0b00001000
#define PS_INRD  0b00000100
#define PS_ZERO  0b00000010
#define PS_CRRY  0b00000001

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

    // EMULATOR FLAGS AND VARIABLES
    bool     paused;      // checks whether the emulator should continue emulating cycles
    bool     initialised; // verifies that the cpu struct has been initialised
    bool     pcreset;     // verifies that pc has been set to the reset vector
    double   speed;       // mhz
};

static inline void     executeInstruction(uint8_t opcode);
static inline void     decodeOpcode(uint8_t opcode);
static inline uint8_t* fetchOperands(uint8_t amt);

static inline uint8_t  hi(uint8_t byte);
static inline uint8_t  lo(uint8_t byte);

void  reset(uint16_t vector);
void  cycle();

FILE* openBinary(const char* filename);

struct mos6502* initialiseCPU();

#endif
