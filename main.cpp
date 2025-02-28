#include <chrono>
#include <iostream>
#include "memory/memory.hpp"
#include "cpu/cpu.hpp"
#include "timers/timers.hpp"
#include "ppu/ppu.hpp"
#include <SDL3/SDL.h>
#include "profiling/profiling.hpp"
#include "ppu/video.cuh"

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
    auto format = SDL_GetPixelFormatDetails(surface->format);

    cpu.load_bootup("dmg_boot.bin", mem);

    bool rendered = false;

    Profiling::TimeMeasure time_measure;

    u32 cycles = 0;
    while (1) {
        time_measure.reset();

        SDL_Event Event;
        while(SDL_PollEvent(&Event)) {
            // TODO: handle window events
        }

        // Debugging
        if (cpu.PC == 0xE9) {
            //mem.dump("dump.bin");
            //lcd.debug();
        }
        u32 c = cpu.execute(mem);
        time_measure.add_task("CPU");
        timers.update(c, mem);
        time_measure.add_task("Timers");
        ppu.update(c * 4, mem, lcd);
        time_measure.add_task("PPU");
        cycles += c;

        /*
         * TEMPORARY
         * Hard coding some logic so that I don't lose performance for now
         **/
        if (lcd.is_ready() && !lcd.is_full_empty() && !rendered) {
            auto pixels = static_cast<Uint32*>(surface->pixels);

            build_video(lcd.get_display(), DISPLAY_WIDTH, DISPLAY_HEIGHT, pixels, scale);
            rendered = true;

            SDL_UpdateWindowSurface(window);
            time_measure.add_task("Render");

            time_measure.profile();
        } else if (!lcd.is_ready()) {
            rendered = false;
        }


    }

    return 0;
}
