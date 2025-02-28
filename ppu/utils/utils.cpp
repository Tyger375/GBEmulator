#include "utils.hpp"

Byte VideoUtils::palette_to_color(Pixel pixel)  {
    switch (pixel.color) {
        case 0: {
            return pixel.palette & 0b11;
        }
        case 1: {
            return (pixel.palette >> 2) & 0b11;
        }
        case 2: {
            return (pixel.palette >> 4) & 0b11;
        }
        case 3: {
            return (pixel.palette >> 6) & 0b11;
        }
    }
    return 0;
}

Uint32 VideoUtils::color_to_rgb(const SDL_PixelFormatDetails* format, Byte color)  {
    switch (color) {
        case 0: {
            return SDL_MapRGB(format, nullptr, 255, 255, 255);
        }
        case 1: {
            return SDL_MapRGB(format, nullptr, 169, 169, 169);
        }
        case 2: {
            return SDL_MapRGB(format, nullptr, 84, 84, 84);
        }
        case 3: {
            return SDL_MapRGB(format, nullptr, 0, 0, 0);
        }
        default: return SDL_MapRGB(format, nullptr, 255, 255, 255);
    }
}

VideoUtils::OAM::Sprite VideoUtils::OAM::fetch_sprite(Word index, Memory &mem)  {
    return {
            mem[index],
            mem[index+1],
            mem[index+2],
            mem[index+3]
    };
}