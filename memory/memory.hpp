#pragma once
#include "../defs.hpp"

struct Memory {
private:
    static constexpr u32 MAX_MEM = 64 * 1024;
    Byte Data[MAX_MEM] = {};

public:
    void init() {
        for (int i = 0; i < MAX_MEM; ++i) {
            Data[i] = 0;
        }
    }

    Byte operator[](u32 addr) const {
        return Data[addr];
    }

    Byte& operator[](u32 addr) {
        return Data[addr];
    }
};


