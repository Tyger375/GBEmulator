#include "timers.hpp"

void Timers::update(u32 cycles, Memory& mem) {
    for (u32 i = 0; i < cycles * 4; ++i) {
        if (mem[DIV_REG] != ((DIV >> 8) & 0xFF))
            DIV = 0;

        DIV++;
        mem[DIV_REG] = (DIV >> 8) & 0xFF;

        if (!tima_overflow) {
            Byte tac = mem[TAC_REG];
            bool timer_enable = tac & 0b100;
            bool div_bit = false;
            switch (tac & 0b11) {
                case 0: {
                    div_bit = DIV & 0x200;
                    break;
                }
                case 1: {
                    div_bit = DIV & 0b1000;
                    break;
                }
                case 2: {
                    div_bit = DIV & 0b100000;
                    break;
                }
                case 3: {
                    div_bit = DIV & 0b10000000;
                    break;
                }
                default: break;
            }

            const bool ANDed = div_bit & timer_enable;
            if (last_ANDed && !ANDed) {
                const Byte tima_value = ++mem[TIMA_REG];
                if (tima_value == 0) {
                    tima_overflow = true;
                }
            }
            last_ANDed = ANDed;
        } else {
            tima_overflow_cycles++;

            if (tima_overflow_cycles == 4) {
                mem[TIMA_REG] = mem[TMA_REG];
                mem[IF_REG] |= 1 << 2; // Calling interrupt
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