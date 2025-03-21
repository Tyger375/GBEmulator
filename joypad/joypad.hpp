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
    bool keyboard_event(SDL_Event event) {
        if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP) return false;
        bool new_value = event.key.down;

        switch (event.key.key) {
            case SDLK_A: {
                A = new_value;
                break;
            }
            case SDLK_B: {
                B = new_value;
                break;
            }

            case SDLK_T: {
                start = new_value;
                break;
            }
            case SDLK_Y: {
                select = new_value;
                break;
            }

            case SDLK_UP: {
                up = new_value;
                break;
            }
            case SDLK_DOWN: {
                down = new_value;
                break;
            }
            case SDLK_LEFT: {
                left = new_value;
                break;
            }
            case SDLK_RIGHT: {
                right = new_value;
                break;
            }
            default: {
                return false;
            }
        }
        return true;
    }

    static bool high_to_low_transition(Byte first, Byte second, u32 bit) {
        bool first_bit = (first & (1 << bit)) > 0;
        bool second_bit = (second & (1 << bit)) > 0;
        return first_bit && !second_bit;
    }

    static bool is_interrupt(Byte current, Byte old) {
        return
                high_to_low_transition(old, current, 0) ||
                high_to_low_transition(old, current, 1) ||
                high_to_low_transition(old, current, 2) ||
                high_to_low_transition(old, current, 3);
    }

    void update(Memory& mem) {
        Byte Joypad = mem[JOYPAD_REG];

        Byte values = 0x0;
        bool select_buttons = (Joypad & 0b100000) == 0;
        bool select_dpad    = (Joypad & 0b10000) == 0;

        if (select_buttons) {
            values |= (!start) << 3;
            values |= (!select) << 2;
            values |= (!B) << 1;
            values |= !A;
        }

        if (select_dpad) {
            values |= (!down) << 3;
            values |= (!up) << 2;
            values |= (!left) << 1;
            values |= !right;
        }

        if (!select_buttons && !select_dpad)
            values = 0xF;

        Joypad |= values;
        mem[JOYPAD_REG] = Joypad;

        if (is_interrupt(Joypad, old_values)) {
            mem[IF_REG] |= 1 << 4; // Calling interrupt
        }

        old_values = Joypad;
    }
};