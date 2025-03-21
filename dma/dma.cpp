#include "dma.hpp"

void DMA::transfer(u32 cycles, Memory& mem) {
    for (u32 i = 0; i < cycles; ++i) {
        Byte DMA = mem[DMA_REG];

        Word addr = (DMA << 8) + transfer_pos;
        Word dest = 0xFE00 + transfer_pos;

        mem[dest] = mem[addr];
        transfer_pos++;

        if (transfer_pos > 0x9F) {
            transferring = false;
            mem[DMA_REG] = 0x00;
            return;
        }
    }
}

void DMA::update(u32 cycles, Memory& mem) {
    for (u32 i = 0; i < cycles; ++i) {
        Byte DMA = mem[DMA_REG];
        if (DMA != 0x00 && DMA <= 0xDF && !transferring) {
            transferring = true;
            transfer_pos = 0;
            continue;
        }

        if (transferring)
            transfer(1, mem);
    }
}