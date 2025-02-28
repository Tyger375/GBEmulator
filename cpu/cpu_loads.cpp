#include <filesystem>
#include "cpu.hpp"

void CPU::load_bootup(const char *filename, Memory &mem)  {
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    if (file.is_open()) {
        for (size_t i = 0; i < 0x100; ++i) {
            Byte value = 0;
            file.read((char*)&value, sizeof(char));
            mem[i] = value;
        }
    } else {
        std::cerr << "Failed to open file " << filename << std::endl;
    }
    file.close();
    is_boot = true;
}

void CPU::load_rom(const char *filename, Memory &mem) {
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);

    if (file.is_open()) {
        uintmax_t size = std::filesystem::file_size(filename);
        std::cout << "ROM size: " << size << std::endl;
        for (size_t i = 0; i < size; ++i) {
            Byte value = 0;
            file.read((char*)&value, sizeof(char));

            if (i < 0x100)
                rom_first[i] = value;
            else
                mem[i] = value;
        }
    } else {
        std::cerr << "Failed to open file " << filename << std::endl;
    }
    file.close();
}