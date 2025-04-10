#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "FIFO/FIFO.hpp"
#include "LCD/LCD.hpp"
#include "../memory/memory.hpp"

class PPU {
    int mode = 0;
    u32 total_cycles = 0;

    u32 frames_count = 0;

    std::vector<VideoUtils::OAM::Sprite> sprites_buffer;

    Word x_pos_counter = 0;

    Word background_tile_number = 0;
    Byte tile_data_low = 0;
    Byte tile_data_high = 0;
    int drawing_step = 0;
    Byte window_line_counter = 0;

    Word sprite_tile_number = 0;
    Byte sprite_tile_data_low = 0;
    Byte sprite_tile_data_high = 0;
    int sprites_drawing_step = 0;

    FIFO background_fifo;
    FIFO oam_fifo;

    static constexpr Word IF_REG = 0xFF0F;

    static constexpr Word LCDC_REG = 0xFF40;
    static constexpr Word LY_REG = 0xFF44;
    static constexpr Word LYC_REG = 0xFF45;
    static constexpr Word LCDS_REG = 0xFF41;

    static constexpr Word BGP_REG = 0xFF47;

    static constexpr Word SCY_REG = 0xFF42;
    static constexpr Word SCX_REG = 0xFF43;

    static constexpr Word WY_REG = 0xFF4A;
    static constexpr Word WX_REG = 0xFF4B;
public:
    void init();

    // Sprites processing
    void sprites_draw(Memory&);
    void oam_scan(u32, Memory&);
    void sprites_fetch_tile_number(Memory&);
    void sprites_fetch_tile_data_low(Memory&);
    void sprites_fetch_tile_data_high(Memory&);
    void decode_sprite_tile(Pixel*, Memory&) const;
    void sprites_push_tile_data(Memory&);

    // Background / Window processing
    void background_draw(Memory&);
    void background_fetch_tile_number(Memory&);
    void background_fetch_tile_data_low(Memory&);
    void background_fetch_tile_data_high(Memory&);
    void decode_background_tile(Pixel*, Memory&) const;
    void background_push_tile_data(Memory&);

    void draw(u32, Memory&);
    void pop_and_mix_to_lcd(u32, LCD&);

    static void request_stat_interrupt(Memory&);

    /**
     *
     * @param cycles T-Cycles
     * @param mem Memory reference
     * @param lcd LCD reference
     */
    void update(u32, Memory&, LCD&);

    int get_mode() const { return mode; }
};
