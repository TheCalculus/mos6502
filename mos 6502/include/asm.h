#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

// ADDRESSING MODES (BBB)

// TODO: figure out whether all addressing modes (even from different groups) \
   even need to be in different enums

#ifdef OLD

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

#endif

enum OPCODE {
    // ARITH
    ADC_IMMEDIATE   = 0x69,
    ADC_ZERO_PAGE   = 0x65,
    ADC_ZERO_PAGE_X = 0x75,
    ADC_ABSOLUTE    = 0x6D,
    ADC_ABSOLUTE_X  = 0x7D,
    ADC_ABSOLUTE_Y  = 0x79,
    ADC_INDIRECT_X  = 0x61,
    ADC_INDIRECT_Y  = 0x71,

    SBC_IMMEDIATE   = 0xE9,
    SBC_ZERO_PAGE   = 0xE5,
    SBC_ZERO_PAGE_X = 0xF5,
    SBC_ABSOLUTE    = 0xED,
    SBC_ABSOLUTE_X  = 0xFD,
    SBC_ABSOLUTE_Y  = 0xF9,
    SBC_INDIRECT_X  = 0xE1,
    SBC_INDIRECT_Y  = 0xF1,

    INC_ZERO_PAGE   = 0xE6,
    INC_ZERO_PAGE_X = 0xF6,
    INC_ABSOLUTE    = 0xEE,
    INC_ABSOLUTE_X  = 0xFE,

    DEC_ZERO_PAGE   = 0xC6,
    DEC_ZERO_PAGE_X = 0xD6,
    DEC_ABSOLUTE    = 0xCE,
    DEC_ABSOLUTE_X  = 0xDE,

    // LOAD
    LDA_IMMEDIATE   = 0xA9,
    LDA_ZERO_PAGE   = 0xA5,
    LDA_ZERO_PAGE_X = 0xB5,
    LDA_ABSOLUTE    = 0xAD,
    LDA_ABSOLUTE_X  = 0xBD,
    LDA_ABSOLUTE_Y  = 0xB9,
    LDA_INDIRECT_X  = 0xA1,
    LDA_INDIRECT_Y  = 0xB1,

    LDX_IMMEDIATE   = 0xA2,
    LDX_ZERO_PAGE   = 0xA6,
    LDX_ZERO_PAGE_Y = 0xB6,
    LDX_ABSOLUTE    = 0xAE,
    LDX_ABSOLUTE_Y  = 0xBE,

    LDY_IMMEDIATE   = 0xA0,
    LDY_ZERO_PAGE   = 0xA4,
    LDY_ZERO_PAGE_X = 0xB4,
    LDY_ABSOLUTE    = 0xAC,
    LDY_ABSOLUTE_X  = 0xBC,

    STA_ZERO_PAGE   = 0x85,
    STA_ZERO_PAGE_X = 0x95,
    STA_ABSOLUTE    = 0x8D,
    STA_ABSOLUTE_X  = 0x9D,
    STA_ABSOLUTE_Y  = 0x99,
    STA_INDIRECT_X  = 0x81,
    STA_INDIRECT_Y  = 0x91,

    STX_ZERO_PAGE   = 0xD9,
    STX_ZERO_PAGE_Y = 0xD9,
    STX_ABSOLUTE    = 0xD9,
    STY             = 0xD9,
    
    // STACK
    PHA             = 0x48,
    PHP             = 0x08,
    PLA             = 0x68,
    PLP             = 0x28,
};

