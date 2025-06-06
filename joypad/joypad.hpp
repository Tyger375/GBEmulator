#pragma once
#include <iostream>
#include <SDL3/SDL_events.h>
#include "../defs.hpp"
#include "../memory/memory.hpp"

class Joypad {
    static constexpr Word JOYPAD_REG = 0xFF00;
    static constexpr Word IF_REG = 0xFF0F;

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    bool start = false;
    bool select = false;

    bool A = false;
    bool B = false;

    Byte old_values = 0xFF;
public:
    bool keyboard_event(const SDL_Event&);
    static bool high_to_low_transition(Byte first, Byte second, u32 bit);
    static bool is_interrupt(Byte current, Byte old);

    void update(Memory& mem);
};