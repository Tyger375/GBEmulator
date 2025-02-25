#pragma once
#include <iostream>
#include <queue>

struct Pixel {
    int color;
    int palette;
    int background_priority;
};

class FIFO {
    std::queue<Pixel> fifo;

public:
    bool is_empty() const { return fifo.empty();}

    void empty() {
        while (!fifo.empty()) {
            fifo.pop();
        }
    }

    void push(Pixel pixel[]) {
        for (int i = 0; i < 8; ++i) {
            fifo.push(pixel[i]);
        }
    }

    Pixel pop() {
        Pixel pixel = fifo.front();
        fifo.pop();
        return pixel;
    }
};