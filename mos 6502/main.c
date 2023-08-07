#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cpu.h"
#include "asm.c"

struct mos6502* cpu;

void initialiseCPU(struct mos6502* cpu) {
    cpu->A  = cpu->X = cpu->Y = cpu->P = cpu->S = cpu->PC = 0;
    cpu->PC = 0x0000;

    memset(cpu->memory, 0, sizeof(cpu->memory));
    cpu->stack = &cpu->memory[STACK_PG];
}

void executeInstruction(uint8_t opcode) {
    // TODO: implement function
   
    uint8_t BBB   = (opcode >> 2) & 0b00000111; // ADDR_MODE
    uint8_t AAACC = (opcode & 0b00000011)       // OPCODE excluding ADDR_MODE
                            | opcode >> 3;

    switch (AAACC) {
        // ARITH
        case ADC:
            switch (BBB) {
                case G1_IMMEDIATE:      break;
                case G1_ABSOLUTE:       break;
                case G1_ABSOLUTE_X:     break;
                case G1_ABSOLUTE_Y:     break;
                case G1_ZERO_PAGE:      break;
                case G1_ZERO_PAGE_X:    break;
                case G1_ZERO_PAGE_X_I:  break;
                case G1_ZERO_PAGE_Y_I:  break;
            };

            break;
        case CMP:
            switch (BBB) {
                case G1_IMMEDIATE:      break;
                case G1_ABSOLUTE:       break;
                case G1_ABSOLUTE_X:     break;
                case G1_ABSOLUTE_Y:     break;
                case G1_ZERO_PAGE:      break;
                case G1_ZERO_PAGE_X:    break;
                case G1_ZERO_PAGE_X_I:  break;
                case G1_ZERO_PAGE_Y_I:  break;
            };

            break;
        case CPX:
            switch (BBB) {
                case G3_IMMEDIATE:   break;
                case G3_ABSOLUTE:    break;
                case G3_ZERO_PAGE:   break;
            };

            break;
        case CPY:
            switch (BBB) {
                case G3_IMMEDIATE:   break;
                case G3_ABSOLUTE:    break;
                case G3_ZERO_PAGE:   break;
            };

            break;
        case SBC:
            switch (BBB) {
                case G1_IMMEDIATE:      break;
                case G1_ABSOLUTE:       break;
                case G1_ABSOLUTE_X:     break;
                case G1_ABSOLUTE_Y:     break;
                case G1_ZERO_PAGE:      break;
                case G1_ZERO_PAGE_X:    break;
                case G1_ZERO_PAGE_X_I:  break;
                case G1_ZERO_PAGE_Y_I:  break;
            };
            
            break;
        // INC
        case DEC:
            switch (BBB) {
                case G2_ABSOLUTE:    break;
                case G2_ABSOLUTE_X:  break;
                case G2_ZERO_PAGE:   break;
                case G2_ZERO_PAGE_X: break;
            };
            
            break;
        // TODO: continue
    };

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
