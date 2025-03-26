#include "cpu.hpp"

Byte CPU::fetch_byte(u32 &cycles, Memory &mem)
{
    Byte value = mem[PC];
    PC++;
    cycles++;
    return value;
}

Word CPU::fetch_word(u32 &cycles, Memory &mem)
{
    Byte little = fetch_byte(cycles, mem);
    Byte big = fetch_byte(cycles, mem);
    return little | (big << 8);
}

Byte CPU::read_byte(Word addr, u32 &cycles, Memory &mem)
{
    Byte value = mem[addr];
    cycles++;
    return value;
}

void CPU::write_byte(Word addr, Byte data, u32 &cycles, Memory &mem)
{
    mem[addr] = data;
    cycles++;
}

void CPU::write_word(Word addr, Word data, u32 &cycles, Memory &mem)
{
    Byte little = data & 0x00FF;
    Byte big = (data & 0xFF00) >> 8;
    mem[addr] = little;
    mem[addr + 1] = big;
    cycles += 2;
}

Byte CPU::rlc_r(Byte data)
{
    Byte last = (data & 0x80) > 0;
    data <<= 1;
    data |= last;
    c = last;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::rrc_r(Byte data)
{
    Byte first = data & 1;
    data >>= 1;
    data |= first << 7;
    c = first;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::rl_r(Byte data)
{
    Byte last = (data & 0x80) > 0;
    data <<= 1;
    data |= c & 1;
    c = last;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::rr_r(Byte data)
{
    Byte first = data & 1;
    data >>= 1;
    data |= (c & 1) << 7;
    c = first;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::sla_r(Byte data)
{
    Byte last = (data & 0x80) > 0;
    data <<= 1;
    c = last;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::sra_r(Byte data)
{
    Byte first = data & 1;
    Byte last = (data & 0x80) > 0;
    data >>= 1;
    // Making sure it's arithmetic and not logical shifting
    if (last)
        data |= 0x80;
    else
        data &= 0x7F;

    c = first;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::srl_r(Byte data)
{
    Byte first = data & 1;
    Byte last = (data & 0x80) > 0;
    data >>= 1;
    // Making sure it's logical and not arithmetical shifting
    data &= 0x7F;

    c = first;
    z = data == 0;
    n = 0;
    h = 0;
    return data;
}

Byte CPU::swap_r(Byte data)
{
    Byte first = (data & 0xF) << 4;
    Byte last = (data >> 4) & 0xF;
    return first | last;
}

void CPU::bit_r(Byte data, Byte bit)
{
    z = (data & (1 << bit)) == 0;
    n = 0;
    h = 1;
}

Byte CPU::res_r(Byte data, Byte bit)
{
    return data & ~(1 << bit);
}

Byte CPU::set_r(Byte data, Byte bit)
{
    return data | (1 << bit);
}
