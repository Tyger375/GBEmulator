cmake_minimum_required(VERSION 3.10)
project(GBEmulator CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 75 86)
cmake_policy(SET CMP0104 NEW)

set(SDL3_DIR C:/SDL/build)
find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_executable(GBEmulator
        main.cpp
        defs.hpp

        cpu/cpu.hpp
        cpu/cpu.cpp
        cpu/cpu_utils.cpp
        cpu/cpu_ops.cpp
        cpu/cpu_loads.cpp
        cpu/interrupts.cpp

        ppu/ppu.hpp
        ppu/ppu.cpp
        ppu/bg_ppu.cpp
        ppu/oam_ppu.cpp
        ppu/LCD/LCD.hpp
        ppu/LCD/LCD.cpp
        ppu/FIFO/FIFO.hpp
        ppu/FIFO/FIFO.cpp
        ppu/utils/utils.hpp
        ppu/utils/utils.cpp
        ppu/gpu/gpu.cu
        ppu/gpu/gpu.cuh

        timers/timers.hpp
        timers/timers.cpp

        memory/memory.hpp
        memory/memory.cpp

        profiling/profiling.hpp

        dma/dma.cpp
        dma/dma.hpp
        joypad/joypad.hpp
)

set_target_properties(GBEmulator PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(GBEmulator SDL3::SDL3)