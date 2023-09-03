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
addToQueue(fnptr func) {
    cpu->queue = func;
    func();
}

static inline void 
decodeOpcode(uint8_t opcode) {
    switch (opcode) {
    case LDA_IMMEDIATE:
        IMPLEMENTATION_LDA_IMMEDIATE();
    case LDA_ZERO_PAGE:
        IMPLEMENTATION_LDA_ZERO_PAGE();
    case LDA_ZERO_PAGE_X: 
        IMPLEMENTATION_LDA_ZERO_PAGE_X();
    case LDA_ABSOLUTE: 
        IMPLEMENTATION_LDA_ABSOLUTE();
    case LDA_ABSOLUTE_X: 
        IMPLEMENTATION_LDA_ABSOLUTE_X();
    case LDA_ABSOLUTE_Y: 
        IMPLEMENTATION_LDA_ABSOLUTE_Y();
    case LDA_INDIRECT_X: 
        IMPLEMENTATION_LDA_INDIRECT_X();
    case LDA_INDIRECT_Y: 
        IMPLEMENTATION_LDA_INDIRECT_Y();
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
