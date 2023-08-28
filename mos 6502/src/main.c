#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/asm.h"
#include "../include/cpu.h"
#include "../include/error.h"
#include "../include/ins.h"

struct mos6502* cpu;

int main(int argc, char** argv) {

    #define HEXDUMP

    ASSERT_M(argc > 1, "no binary provided");

    cpu = initialiseCPU();
    reset(RST_VECT); // default value of reset vector

    char* binary = argv[1];
    FILE* buffer = openBinary(binary);

    cycle();
    return 0;
}

struct mos6502* initialiseCPU() {
    struct mos6502* cpu = (struct mos6502*)malloc(sizeof(struct mos6502));
   
    // PC set to RST_VECT in main
    cpu->A = cpu->X = cpu->Y = cpu->P = cpu->S = cpu->PC = 0;

    memset(cpu->memory, 0, MEM_SIZE);
    cpu->stack = &cpu->memory[STA_PG];

    cpu->speed       = 1.02; // 1.02 mhz
    cpu->initialised = true;

    return cpu;
}

static inline uint8_t*
fetchOperands(uint8_t amt) {
    ASSERT_M(amt > 0, "cannot fetch n <= 0 operands");
    
    uint8_t* operands = (uint8_t*)malloc(sizeof(uint8_t) * amt);

    for (int i = 0; i < amt; i++) {
        cpu->PC++;
        uint8_t value = cpu->memory[cpu->PC];
        operands[i]   = value;
    }

    return operands;
}

static inline void 
decodeOpcode(uint8_t AAACC, uint8_t BBB) {
    switch (AAACC) {
        case LDA:
            switch (BBB) {
                fetchOperands(1);

                case G1_IMMEDIATE:
                    addToQueue(&LDA_IMMEDIATE);
                    break;
                case G1_ZERO_PAGE:      
                    addToQueue(&LDA_ZERO_PAGE);
                    break;
                case G1_ZERO_PAGE_X:
                    addToQueue(&LDA_ZERO_PAGE_X);
                    break;
                case G1_ABSOLUTE:
                    addToQueue(&LDA_ABSOLUTE);
                    break;
                case G1_ABSOLUTE_X:
                    addToQueue(&LDA_ABSOLUTE_X);
                    break;
                case G1_ABSOLUTE_Y:
                    addToQueue(&LDA_ABSOLUTE_Y);
                    break;
                case G1_ZERO_PAGE_X_I:
                    addToQueue(&LDA_ZERO_PAGE_X_I);
                    break;
                case G1_ZERO_PAGE_Y_I:
                    addToQueue(&LDA_ZERO_PAGE_Y_I);
                    break;
            }

        break;
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
    default:
        ASSERT_MF(false, "UNIMPLEMENTED OPCODE %d", (AAACC << 2) & BBB);
        break;
};
}

static inline void
executeInstruction(uint8_t opcode) {
    uint8_t BBB   = (opcode >> 2) & 0b00000111; // ADDR_MODE
    uint8_t AAACC = (opcode & 0b00000011)       // OPCODE excluding ADDR_MODE
                            | opcode >> 3;
    
    decodeOpcode(AAACC, BBB);
}

void cycle() {
    double       delay_us = 1 / cpu->speed;
    unsigned int ticks    = 0;

    while (!cpu->paused && ticks < 70) {
        uint8_t opcode = cpu->memory[cpu->PC];

        executeInstruction(opcode);

        ticks++;
        cpu->PC++; // assume this is correct for now

#ifdef HEXDUMP
        // hexdump-style opcode printing
        printf("%02x ", opcode);
        if      (ticks % 16 == 0) printf("\n");
        else if (ticks % 8 == 0)  printf(" ");
#endif

        usleep(delay_us);
    }
}

void reset(uint16_t vector) {
    cpu->PC      = vector;
    cpu->pcreset = true;
}

FILE* openBinary(const char* filename) {
    ASSERT_M(cpu->initialised, "cpu not initialised");
    ASSERT_M(cpu->pcreset,     "pc not set to RST_VECT");

    FILE* fd;
    ASSERT_M((fd = fopen(filename, "rb")), "file failed to open");

    fseek(fd, 0, SEEK_END); long fs = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    size_t bytesRead = fread(&cpu->memory[cpu->PC], 1, fs, fd);
    ASSERT_M(bytesRead == fs, "failed to read all bytes of file");

    fclose(fd);
    return fd;
}
