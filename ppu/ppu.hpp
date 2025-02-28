#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "fifo.hpp"
#include "LCD.hpp"
#include "../memory/memory.hpp"

class PPU {
    int mode = 0;
    u32 total_cycles = 0;

    std::vector<VideoUtils::OAM::Sprite> sprites_buffer;

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

    static constexpr Word BGP_REG = 0xFF47;

    static constexpr Word SCY_REG = 0xFF42;
    static constexpr Word SCX_REG = 0xFF43;

    static constexpr Word WY_REG = 0xFF4A;
    static constexpr Word WX_REG = 0xFF4B;

    int pushes = 0;
    int pops = 0;

    u32 ins_for_ly = 0;
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

            Word index = VideoUtils::OAM::OAM + i * 4;

            VideoUtils::OAM::Sprite sprite = VideoUtils::OAM::fetch_sprite(index, mem);

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

    // Background / Window processing
    void background_fetch_tile_number(Memory&);
    void background_fetch_tile_data_low(Memory&);
    void background_fetch_tile_data_high(Memory&);
    void decode_background_tile(Pixel*, Memory&) const;
    void background_push_tile_data(Memory&);

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
                    background_push_tile_data(mem);
                    break;
                }
                default: break;
            }
        }
    }

    void pop_and_mix_to_lcd(u32 cycles, LCD& lcd) {
        for (u32 i = 0; i < cycles; ++i) {
            if (background_fifo.is_empty()) return;

            Pixel pixel = background_fifo.pop();
            lcd.push(pixel);
            pops++;
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

        Byte old_LY = mem[LY_REG];

        for (u32 i = 0; i < cycles / 2; ++i) {
            switch (mode) {
                case 2: {
                    oam_scan(2, mem);
                    break;
                }
                case 3: {
                    draw(2, mem);
                    break;
                }
                case 0: {
                    total_cycles += 2;
                    if (total_cycles >= 456) {
                        total_cycles = 0;
                        mem[LY_REG]++;
                        if (mem[LY_REG] >= 144) {
                            mode = 1;
                        } else {
                            mode = 2;
                        }
                        break;
                    }
                    break;
                }
                case 1: {
                    //VBlank
                    total_cycles += 2;
                    if (total_cycles >= 456) {
                        total_cycles = 0;
                        mem[LY_REG]++;
                        if (mem[LY_REG] >= 154) {
                            mem[LY_REG] = 0;
                            lcd.reset();
                            mode = 2;
                            x_pos_counter = 0;
                        }
                    }
                    break;
                }
                default: std::cerr << "Unknown mode" << std::endl;
            }
        }

        pop_and_mix_to_lcd(cycles, lcd);

        Byte LY = mem[LY_REG];
        Byte LYC = mem[LYC_REG];

        if (old_LY == LY)
            ins_for_ly++;
        else
            ins_for_ly = 0;

        Byte value = mem[LCDS_REG] & (~0b111);
        value |= (LY == LYC) << 2;
        value |= mode & 0b11;
        mem[LCDS_REG] = value;
    }
};
