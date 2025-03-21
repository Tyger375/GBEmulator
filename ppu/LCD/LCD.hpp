#pragma once
#include "../utils/utils.hpp"
#include "../FIFO/FIFO.hpp"

class LCD {
    Byte* display = nullptr;

    int pos = 0;
public:
    void init();

    inline Byte* get_display() const { return display; }
    inline bool is_ready() const { return pos >= (DISPLAY_WIDTH * DISPLAY_HEIGHT) - 1; }

    void push(Pixel pixel);
    void reset();
};