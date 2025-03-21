#pragma once

#include "../defs.hpp"
#include "../memory/memory.hpp"

class DMA {
    bool transferring = false;
    u32 transfer_pos{};

    static constexpr Word DMA_REG = 0xFF46;
public:
    void transfer(u32 cycles, Memory& mem);

    /**
     * @param cycles M-Cycles
     * @param mem Memory reference
     * */
    void update(u32 cycles, Memory& mem);

    bool is_transferring() const { return transferring; }
};