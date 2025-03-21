#include "LCD.hpp"

void LCD::init() {
    display = (Byte*)malloc(sizeof(Byte) * (DISPLAY_WIDTH * DISPLAY_HEIGHT));

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            display[y * DISPLAY_WIDTH + x] = 0;
        }
    }
}

void LCD::push(Pixel pixel) {
    display[pos++] = VideoUtils::palette_to_color(pixel);
}

void LCD::reset() {
    pos = 0;
}