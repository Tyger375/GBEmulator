# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(GBEmulator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
set(SDL3_DIR C:/SDL3-3.2.4/cmake)
find_package(SDL3 REQUIRED)

# Include SDL2 headers
include_directories(${SDL3_INCLUDE_DIRS})

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
        ppu/LCD.hpp
        ppu/fifo.hpp
        profiling/profiling.hpp
)

target_link_libraries(GBEmulator ${SDL3_LIBRARIES})