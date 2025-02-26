#pragma once

class LCD {
    static constexpr int DISPLAY_WIDTH = 160;
    static constexpr int DISPLAY_HEIGHT = 144;
    Byte display[DISPLAY_HEIGHT][DISPLAY_WIDTH] = {};

    int pos = 0;

    /*
     * TEMPORARY
     * Hard coding some logic so that I don't lose performance for now
     **/
    bool is_empty = true;
public:
    void init() {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                display[y][x] = 0;
            }
        }
    }

    Byte get(int x, int y) const {
        return display[y][x];
    }

    void push(Pixel pixel) {
        int y = pos / DISPLAY_WIDTH;
        int x = pos % DISPLAY_WIDTH;

        display[y][x] = pixel.color;

        // Debugging (enhancing performances)
        if (pixel.color > 0) is_empty = false;
        pos++;
    }

    bool is_ready() { return pos >= (DISPLAY_WIDTH * DISPLAY_HEIGHT) - 1; }

    void reset() {
        pos = 0;
        is_empty = true;
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