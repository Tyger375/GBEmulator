#include "ppu.hpp"

void PPU::background_fetch_tile_number(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x1) == 0) {
        drawing_step++;
        return;
    }

    bool window_enable = (LCDC & 0b100000) > 0;
    Byte LY = mem[LY_REG];
    Byte WY = mem[WY_REG];

    if (window_enable && LY >= WY) {
        // Window tile
        // TODO
        Word window_tile_area = (LCDC & 0b1000000) > 0 ? 0x9C00 : 0x9800;
        Word addr = window_tile_area + x_pos_counter + 32 * (window_line_counter / 8);
        background_tile_number = mem[addr];
        //std::cout << "WINDOW TILE AREA" << std::endl;
    } else {
        // Background tile

        Byte SCY = mem[SCY_REG];
        Byte SCX = mem[SCX_REG];

        Word background_tile_area = (LCDC & 0b1000) > 0 ? 0x9C00 : 0x9800;
        Word addr = background_tile_area;
        Byte X = ((SCX / 8) + x_pos_counter) & 0x1F;
        Byte Y = ((LY + SCY) / 8) & 0x1F;
        addr += X + Y * 32;
        background_tile_number = mem[addr];
    }

    drawing_step++;
}

void PPU::background_fetch_tile_data_low(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x1) == 0) {
        drawing_step++;
        return;
    }

    Byte LY = mem[LY_REG];
    Byte SCY = mem[SCY_REG];

    bool unsigned_method = ((LCDC & 0b10000) > 0);
    Word addr = unsigned_method ? 0x8000 : 0x8800;

    if (unsigned_method) {
        addr += static_cast<unsigned int>(background_tile_number) * 16;
    } else {
        addr += static_cast<signed int>(background_tile_number) * 16;
    }
    addr += 2 * ((LY + SCY) % 8);

    background_tile_number = addr;
    tile_data_low = mem[addr];
    drawing_step++;
}

void PPU::background_fetch_tile_data_high(Memory& mem) {
    Byte LCDC = mem[LCDC_REG];

    if ((LCDC & 0x1) == 0) {
        drawing_step++;
        return;
    }

    tile_data_high = mem[background_tile_number + 1];
    drawing_step++;
    // TODO: reset if first iteration
}

void PPU::decode_background_tile(Pixel* pixels, Memory& mem) const {
    for (int i = 0; i < 8; ++i) {
        Byte mask = 1 << (7 - i);
        Byte first = (tile_data_low & mask) > 0;
        Byte second = (tile_data_high & mask) > 0;

        Byte BGP = mem[BGP_REG];
        pixels[i] = {first + second, BGP, 0};
    }
}

void PPU::background_push_tile_data(Memory& mem) {
    if (!background_fifo.is_empty()) return;

    Pixel pixels[8];
    decode_background_tile(pixels, mem);
    background_fifo.push(pixels);

    drawing_step = 1;
    x_pos_counter++;

    if (x_pos_counter >= 20) {
        mode = 0;
        x_pos_counter = 0;
    }
}

void PPU::background_draw(Memory& mem) {
    if (sprites_drawing_step > 1) return;

    switch (drawing_step) {
        case 1: {
            background_fetch_tile_number(mem);
            break;
        }
        case 2: {
            background_fetch_tile_data_low(mem);
            break;
        }
        case 3: {
            background_fetch_tile_data_high(mem);
            break;
        }
        case 4: {
            background_push_tile_data(mem);
            break;
        }
        default: return;
    }
}