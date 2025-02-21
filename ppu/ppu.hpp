#pragma once
#include "oam.hpp"
#include <iostream>
#include <vector>

class PPU {
    int mode = 0;
    u32 total_cycles = 0;

    std::vector<OAM::Sprite> sprites_buffer;

    static constexpr Word LCDC_REG = 0xFF40;
    static constexpr Word LY_REG = 0xFF44;
    static constexpr Word LYC_REG = 0xFF45;
    static constexpr Word LCDS_REG = 0xFF41;

public:
    void init() {
        mode = 2;
        total_cycles = 0;
    }

    void oam_scan(u32 cycles, Memory& mem) {
        const u32 sprite_height = (mem[LCDC_REG] & 0b100) ? 16 : 8;

        // Every step completed every 2 T-Cycles
        for (u32 i = 0; i < cycles / 2; ++i) {
            if (sprites_buffer.size() >= 10) return;

            Byte LY = mem[LY_REG];

            Word index = OAM::OAM + i * 4;

            OAM::Sprite sprite = OAM::fetch_sprite(index, mem);

            if (
                sprite.x_pos > 0 &&
                LY + 16 >= sprite.y_pos &&
                LY + 16 < sprite.y_pos + sprite_height
                ) {
                sprites_buffer.push_back(sprite);
            }

            total_cycles += 2;

            if (total_cycles >= 80) {
                mode = 3;
                return;
            }
        }
    }

    /**
     *
     * @param cycles T-Cycles
     * @param mem Memory
     */
    void update(u32 cycles, Memory& mem) {
        Byte LCDC = mem[LCDC_REG];
        if ((LCDC & 0x80) == 0) return;

        switch (mode) {
            case 2: {
                oam_scan(cycles, mem);
                break;
            }
            default: std::cerr << "Unknown mode" << std::endl;
        }

        Byte LY = mem[LY_REG];
        Byte LYC = mem[LYC_REG];

        Byte value = mem[LCDS_REG] & (~0b111);
        value |= (LY == LYC) << 2;
        value |= mode & 0b11;
        mem[LCDS_REG] = value;
    }
};
