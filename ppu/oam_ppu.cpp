#include "ppu.hpp"

void PPU::oam_scan(u32 cycles, Memory& mem) {
    const u32 sprite_height = (mem[LCDC_REG] & 0b100) ? 16 : 8;

    // Every step completed every 2 T-Cycles
    for (u32 i = 0; i < cycles / 2; ++i) {
        if (sprites_buffer.size() < 10) {
            Byte LY = mem[LY_REG];

            Word index = VideoUtils::OAM::OAM + (total_cycles / 2) * 4;

            VideoUtils::OAM::Sprite sprite = VideoUtils::OAM::fetch_sprite(index, mem);

            if (
                    sprite.x_pos > 0 &&
                    LY + 16u >= sprite.y_pos &&
                    LY + 16u < sprite.y_pos + sprite_height
                    ) {
                sprites_buffer.push_back(sprite);
            }
        }

        total_cycles += 2;

        if (total_cycles >= 80) {
            total_cycles = 0;
            mode = 3;

            background_fifo.empty();
            oam_fifo.empty();

            drawing_step = 1;
            sprites_drawing_step = 1;

            return;
        }
    }
}

void PPU::sprites_fetch_tile_number(Memory& mem) {
    if (background_fifo.is_empty()) return;

    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x2) == 0) {
        return;
    }

    bool found = false;
    VideoUtils::OAM::Sprite sprite{};
    for (auto s : sprites_buffer) {
        if (s.x_pos == (x_pos_counter * 8)) {
            found = true;
            sprite = s;
            drawing_step = 1;
            break;
        }
    }

    if (!found) {
        return;
    }

    sprite_tile_number = sprite.tile_number;
    sprites_drawing_step++;
}

void PPU::sprites_fetch_tile_data_low(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x2) == 0) {
        sprites_drawing_step++;
        return;
    }

    Byte LY = mem[LY_REG];
    Byte SCY = mem[SCY_REG];

    Word addr = 0x8000;
    addr += static_cast<unsigned int>(sprite_tile_number) * 16;
    addr += 2 * ((LY + SCY) % 8);

    sprite_tile_number = addr;
    sprite_tile_data_low = mem[addr];
    sprites_drawing_step++;
}

void PPU::sprites_fetch_tile_data_high(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x2) == 0) {
        sprites_drawing_step++;
        return;
    }

    sprite_tile_data_high = mem[sprite_tile_number + 1];
    sprites_drawing_step++;
}

void PPU::decode_sprite_tile(Pixel* pixels, Memory& mem) const {
    for (int i = 0; i < 8; ++i) {
        Byte mask = 1 << (7 - i);
        Byte first = (sprite_tile_data_low & mask) > 0;
        Byte second = (sprite_tile_data_high & mask) > 0;

        Byte BGP = mem[BGP_REG];
        pixels[i] = {first + second, BGP, 1};
    }
}

void PPU::sprites_push_tile_data(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x2) == 0) {
        sprites_drawing_step = 1;
        return;
    }

    if (!oam_fifo.is_empty()) {
        sprites_drawing_step = 1;
        return;
    }

    Pixel pixels[8];
    decode_sprite_tile(pixels, mem);
    oam_fifo.push(pixels);

    sprites_drawing_step = 1;
}

void PPU::sprites_draw(Memory& mem) {
    switch (sprites_drawing_step) {
        case 1: {
            sprites_fetch_tile_number(mem);
            break;
        }
        case 2: {
            sprites_fetch_tile_data_low(mem);
            break;
        }
        case 3: {
            sprites_fetch_tile_data_high(mem);
            break;
        }
        case 4: {
            sprites_push_tile_data(mem);
            break;
        }
        default: return;
    }
}