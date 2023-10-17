## todo / roadmap for 6502 emulator
[ ] **see [6502_opcodes](https://pastraiser.com/cpu/6502/6502_opcodes.html) for opcode table**
[ ] figure out where to load programs into memory (realism > efficiency)
[ ] implement a screen-sorta thing or something else for visual i/o
[ ] attempt to make this virtual computer work with some old operating system (is that possible?)

this table is the estimated order of implementation **within each category**. implementation among different categories is **not** guaranteed to be in the order of the categories within the table   

NOTE: some categories are disjoint, and perhaps even incomplete.

| Opcode | Instruction | Category    |
| ------ | ----------- | ----------- |
| 69     | ADC #$nn    | Arithmetic  |
| 65     | ADC $nn     | Arithmetic  |
| 75     | ADC $nn,X   | Arithmetic  |
| 79     | ADC $nn,Y   | Arithmetic  |
| 61     | ADC ($nn,X) | Arithmetic  |
| 71     | ADC ($nn),Y | Arithmetic  |
| 6D     | ADC $nnnn   | Arithmetic  |
| 29     | AND #$nn    | Logic       |
| 25     | AND $nn     | Logic       |
| 35     | AND $nn,X   | Logic       |
| 39     | AND $nn,Y   | Logic       |
| 21     | AND ($nn,X) | Logic       |
| 31     | AND ($nn),Y | Logic       |
| 2D     | AND $nnnn   | Logic       |
| 0A     | ASL A       | Shift       |
| 06     | ASL $nn     | Shift       |
| 16     | ASL $nn,X   | Shift       |
| 0E     | ASL $nnnn   | Shift       |
| 90     | BCC $nn     | Branch      |
| B0     | BCS $nn     | Branch      |
| F0     | BEQ $nn     | Branch      |
| 24     | BIT $nn     | Logic       |
| 34     | BIT $nn,X   | Logic       |
| 2C     | BIT $nnnn   | Logic       |
| 30     | BMI $nn     | Branch      |
| D0     | BNE $nn     | Branch      |
| 10     | BPL $nn     | Branch      |
| 00     | BRK         | Interrupt   |
| 50     | BVC $nn     | Branch      |
| 70     | BVS $nn     | Branch      |
| 18     | CLC         | Control     |
| D8     | CLD         | Control     |
| 58     | CLI         | Control     |
| B8     | CLV         | Control     |
| C9     | CMP #$nn    | Compare     |
| C5     | CMP $nn     | Compare     |
| D5     | CMP $nn,X   | Compare     |
| D9     | CMP $nn,Y   | Compare     |
| C1     | CMP ($nn,X) | Compare     |
| D1     | CMP ($nn),Y | Compare     |
| CD     | CMP $nnnn   | Compare     |
| E0     | CPX #$nn    | Compare     |
| E4     | CPX $nn     | Compare     |
| EC     | CPX $nn,X   | Compare     |
| C0     | CPY #$nn    | Compare     |
| C4     | CPY $nn     | Compare     |
| CC     | CPY $nn,X   | Compare     |
| C6     | DEC $nn     | Arithmetic  |
| D6     | DEC $nn,X   | Arithmetic  |
| CE     | DEC $nnnn   | Arithmetic  |
| CA     | DEX         | Arithmetic  |
| 88     | DEY         | Arithmetic  |
| 49     | EOR #$nn    | Logic       |
| 45     | EOR $nn     | Logic       |
| 55     | EOR $nn,X   | Logic       |
| 59     | EOR $nn,Y   | Logic       |
| 41     | EOR ($nn,X) | Logic       |
| 51     | EOR ($nn),Y | Logic       |
| 4D     | EOR $nnnn   | Logic       |
| E6     | INC $nn     | Arithmetic  |
| F6     | INC $nn,X   | Arithmetic  |
| EE     | INC $nnnn   | Arithmetic  |
| E8     | INX         | Arithmetic  |
| C8     | INY         | Arithmetic  |
| 4C     | JMP $nnnn   | Jump        |
| 6C     | JMP ($nnnn) | Jump        |
| 20     | JSR $nnnn   | Subroutine  |
| A9     | LDA #$nn    | Load        |
| A5     | LDA $nn     | Load        |
| B5     | LDA $nn,X   | Load        |
| B9     | LDA $nn,Y   | Load        |
| A1     | LDA ($nn,X) | Load        |
| B1     | LDA ($nn),Y | Load        |
| AD     | LDA $nnnn   | Load        |
| A2     | LDX #$nn    | Load        |
| A6     | LDX $nn     | Load        |
| B6     | LDX $nn,Y   | Load        |
| A0     | LDY #$nn    | Load        |
| A4     | LDY $nn     | Load        |
| B4     | LDY $nn,X   | Load        |
| 4A     | LSR A       | Shift       |
| 46     | LSR $nn     | Shift       |
| 56     | LSR $nn,X   | Shift       |
| 4E     | LSR $nnnn   | Shift       |
| EA     | NOP         | Control     |
| 09     | ORA #$nn    | Logic       |
| 05     | ORA $nn     | Logic       |
| 15     | ORA $nn,X   | Logic       |
| 19     | ORA $nn,Y   | Logic       |
| 01     | ORA ($nn,X) | Logic       |
| 11     | ORA ($nn),Y | Logic       |
| 0D     | ORA $nnnn   | Logic       |
| 48     | PHA         | Stack       |
| 08     | PHP         | Stack       |
| 68     | PLA         | Stack       |
| 28     | PLP         | Stack       |
| 2A     | ROL A       | Shift       |
| 26     | ROL $nn     | Shift       |
| 36     | ROL $nn,X   | Shift       |
| 2E     | ROL $nnnn   | Shift       |
| 6A     | ROR A       | Shift       |
| 66     | ROR $nn     | Shift       |
| 76     | ROR $nn,X   | Shift       |
| 6E     | ROR $nnnn   | Shift       |
| 40     | RTI         | Control     |
| 60     | RTS         | Control     |
| E9     | SBC #$nn    | Arithmetic  |
| E5     | SBC $nn     | Arithmetic  |
| F5     | SBC $nn,X   | Arithmetic  |
| F9     | SBC $nn,Y   | Arithmetic  |
| E1     | SBC ($nn,X) | Arithmetic  |
| F1     | SBC ($nn),Y | Arithmetic  |
| ED     | SBC $nnnn   | Arithmetic  |
| 38     | SEC         | Control     |
| F8     | SED         | Control     |
| 78     | SEI         | Control     |
| 85     | STA $nn     | Store       |
| 95     | STA $nn,X   | Store       |
| 99     | STA $nn,Y   | Store       |
| 81     | STA ($nn,X) | Store       |
| 91     | STA ($nn),Y | Store       |
| 8D     | STA $nnnn   | Store       |
| 86     | STX $nn     | Store       |
| 96     | STX $nn,Y   | Store       |
| 84     | STY $nn     | Store       |
| 94     | STY $nn,X   | Store       |
| AA     | TAX         | Transfer    |
| A8     | TAY         | Transfer    |
| BA     | TSX         | Transfer    |
| 8A     | TXA         | Transfer    |
| 9A     | TXS         | Transfer    |
| 98     | TYA         | Transfer    |
