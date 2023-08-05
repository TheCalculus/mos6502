#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 0x64000  // bytes
#define ZERO_PG  0x0000   // 0x0000 - 0x00FF
#define STACK_PG 0x0100   // 0x0100 - 0x01FF
#define SPEED    1

struct mos6502 {
    uint8_t  A;     // accumulator
    uint8_t  X;     // index register X
    uint8_t  Y;     // index register Y
    uint8_t  P;     // processor status flag bits (N, V, reserved, B, D, I, Z, C)
    uint8_t  S;     // stack pointer
    uint16_t PC;    // program counter

    uint8_t* stack;
    uint8_t  memory[MEM_SIZE];
};

struct mos6502* cpu;

// ADDRESSING MODES (BBB for all CC)
enum GRP1_BBB {
    IMPLIED     = 0b000,
    ACCUMULATOR = 0b001,
    IMMEDIATE   = 0b010,
    ABSOLUTE    = 0b011,
    XABSOLUTE   = 0b100,
    YABSOLUTE   = 0b101,
    IABSOLUTE   = 0b011,
    ZEROPAGE    = 0b110,
    XZEROPAGE   = 0b111,
    YZEROPAGE   = 0b101,
    IXZEROPAGE  = 0b100,
    IYZEROPAGE  = 0b100,
    RELATIVE    = 0b100,
};

void initialiseCPU(struct mos6502* cpu) {
    cpu->A  = cpu->X = cpu->Y = cpu->P = cpu->S = cpu->PC = 0;
    cpu->PC = 0x0000;

    memset(cpu->memory, 0, sizeof(cpu->memory));
    stack = &memory[STACK_PG];
}

void executeInstruction(uint8_t opcode) {
    // TODO: implement function
    uint8_t segmentX = opcode >> (8 - 0x03);         // AAA
    uint8_t segmentY = opcode &  ((1 << 0x02) - 1);  // CC

    cpu->PC += 2;
}

void cycle() {
    for (int i = 0; i < SPEED; i++) {
        if (cpu->paused)
            continue;

        // AAABBBCC, AAA and CC define the opcode
        uint8_t opcode = cpu->memory[cpu->PC];

        executeInstruction(opcode);
    }
}

int main() {
    initialiseCPU(cpu);

    return 0;
}
