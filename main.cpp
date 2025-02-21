#include <iostream>
#include "cpu/cpu.hpp"
#include "timers/timers.hpp"
#include "ppu/ppu.hpp"

int main() {
    Timers timers;
    Memory mem{};
    CPU cpu{};
    PPU ppu{};

    mem.init();
    ppu.init();

    //cpu.load_bootup("dmg_boot.bin", mem);

    u32 cycles = 0;
    while (1) {
        u32 c = cpu.execute(mem);
        timers.update(c, mem);
        ppu.update(c * 4, mem);
        cycles += c;
    }

    return 0;
}
