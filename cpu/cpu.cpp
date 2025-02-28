#include "cpu.hpp"

u32 CPU::execute(Memory& mem) {
    u32 cycles = 0;

    handle_interrupts(mem);
    exec_op(cycles, mem);

    if (PC == 0x100 && is_boot) {
        for (int i = 0; i < 0x100; ++i) {
            mem[i] = rom_first[i];
        }
        is_boot = false;
    }

    return cycles;
}