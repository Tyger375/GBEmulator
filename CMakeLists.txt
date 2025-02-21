# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(GBEmulator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add an executable target
add_executable(GBEmulator
        main.cpp
        defs.hpp

        cpu/cpu.hpp
        cpu/cpu.cpp
        cpu/cpu_ops.cpp
        cpu/interrupts.cpp

        ppu/ppu.hpp
        ppu/oam.hpp

        timers/timers.hpp

        memory/memory.hpp
)