# mos 6502 emulation
an emulation of the [MOS Technology 6502](https://en.wikipedia.org/wiki/MOS_Technology_6502) written in pure c  
⚠️ this is a very early iteration of the README and is definitely subject to change  

### install and usage

<hr>

for installing on  **macos / unix-like** systems  

NOTE: `build.sh` will be added in a later commit. if you do not see this yet, try building manually

1. open terminal
2. run `sh build.sh`
3. run the output executable with `./6502emulator`  

if the program fails to compile, it may be because you do not have a supported compiler installed. try building manually.

<hr>

for installing on **windows** systems

NOTE: `build.bat` will be added in a later commit. if you do not see this yet, try building manually

1. open cmd / powershell
2. run `build.bat`
3. run the output executable with `6502emulator`

<hr>

the emulator is planned to be implemented with `chasm` ([here](https://github.com/TheCalculus/chasm), if it is ever usable) so that it can be run on the web. why? because i do not want to make an application / gui for the emulator.  

### references, resources  
- [How to Create Your Very Own Chip-8 Emulator](https://www.freecodecamp.org/news/creating-your-very-own-chip-8-emulator/)
- [MOS Microcomputers Programming Manual](https://archive.org/details/mos_microcomputers_programming_manual/page/n73/mode/2up?view=theater)
- [6502 datasheet](http://archive.6502.org/datasheets/mos_6500_mpu_nov_1985.pdf)
- [6502 Addressing Modes - CDOT Wiki](https://wiki.cdot.senecacollege.ca/wiki/6502_Addressing_Modes)
- [The 6502 Instruction Set Decoded](https://llx.com/Neil/a2/opcodes.html)
#### currently using
- [6502 Addressing Modes](https://slark.me/c64-downloads/6502-addressing-modes.pdf)
- [6502 CPU | Ultimate C64 Reference](https://www.pagetable.com/c64ref/6502/?tab=3)
- [Internals of BRK/IRQ/NMI/RESET on a MOS 6502](https://www.pagetable.com/?p=410)
- [MOS Technology 6502 CPU Emulation](https://jayscholar.etown.edu/cgi/viewcontent.cgi?article=1000&context=comscistu)
- [MOS Technology 6502](https://en.wikipedia.org/wiki/MOS_Technology_6502)
