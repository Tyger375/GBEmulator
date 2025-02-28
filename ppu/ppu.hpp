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
    void init();

    void oam_scan(u32 cycles, Memory& mem);

    // Background / Window processing
    void background_fetch_tile_number(Memory&);
    void background_fetch_tile_data_low(Memory&);
    void background_fetch_tile_data_high(Memory&);
    void decode_background_tile(Pixel*, Memory&) const;
    void background_push_tile_data(Memory&);

    void draw(u32, Memory&);
    void pop_and_mix_to_lcd(u32, LCD&);

    /**
     *
     * @param cycles T-Cycles
     * @param mem Memory reference
     * @param lcd LCD reference
     */
    void update(u32, Memory&, LCD&);
};
