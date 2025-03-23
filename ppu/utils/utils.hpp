#pragma once

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_pixels.h>
#include "../../defs.hpp"
#include "../../memory/memory.hpp"
#include "../FIFO/FIFO.hpp"

namespace VideoUtils {
    Uint32 color_to_rgb(const SDL_PixelFormatDetails*, Byte);
    Byte palette_to_color(Pixel pixel);

    namespace OAM {
        static constexpr Word LCDC_REG = 0xFF40;
        static constexpr Word OAM = 0xFE00;
        static constexpr Word OAM_SIZE = 0x9F / 4;

        struct Sprite {
            Byte id;
            Word y_pos;
            Word x_pos;
            Byte tile_number;
            Byte flags;
        };

        Sprite fetch_sprite(Word index, Memory& mem);
    }
}