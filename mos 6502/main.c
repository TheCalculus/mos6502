#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "asm.h"

struct mos6502* cpu;

int main(int argc, char** argv) {
    if (argc < 1) exit(1);

    FILE* buffer = openBinary(argv[1]);
    char  opcode;

    initialiseCPU(cpu);

    while ((opcode = getc(buffer)) != EOF) {
        executeInstruction((uint8_t)opcode); 
    }

    return 0;
}

void initialiseCPU(struct mos6502* cpu) {
    cpu = (struct mos6502*)malloc(sizeof(struct mos6502));
    
    reset(RST_VECT); // default value of reset vector
    cpu->A  = cpu->X = cpu->Y = cpu->P = cpu->S = cpu->PC = 0;

    memset(cpu->memory, 0, MEM_SIZE);
    cpu->stack = &cpu->memory[STA_PG];
}

void executeInstruction(uint8_t opcode) {
    uint8_t BBB   = (opcode >> 2) & 0b00000111; // ADDR_MODE
    uint8_t AAACC = (opcode & 0b00000011)       // OPCODE excluding ADDR_MODE
                            | opcode >> 3;

    switch (AAACC) {
        // ARITH
        case ADC:
            /* https://stackoverflow.com/questions/29193303/6502-emulation-proper-way-to-implement-adc-and-sbc */

            switch (BBB) {
                uint8_t* memory = cpu->stack + cpu->S;  // address of stack @ stack pointer
                uint8_t  carry  = cpu->P & 0b00000001;  // check whether carry bit is set

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
                case G3_IMMEDIATE:      break;
                case G3_ABSOLUTE:       break;
                case G3_ZERO_PAGE:      break;

                case G3_IMPLIED:        break; // INX, INY
            };

            break;
        case CPY:
            switch (BBB) {
                case G3_IMMEDIATE:      break;
                case G3_ABSOLUTE:       break;
                case G3_ZERO_PAGE:      break;
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
                case G2_ABSOLUTE:       break;
                case G2_ABSOLUTE_X:     break;
                case G2_ZERO_PAGE:      break;
                case G2_ZERO_PAGE_X:    break;

                case G3_IMPLIED:        break;  // DEX
            };
            
            break;
        case DEY:
            switch (BBB) {
                case G3_IMPLIED:        break;
            }
            
            break;
        case INC:
            switch (BBB) {
                case G2_ABSOLUTE:       break;
                case G2_ABSOLUTE_X:     break;
                case G2_ZERO_PAGE:      break;
                case G2_ZERO_PAGE_X:    break;
            }
        // see CPX for INX, INY
    };
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

void reset(uint16_t vector) {
    cpu->PC = cpu->memory[vector];
    // cycle()?
}

FILE* openBinary(const char* filename) {
    FILE* fd;
    if ((fd = fopen(filename, "rb")) == NULL) exit(1);
    
    return fd;
}

