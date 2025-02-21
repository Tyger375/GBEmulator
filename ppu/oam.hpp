#pragma once

namespace OAM {
    static constexpr Word LCDC_REG = 0xFF40;
    static constexpr Word OAM = 0xFE00;
    static constexpr Word OAM_SIZE = 0x9F / 4;

    struct Sprite {
        Byte y_pos;
        Byte x_pos;
        Byte tile_number;
        Byte flags;
    };

    Sprite fetch_sprite(Word index, Memory& mem) {
        return {
            mem[index],
            mem[index+1],
            mem[index+2],
            mem[index+3]
        };
    }

    bool scan_search(const Byte LY, Memory& mem, Sprite* s) {
        const u32 sprite_height = (mem[LCDC_REG] & 0b100) ? 16 : 8;

        for (u32 i = 0; i < OAM_SIZE; ++i) {
            Sprite sprite = fetch_sprite(OAM + i * 4, mem);

            if (
                sprite.x_pos > 0 &&
                LY + 16 >= sprite.y_pos &&
                LY + 16 < sprite.y_pos + sprite_height
                ) {
                *s = sprite;
                return true;
            }
        }

        return false;
    }
}