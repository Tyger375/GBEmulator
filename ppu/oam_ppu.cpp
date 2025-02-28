#include "ppu.hpp"

void PPU::oam_scan(u32 cycles, Memory& mem) {
    const u32 sprite_height = (mem[LCDC_REG] & 0b100) ? 16 : 8;

    // Every step completed every 2 T-Cycles
    for (u32 i = 0; i < cycles / 2; ++i) {
        if (sprites_buffer.size() >= 10) return;

        Byte LY = mem[LY_REG];

        Word index = VideoUtils::OAM::OAM + i * 4;

        VideoUtils::OAM::Sprite sprite = VideoUtils::OAM::fetch_sprite(index, mem);

        if (
                sprite.x_pos > 0 &&
                LY + 16u >= sprite.y_pos &&
                LY + 16u < sprite.y_pos + sprite_height
                ) {
            sprites_buffer.push_back(sprite);
        }

        total_cycles += 2;

        if (total_cycles >= 80) {
            total_cycles = 0;
            mode = 3;
            drawing_step = 1;

            return;
        }
    }
}