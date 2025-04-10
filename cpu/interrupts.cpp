#include "cpu.hpp"

bool is_vblank_int(const Byte IE, const Byte IF) {
    constexpr Byte VBLANK_MASK = 0x01;
    return IE & VBLANK_MASK && IF & VBLANK_MASK;
}

bool is_lcd_int(const Byte IE, const Byte IF) {
    constexpr Byte LCD_MASK = 0x02;
    return IE & LCD_MASK && IF & LCD_MASK;
}

bool is_timer_int(const Byte IE, const Byte IF) {
    constexpr Byte TIMER_MASK = 0x04;
    return IE & TIMER_MASK && IF & TIMER_MASK;
}

bool is_joypad_int(const Byte IE, const Byte IF) {
    constexpr Byte JOYPAD_MASK = 0x10;
    return IE & JOYPAD_MASK && IF & JOYPAD_MASK;
}

void CPU::call_int(Memory& mem, Word addr) {
    SP -= 2;
    u32 _ = 0;
    write_word(SP, PC, _, mem);
    PC = addr;
}

void CPU::ack_int(Memory& mem, int bit) {
    IME = 0;
    mem[IF_REG] &= ~(1 << bit);
}

void CPU::handle_interrupts(Memory& mem) {
    if (IME == 0)
        return;

    Byte IE = mem[IE_REG];
    Byte IF = mem[IF_REG];

    if (is_vblank_int(IE, IF)) {
        ack_int(mem, 0);
        call_int(mem, 0x0040);
        return;
    }

    bool lcd = is_lcd_int(IE, IF);
    if (lcd && !old_lcd_int_flag) {
        ack_int(mem, 1);
        call_int(mem, 0x0048);
        old_lcd_int_flag = lcd;
        return;
    }
    old_lcd_int_flag = lcd;

    if (is_timer_int(IE, IF)) {
        ack_int(mem, 2);
        call_int(mem, 0x0050);
        return;
    }

    if (is_joypad_int(IE, IF)) {
        ack_int(mem, 4);
        call_int(mem, 0x0060);
    }
}
