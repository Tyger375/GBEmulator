#pragma once
#include "oam.hpp"
#include <iostream>
#include <vector>
#include <queue>

#include "fifo.hpp"
#include "LCD.hpp"

class PPU {
    int mode = 0;
    u32 total_cycles = 0;

    std::vector<OAM::Sprite> sprites_buffer;

    Word background_tile_number = 0;
    Byte tile_data_low = 0;
    Byte tile_data_high = 0;
    int drawing_step = 0;
    Byte x_pos_counter = 0;
    Byte window_line_counter = 0;

    FIFO background_fifo;
    FIFO oam_fifo;

    static constexpr Word LCDC_REG = 0xFF40;
    static constexpr Word LY_REG = 0xFF44;
    static constexpr Word LYC_REG = 0xFF45;
    static constexpr Word LCDS_REG = 0xFF41;

    static constexpr Word SCY_REG = 0xFF42;
    static constexpr Word SCX_REG = 0xFF43;

    static constexpr Word WY_REG = 0xFF4A;
    static constexpr Word WX_REG = 0xFF4B;

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
                total_cycles = 0;
                mode = 3;
                drawing_step = 1;

                return;
            }
        }
    }

    void background_fetch_tile_number(Memory& mem) {
        Byte LCDC = mem[LCDC_REG];

        if ((LCDC & 0x1) == 0)
            return;

        bool window_enable = (LCDC & 0b100000) > 0;
        Byte LY = mem[LY_REG];
        Byte WY = mem[WY_REG];

        if (window_enable && LY >= WY) {
            // Window tile
            Word window_tile_area = (LCDC & 0b1000000) > 0 ? 0x9C00 : 0x9800;
            Word addr = window_tile_area + x_pos_counter + 32 * (window_line_counter / 8);
            std::cout << "WINDOW TILE AREA" << std::endl;
        } else {
            // Background tile
            //std::cout << "BACKGROUND TILE AREA" << std::endl;

            Byte SCY = mem[SCY_REG];
            Byte SCX = mem[SCX_REG];

            Word background_tile_area = (LCDC & 0b1000) > 0 ? 0x9C00 : 0x9800;
            Word addr = background_tile_area;
            Byte X = ((SCX / 8) + x_pos_counter) & 0x1F;
            Byte Y = (LY + SCY) & 255;
            addr += X + Y * 32;
            //addr += x_pos_counter;
            //addr += (SCX / 8) & 0x1F;
            //addr += 32 * (((LY + SCY) & 0xFF) / 8);
            background_tile_number = addr;
        }

        drawing_step++;
    }

    void background_fetch_tile_data_low(Memory& mem) {
        Byte LCDC = mem[LCDC_REG];

        Byte LY = mem[LY_REG];
        Byte SCY = mem[SCY_REG];

        Word addr = background_tile_number;

        if ((LCDC & 0b10000) > 0) {
            unsigned int offset = 2 * ((LY + SCY) % 8);
            addr += offset;
        } else {
            signed int offset = 2 * ((LY + SCY) % 8);
            addr += offset;
        }
        background_tile_number = addr;
        tile_data_low = mem[addr];
        drawing_step++;
    }

    void background_fetch_tile_data_high(Memory& mem) {
        tile_data_high = mem[background_tile_number + 1];
        drawing_step++;
        // TODO: reset if first iteration
    }

    void decode_tile(Pixel* pixels) {
        for (int i = 0; i < 8; ++i) {
            Byte mask = 1 << (7 - i);
            Byte first = (tile_data_low & mask) > 0;
            Byte second = (tile_data_high & mask) > 0;

            // TODO: fix
            pixels[i] = {first + second, 0, 0};
        }
    }

    void background_push_tile_data() {
        if (!background_fifo.is_empty()) return;

        Pixel pixels[8];
        decode_tile(pixels);
        background_fifo.push(pixels);

        drawing_step = 1;
        x_pos_counter++;

        if (x_pos_counter >= 20) {
            mode = 0;
            //x_pos_counter = 0;
        }
    }

    void draw(u32 cycles, Memory& mem) {
        for (u32 i = 0; i < cycles / 2; ++i) {
            // TODO drawing

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
                    background_push_tile_data();
                    break;
                }
                default: break;
            }
        }
    }

    void pop_and_mix_to_lcd(u32 cycles, Memory& mem, LCD& lcd) {
        for (u32 i = 0; i < cycles; ++i) {
            if (background_fifo.is_empty()) return;

            Pixel pixel = background_fifo.pop();
            lcd.push(pixel);
        }
    }

    /**
     *
     * @param cycles T-Cycles
     * @param mem Memory
     */
    void update(u32 cycles, Memory& mem, LCD& lcd) {
        Byte LCDC = mem[LCDC_REG];
        if ((LCDC & 0x80) == 0) return;

        switch (mode) {
            case 2: {
                oam_scan(cycles, mem);
                break;
            }
            case 3: {
                draw(cycles, mem);
                break;
            }
            case 0: {
                for (u32 i = 0; i < cycles / 2; ++i) {
                    total_cycles += 2;
                    if (total_cycles >= 456) {
                        total_cycles = 0;
                        mem[LY_REG]++;
                        if (mem[LY_REG] >= 144) {
                            mode = 1;
                        } else {
                            mode = 2;
                        }
                    }
                }
                break;
            }
            case 1: {
                //VBlank
                for (u32 i = 0; i < cycles / 2; ++i) {
                    total_cycles += 2;
                    if (total_cycles >= 456) {
                        total_cycles = 0;
                        mem[LY_REG]++;
                        if (mem[LY_REG] >= 154) {
                            lcd.reset();
                            mode = 2;
                            x_pos_counter = 0;
                        }
                    }
                }
                break;
            }
            default: std::cerr << "Unknown mode" << std::endl;
        }

        pop_and_mix_to_lcd(cycles, mem, lcd);

        Byte LY = mem[LY_REG];
        Byte LYC = mem[LYC_REG];

        Byte value = mem[LCDS_REG] & (~0b111);
        value |= (LY == LYC) << 2;
        value |= mode & 0b11;
        mem[LCDS_REG] = value;
    }
};
