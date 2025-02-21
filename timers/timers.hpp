#include "../defs.hpp"

class Timers {
    Word DIV;
    bool last_anded = 0;

    bool tima_overflow = false;
    u32 tima_overflow_cycles = 0;

    static constexpr Word DIV_REG   = 0xFF04;
    static constexpr Word TIMA_REG  = 0xFF05;
    static constexpr Word TMA_REG   = 0xFF06;
    static constexpr Word TAC_REG   = 0xFF07;

    void update(u32 cycles, Memory& mem) {
        for (u32 i = 0; i < cycles; ++i) {
            if (mem[DIV_REG] != ((DIV >> 8) & 0x0F))
                DIV = 0;

            DIV += i;
            mem[DIV_REG] = (DIV >> 8) & 0x0F;

            if (!tima_overflow) {
                Byte tac = mem[TAC_REG];
                bool timer_enable = tac & 0b100;
                bool div_bit = false;
                switch (tac & 0b11) {
                    case 0: {
                        div_bit = DIV & 0x100;
                        break;
                    }
                    case 1: {
                        div_bit = DIV & 0b100;
                        break;
                    }
                    case 2: {
                        div_bit = DIV & 0b10000;
                        break;
                    }
                    case 3: {
                        div_bit = DIV & 0b1000000;
                        break;
                    }
                    default: break;
                }

                bool anded = div_bit & timer_enable;
                if (last_anded && !anded) {
                    Byte tima_value = mem[TIMA_REG]++;
                    if (tima_value == 0) {
                        tima_overflow = true;
                    }
                }
            } else {
                tima_overflow_cycles++;

                if (tima_overflow_cycles == 4) {
                    mem[TIMA_REG] = mem[TMA_REG];
                    //TODO: call interrupt
                    tima_overflow = false;
                    tima_overflow_cycles = 0;
                } else {
                    if (mem[TIMA_REG] != 0) {
                        // overflow aborted
                        tima_overflow = false;
                        tima_overflow_cycles = 0;
                    }
                }
            }
        }
    }
}
