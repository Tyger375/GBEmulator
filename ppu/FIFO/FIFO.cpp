#include "FIFO.hpp"

void FIFO::empty()  {
    while (!fifo.empty()) {
        fifo.pop();
    }
}

void FIFO::push(Pixel pixel[]) {
    for (int i = 0; i < 8; ++i) {
        fifo.push(pixel[i]);
    }
}

Pixel FIFO::pop() {
    Pixel pixel = fifo.front();
    fifo.pop();
    return pixel;
}