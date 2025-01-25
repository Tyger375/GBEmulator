#include "../defs.hpp"

class Timers {
    Word DIV;
    static constexpr Word DIV_REG = 0xFF04;

    void update(u32 cycles, Memory& mem) {
        if (mem[DIV_REG] == 0)
            DIV = 0;

        DIV += cycles;
        mem[DIV_REG] = (DIV >> 8) & 0x0F;
    }
}
