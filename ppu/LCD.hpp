#pragma once
#include "utils/utils.hpp"

class LCD {
    Byte* display = nullptr;

    int pos = 0;
public:
    void init() {
        display = (Byte*)malloc(sizeof(Byte) * (DISPLAY_WIDTH * DISPLAY_HEIGHT));

        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                display[y * DISPLAY_WIDTH + x] = 0;
            }
        }
    }

    Byte* get_display() const { return display; }

    void push(Pixel pixel) {
        display[pos++] = VideoUtils::palette_to_color(pixel);
    }

    bool is_ready() const { return pos >= (DISPLAY_WIDTH * DISPLAY_HEIGHT) - 1; }

    void reset() {
        pos = 0;
    }
};