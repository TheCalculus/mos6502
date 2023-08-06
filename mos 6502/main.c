#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct mos6502* cpu;

// ADDRESSING MODES (BBB)

// TODO: figure out whether all addressing modes (even from different groups) \
   even need to be in different enums

enum ADDR_MODE_G1 {
    // CC 01, "group one" instructions
    G1_ZERO_PAGE_X_I = 0b000,  // (zero page, X)
    G1_ZERO_PAGE     = 0b001,  // zero page
    G1_IMMEDIATE     = 0b010,  // #immediate
    G1_ABSOLUTE      = 0b011,  // absolute
    G1_ZERO_PAGE_Y_I = 0b100,  // (zero page), Y
    G1_ZERO_PAGE_X   = 0b101,  // zero page, X
    G1_ABSOLUTE_Y    = 0b110,  // absolute, Y
    G1_ABSOLUTE_X    = 0b111,  // absolute, X
};

enum ADDR_MODE_G2 {
    // CC 10, "group two" instructions
    G2_IMMEDIATE     = 0b000,  // #immediate
    G2_ZERO_PAGE     = 0b001,  // zero page
    G2_ACCUMULATOR   = 0b010,  // accumulator
    G2_ABSOLUTE      = 0b011,  // absolute
    G2_ZERO_PAGE_X   = 0b101,  // zero page, X
    G2_ABSOLUTE_X    = 0b111,  // absolute, X
};

enum ADDR_MODE_G3 {
    // CC 00, "group three" instructions
    G3_IMMEDIATE     = 0b000,  // #immediate
    G3_ZERO_PAGE     = 0b001,  // zero page
    G3_ABSOLUTE      = 0b011,  // absolute
    G3_ZERO_PAGE_X   = 0b101,  // zero page, X
    G3_ABSOLUTE_X    = 0b111,  // absolute, X
};

void initialiseCPU(struct mos6502* cpu) {
    cpu->A  = cpu->X = cpu->Y = cpu->P = cpu->S = cpu->PC = 0;
    cpu->PC = 0x0000;

    memset(cpu->memory, 0, sizeof(cpu->memory));
    cpu->stack = &cpu->memory[STACK_PG];
}

void executeInstruction(uint8_t opcode) {
    // TODO: implement function
    uint8_t segmentX = opcode >> (8 - 0x03);         // AAA
    uint8_t segmentY = opcode &  ((1 << 0x02) - 1);  // CC

    cpu->PC += 2;
}

void cycle() {
    for (int i = 0; i < cpu->speed; i++) {
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
