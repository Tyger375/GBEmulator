cmake_minimum_required(VERSION 3.10)
project(GBEmulator CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 75 86)
cmake_policy(SET CMP0104 NEW)

set(SDL3_DIR C:/SDL3-3.2.4/cmake)
find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_executable(GBEmulator
        main.cpp
        defs.hpp

        cpu/cpu.hpp
        cpu/cpu_utils.cpp
        cpu/cpu_ops.cpp
        cpu/cpu_loads.cpp
        cpu/interrupts.cpp

        ppu/ppu.hpp
        ppu/LCD.hpp
        ppu/fifo.hpp
        ppu/bg_ppu.cpp
        ppu/utils/utils.hpp
        ppu/utils/utils.cpp
        ppu/gpu/gpu.cu
        ppu/gpu/gpu.cuh

        timers/timers.hpp

        memory/memory.hpp

        profiling/profiling.hpp
        memory/memory.cpp
        cpu/cpu.cpp
        ppu/oam_ppu.cpp
        ppu/ppu.cpp
        timers/timers.cpp
)

set_target_properties(GBEmulator PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(GBEmulator ${SDL3_LIBRARIES})