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

// TODO: aim for cycle accuracy later

static inline void 
decodeOpcode(uint8_t opcode) {
    uint8_t  byte;
    uint8_t* bytes;
    uint16_t word;

    // TODO: minimise reptition

    switch (opcode) {
    case LDA_IMMEDIATE:
        printf("LDA IMMEDIATE\n");
   
        byte   = fetchOperands(1)[0];
        cpu->A = byte;

        break;

    case LDA_ZERO_PAGE:
        printf("LDA ZERO_PAGE\n");

        byte = fetchOperands(1)[0];

        cpu->A = cpu->memory[0x0F & byte];

        break;

    case LDA_ZERO_PAGE_X:
        printf("LDA ZERO_PAGE_X\n");

        byte = fetchOperands(1)[0];

        cpu->A = cpu->memory[0x0F & byte] +
                 cpu->X;

        break;

    case LDA_ABSOLUTE:
        printf("LDA ASBOLUTE\n");

        bytes = fetchOperands(2);

        // LDA $bytes[1]bytes[0]

        word = (0xF0 & bytes[1]) |
               (0x0F & bytes[0]);

        cpu->A = cpu->memory[word];

        break;

    case LDA_ABSOLUTE_Y:
        bytes = fetchOperands(2);

        word = (0xF0 & bytes[1]) |
               (0x0F & bytes[0]) + 
               cpu->Y /* y register */;

        cpu->A = cpu->memory[word];

        break;

    case LDA_ABSOLUTE_X:
        printf("LDA ABSOLUTE_X\n");

        bytes = fetchOperands(2);

        word = (0xF0 & bytes[1]) |
               (0x0F & bytes[0]) + 
               cpu->X /* x register */;

        cpu->A = cpu->memory[word];

        break;

    case LDA_INDIRECT_X: 
        printf("LDA INDIRECT_X\n");
        break;
    case LDA_INDIRECT_Y: 
        printf("LDA INDIRECT_Y\n");
        break;
    default:
        ASSERT_MF(false, "UNIMPLEMENTED OPCODE %02x", opcode);
        break;
    };
}

static inline void
executeInstruction(uint8_t opcode) {
    uint8_t BBB   = (opcode >> 2) & 0b00000111; // ADDR_MODE
    uint8_t AAACC = (opcode & 0b00000011)       // OPCODE excluding ADDR_MODE
                            | opcode >> 3;
    
    decodeOpcode(opcode);
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
