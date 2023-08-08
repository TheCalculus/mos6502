#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

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
    G3_IMPLIED       = 0b110,  // implied
    G3_IMMEDIATE     = 0b000,  // #immediate
    G3_ZERO_PAGE     = 0b001,  // zero page
    G3_ABSOLUTE      = 0b011,  // absolute
    G3_ZERO_PAGE_X   = 0b101,  // zero page, X
    G3_ABSOLUTE_X    = 0b111,  // absolute, X
};

enum OPCODE_AAACC {
    // ARITHMETIC
   
    ADC = 0b01101,
    CMP = 0b11001,
    CPX = 0b11100,   // also INX, INY
    CPY = 0b11000,
    SBC = 0b11101,

    // INCREMENTS (?)
   
    DEC = 0b11010,   // also DEX
    DEY = 0b10000,
    INC = 0b11110,
    // see CPX for INX, INY
 
    // LOAD

    LDA = 0b10101,
    LDX = 0b10110,   // also TAX, TSX
    LDY = 0b10100,   // also TAY
    STA = 0b10001,
    STX = 0b10010,   // also TXA, TXS
    STY = 0b10000,   // also TYA
};
