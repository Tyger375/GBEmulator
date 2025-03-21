#pragma once
#include "../defs.hpp"
#include <fstream>
#include <iostream>

struct Memory {
private:
    static constexpr u32 MAX_MEM = 64 * 1024;
    Byte Data[MAX_MEM] = {};
public:
    void init();

    Byte operator[](u32 addr) const;
    Byte& operator[](u32 addr);

    /**
     * Dumps all the memory in a file,
     * used for debugging purposes
     * */
    void dump(const char* filename);
};


