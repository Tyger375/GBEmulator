#pragma once
#include "utils/utils.hpp"

class LCD {
    Byte* display = nullptr;

    int pos = 0;

    /*
     * TEMPORARY
     * Hard coding some logic so that I don't lose performance for now
     **/
    bool is_empty = true;
public:
    void init() {
        display = (Byte*)malloc(sizeof(Byte) * (DISPLAY_WIDTH * DISPLAY_HEIGHT));

        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                display[y * DISPLAY_WIDTH + x] = 0;
            }
        }
    }

    Byte get(int x, int y) const {
        return display[y * DISPLAY_WIDTH + x];
    }

    Byte* get_display() const { return display; }

    void push(Pixel pixel) {
        display[pos] = VideoUtils::palette_to_color(pixel);

        // Debugging (enhancing performances)
        if (pixel.color > 0)
            is_empty = false;
        pos++;
    }

    bool is_ready() const { return pos >= (DISPLAY_WIDTH * DISPLAY_HEIGHT) - 1; }

    void reset() {
        pos = 0;
        is_empty = true;
    }

    void debug() {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                Byte value = display[y * DISPLAY_WIDTH + x];
                if (value == 0)
                    std::cout << " ";
                else
                    printf("%i", value);
            }
            std::cout << std::endl;
        }
    }

    bool is_full_empty() const {
        return is_empty;
        /*for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                if (display[y][x] != 0)
                    return false;
            }
        }
        return true;*/
    }
};