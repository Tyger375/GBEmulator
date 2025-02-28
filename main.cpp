#include <chrono>
#include <iostream>
#include "memory/memory.hpp"
#include "cpu/cpu.hpp"
#include "timers/timers.hpp"
#include "ppu/ppu.hpp"
#include <SDL3/SDL.h>
#include "profiling/profiling.hpp"
#include "ppu/gpu/gpu.cuh"

#ifndef USE_PROFILING
#define USE_PROFILING false
#endif
#define PROFILE(name) if(USE_PROFILING) profiling.add_task(name)
#define RESET_PROFILING() profiling.reset()

int main() {
    Timers timers;
    Memory mem{};
    CPU cpu{};
    PPU ppu{};
    LCD lcd{};

    mem.init();
    ppu.init();
    lcd.init();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    int scale = 5;
    SDL_Window* window = SDL_CreateWindow(
        "GBEmulator",
        DISPLAY_WIDTH * scale, DISPLAY_HEIGHT * scale,
        SDL_WINDOW_OPENGL
        );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    auto pixels = static_cast<Uint32*>(surface->pixels);

    cpu.load_bootup("dmg_boot.bin", mem);
    cpu.load_rom("tetris.gb", mem);

    bool rendered = false;

    Profiling::TimeMeasure profiling;

    u32 cycles = 0;
    bool running = true;
    while (running) {
        RESET_PROFILING();

        SDL_Event Event;
        while(SDL_PollEvent(&Event)) {
            if (Event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
                break;
            }
        }

        u32 c = cpu.execute(mem);
        PROFILE("CPU");
        timers.update(c, mem);
        PROFILE("Timers");
        ppu.update(c * 4, mem, lcd);
        PROFILE("PPU");
        cycles += c;

        /*
         * TEMPORARY
         * Hard coding some logic so that I don't lose performance for now
         **/
        if (lcd.is_ready() && !rendered) {
            build_video(lcd.get_display(), DISPLAY_WIDTH, DISPLAY_HEIGHT, pixels, scale);
            rendered = true;

            SDL_UpdateWindowSurface(window);
            PROFILE("Render");
        } else if (!lcd.is_ready()) {
            rendered = false;
        }
    }

    return 0;
}
