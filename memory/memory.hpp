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

    void dump(const char* filename) {
        std::ofstream file;
        file.open(filename, std::ios::out | std::ios::binary);

        if (file.is_open()) {
            for (size_t i = 0; i < MAX_MEM; ++i) {
                file << Data[i];
            }
        } else {
            std::cerr << "Failed to open file " << filename << std::endl;
        }
        file.close();
    }
};


