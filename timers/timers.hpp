#pragma once

#include "../defs.hpp"
#include "../memory/memory.hpp"

class Timers {
    Word DIV = 0;
    bool last_ANDed = false;

    bool tima_overflow = false;
    u32 tima_overflow_cycles = 0;

    static constexpr Word DIV_REG   = 0xFF04;
    static constexpr Word TIMA_REG  = 0xFF05;
    static constexpr Word TMA_REG   = 0xFF06;
    static constexpr Word TAC_REG   = 0xFF07;

    static constexpr Word IF_REG    = 0xFF0F;

public:
    void update(u32 cycles, Memory& mem);
};
