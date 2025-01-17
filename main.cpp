#include <iostream>
#include "cpu/cpu.hpp"

int main() {
    Memory mem;
    CPU cpu;
    mem.init();

    cpu.load_bootup("dmg_boot.bin", mem);

    u32 cycles = 0;
    while (1) {
        cycles += cpu.execute(mem);
        //printf("%d\n", cpu.PC);
    }

    return 0;

    mem[0x00] = CPU::INS_LD_HN; // B
    mem[0x01] = 0xF0;
    mem[0x02] = CPU::INS_LD_LN; // C
    mem[0x03] = 0xFF;
    mem[0x04] = CPU::INS_LD_AN; // D
    mem[0x05] = 0x60;
    mem[0x06] = CPU::INS_LD_HLIA; // A

    u32 instructions = 4;
    for (int i = 0; i < instructions; ++i) {
        cycles += cpu.execute(mem);
    }
    printf("%u\n", cycles);
    DEBUG(mem[0xF0FF]);
    cpu.debug();
    return 0;
}
