#include <chrono>
#include <iostream>
#include "cpu/cpu.hpp"
#include "timers/timers.hpp"
#include "ppu/ppu.hpp"
#include <SDL3/SDL.h>

#include "profiling/profiling.hpp"

long long measure_time(std::chrono::time_point<std::chrono::system_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

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

    SDL_Window* window = SDL_CreateWindow(
        "GBEmulator",
        160, 144,
        SDL_WINDOW_OPENGL
        );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    auto palette = SDL_GetSurfacePalette(surface);
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
            for (int y = 0; y < 144; ++y) {
                for (int x = 0; x < 160; ++x) {
                    Byte b = lcd.get(x, y);
                    Uint32 color = SDL_MapRGB(format, palette, b > 0 ? 255 : 0, 0, 0);  // Red color
                    pixels[y * surface->w + x] = color;
                }
            }
            rendered = true;

            SDL_UpdateWindowSurface(window);
            time_measure.add_task("Render");

            // time_measure.profile();
        } else if (!lcd.is_ready()) {
            rendered = false;
        }


    }

    return 0;
}
