#include <iostream>
#include "cpu/cpu.hpp"
#include "timers/timers.hpp"
#include "ppu/ppu.hpp"

int main() {
    Timers timers;
    Memory mem{};
    CPU cpu{};
    PPU ppu{};
    LCD lcd{};

    mem.init();
    ppu.init();
    lcd.init();

    cpu.load_bootup("dmg_boot.bin", mem);

    u32 cycles = 0;
    while (1) {
        if (!lcd.is_full_empty()) {
            //mem.dump("dump.bin");
            //std::cout << cpu.PC;
            lcd.debug();
        }
        u32 c = cpu.execute(mem);
        timers.update(c, mem);
        ppu.update(c * 4, mem, lcd);
        cycles += c;
    }

    return 0;
}
