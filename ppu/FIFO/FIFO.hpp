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
    inline bool is_empty() const { return fifo.empty();}

    void empty();
    void push(Pixel pixel[]);
    Pixel pop();
};