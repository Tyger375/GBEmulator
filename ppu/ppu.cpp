#include "ppu.hpp"

void PPU::init() {
    mode = 2;
    total_cycles = 0;
}

void PPU::draw(u32 cycles, Memory& mem) {
    for (u32 i = 0; i < cycles / 2; ++i) {
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
}

void PPU::pop_and_mix_to_lcd(u32 cycles, LCD& lcd) {
    for (u32 i = 0; i < cycles; ++i) {
        if (background_fifo.is_empty()) return;

        Pixel pixel = background_fifo.pop();
        lcd.push(pixel);
        pops++;
    }
}

void PPU::update(u32 cycles, Memory& mem, LCD& lcd) {
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
                        background_fifo.empty();
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