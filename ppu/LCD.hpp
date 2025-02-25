#pragma once

class LCD {
    static constexpr int DISPLAY_WIDTH = 160;
    static constexpr int DISPLAY_HEIGHT = 144;
    Byte display[DISPLAY_HEIGHT][DISPLAY_WIDTH] = {};

    int pos = 0;

public:
    void init() {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                display[y][x] = 0;
            }
        }
    }

    void push(Pixel pixel) {
        int y = pos / DISPLAY_WIDTH;
        int x = pos % DISPLAY_WIDTH;

        display[y][x] = pixel.color;
        pos++;
    }

    void reset() {
        pos = 0;
    }

    void debug() {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                Byte value = display[y][x];
                if (value == 0)
                    std::cout << " ";
                else
                    printf("%i", value);
            }
            std::cout << std::endl;
        }
    }

    bool is_full_empty() const {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                if (display[y][x] != 0)
                    return false;
            }
        }
        return true;
    }
};