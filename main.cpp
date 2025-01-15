#include <iostream>
#define DEBUG(byte) printf("%#02X\n", byte)

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory {
private:
    static constexpr u32 MAX_MEM = 64 * 1024;
    Byte Data[MAX_MEM];

public:
    void init() {
        for (int i = 0; i < MAX_MEM; ++i) {
            Data[i] = 0;
        }
    }

    Byte operator[](u32 addr) const {
        return Data[addr];
    }

    Byte& operator[](u32 addr) {
        return Data[addr];
    }
};

struct CPU {
    Byte A, B, C, D, E, H, L;

    Word SP;
    Word PC;

    // flags
    Byte z, n, h, c, IME;

    Byte fetch_byte(u32& cycles, Memory& mem) {
        Byte value = mem[PC];
        PC++;
        cycles++;
        return value;
    }

    Word fetch_word(u32& cycles, Memory& mem) {
        Byte little = fetch_byte(cycles, mem);
        Byte big = fetch_byte(cycles, mem);
        return little | (big << 8);
    }

    Byte read_byte(Word addr, u32& cycles, Memory& mem) {
        Byte value = mem[addr];
        cycles++;
        return value;
    }

    void write_byte(Word addr, Byte value, u32& cycles, Memory& mem) {
        mem[addr] = value;
        cycles++;
    }

    void write_word(Word addr, Word data, u32& cycles, Memory& mem) {
        Byte little = data & 0x00FF;
        Byte big = (data & 0xFF00) >> 8;
        mem[addr] = little;
        mem[addr+1] = big;
        cycles += 2;
    }

    static constexpr Byte INS_NOP = 0x00;
    // 8-BIT LOAD INSTRUCTIONS
    static constexpr Byte INS_LD_BB = 0x40;
    static constexpr Byte INS_LD_BC = 0x41;
    static constexpr Byte INS_LD_BD = 0x42;
    static constexpr Byte INS_LD_BE = 0x43;
    static constexpr Byte INS_LD_BH = 0x44;
    static constexpr Byte INS_LD_BL = 0x45;
    static constexpr Byte INS_LD_BHL = 0x46;
    static constexpr Byte INS_LD_BA = 0x47;
    static constexpr Byte INS_LD_BN = 0x06;

    static constexpr Byte INS_LD_CB = 0x48;
    static constexpr Byte INS_LD_CC = 0x49;
    static constexpr Byte INS_LD_CD = 0x4A;
    static constexpr Byte INS_LD_CE = 0x4B;
    static constexpr Byte INS_LD_CH = 0x4C;
    static constexpr Byte INS_LD_CL = 0x4D;
    static constexpr Byte INS_LD_CHL = 0x4E;
    static constexpr Byte INS_LD_CA = 0x4F;
    static constexpr Byte INS_LD_CN = 0x0E;

    static constexpr Byte INS_LD_DB = 0x50;
    static constexpr Byte INS_LD_DC = 0x51;
    static constexpr Byte INS_LD_DD = 0x52;
    static constexpr Byte INS_LD_DE = 0x53;
    static constexpr Byte INS_LD_DH = 0x54;
    static constexpr Byte INS_LD_DL = 0x55;
    static constexpr Byte INS_LD_DHL = 0x56;
    static constexpr Byte INS_LD_DA = 0x57;
    static constexpr Byte INS_LD_DN = 0x16;

    static constexpr Byte INS_LD_EB = 0x58;
    static constexpr Byte INS_LD_EC = 0x59;
    static constexpr Byte INS_LD_ED = 0x5A;
    static constexpr Byte INS_LD_EE = 0x5B;
    static constexpr Byte INS_LD_EH = 0x5C;
    static constexpr Byte INS_LD_EL = 0x5D;
    static constexpr Byte INS_LD_EHL = 0x5E;
    static constexpr Byte INS_LD_EA = 0x5F;
    static constexpr Byte INS_LD_EN = 0x1E;

    static constexpr Byte INS_LD_HB = 0x60;
    static constexpr Byte INS_LD_HC = 0x61;
    static constexpr Byte INS_LD_HD = 0x62;
    static constexpr Byte INS_LD_HE = 0x63;
    static constexpr Byte INS_LD_HH = 0x64;
    static constexpr Byte INS_LD_HL = 0x65;
    static constexpr Byte INS_LD_HHL = 0x66;
    static constexpr Byte INS_LD_HA = 0x67;
    static constexpr Byte INS_LD_HN = 0x26;

    static constexpr Byte INS_LD_LB = 0x68;
    static constexpr Byte INS_LD_LC = 0x69;
    static constexpr Byte INS_LD_LD = 0x6A;
    static constexpr Byte INS_LD_LE = 0x6B;
    static constexpr Byte INS_LD_LH = 0x6C;
    static constexpr Byte INS_LD_LL = 0x6D;
    static constexpr Byte INS_LD_LHL = 0x6E;
    static constexpr Byte INS_LD_LA = 0x6F;
    static constexpr Byte INS_LD_LN = 0x2E;

    static constexpr Byte INS_LD_HLB = 0x70;
    static constexpr Byte INS_LD_HLC = 0x71;
    static constexpr Byte INS_LD_HLD = 0x72;
    static constexpr Byte INS_LD_HLE = 0x73;
    static constexpr Byte INS_LD_HLH = 0x74;
    static constexpr Byte INS_LD_HLL = 0x75;
    static constexpr Byte INS_LD_HLA = 0x77;
    static constexpr Byte INS_LD_HLN = 0x36;

    static constexpr Byte INS_LD_AB = 0x78;
    static constexpr Byte INS_LD_AC = 0x79;
    static constexpr Byte INS_LD_AD = 0x7A;
    static constexpr Byte INS_LD_AE = 0x7B;
    static constexpr Byte INS_LD_AH = 0x7C;
    static constexpr Byte INS_LD_AL = 0x7D;
    static constexpr Byte INS_LD_AHL = 0X7E;
    static constexpr Byte INS_LD_AA = 0x7F;
    static constexpr Byte INS_LD_AN = 0x3E;

    static constexpr Byte INS_LD_BCA = 0x02;
    static constexpr Byte INS_LD_DEA = 0x12;

    static constexpr Byte INS_LD_ABC = 0x0A;
    static constexpr Byte INS_LD_ADE = 0x1A;

    static constexpr Byte INS_LD_HLIA = 0x22;
    static constexpr Byte INS_LD_HLDA = 0x32;

    static constexpr Byte INS_LD_AHLI = 0x2A;
    static constexpr Byte INS_LD_AHLD = 0x3A;

    static constexpr Byte INS_LDH_A8A = 0xE0;
    static constexpr Byte INS_LDH_AA8 = 0xF0;

    static constexpr Byte INS_LDH_CA = 0xE2;
    static constexpr Byte INS_LDH_AC = 0xF2;

    static constexpr Byte INS_LDH_A16A = 0xEA;
    static constexpr Byte INS_LDH_AA16 = 0xFA;

    // 16 BITS LOAD INSTRUCTIONS
    static constexpr Byte INS_LD_BCN16 = 0x01;
    static constexpr Byte INS_LD_DEN16 = 0x11;
    static constexpr Byte INS_LD_HLN16 = 0x21;
    static constexpr Byte INS_LD_SPN16 = 0x31;

    static constexpr Byte INS_LD_A16SP = 0x08;

    static constexpr Byte INS_LD_HLSPE8 = 0xF8;
    static constexpr Byte INS_LD_SPHL = 0xF9;

    static constexpr Byte INS_PUSH_BC = 0xC5;
    static constexpr Byte INS_PUSH_DE = 0xD5;
    static constexpr Byte INS_PUSH_HL = 0xE5;
    static constexpr Byte INS_PUSH_AF = 0xF5;

    static constexpr Byte INS_POP_BC = 0xC1;
    static constexpr Byte INS_POP_DE = 0xD1;
    static constexpr Byte INS_POP_HL = 0xE1;
    static constexpr Byte INS_POP_AF = 0xF1;

    // JUMPS / CALLS
    static constexpr Byte INS_JR = 0x18;
    static constexpr Byte INS_JR_Z = 0x28;
    static constexpr Byte INS_JR_C = 0x38;
    static constexpr Byte INS_JR_NZ = 0x20;
    static constexpr Byte INS_JR_NC = 0x30;

    static constexpr Byte INS_JP = 0xC3;
    static constexpr Byte INS_JP_HL = 0xE9;
    static constexpr Byte INS_JP_Z = 0xCA;
    static constexpr Byte INS_JP_C = 0xDA;
    static constexpr Byte INS_JP_NZ = 0xC2;
    static constexpr Byte INS_JP_NC = 0xD2;

    static constexpr Byte INS_CALL = 0xCD;
    static constexpr Byte INS_CALL_Z = 0xCC;
    static constexpr Byte INS_CALL_C = 0xDC;
    static constexpr Byte INS_CALL_NZ = 0xC4;
    static constexpr Byte INS_CALL_NC = 0xD4;

    static constexpr Byte INS_RET = 0xC9;
    static constexpr Byte INS_RET_Z = 0xC8;
    static constexpr Byte INS_RET_C = 0xD8;
    static constexpr Byte INS_RET_NZ = 0xC0;
    static constexpr Byte INS_RET_NC = 0xD0;
    static constexpr Byte INS_RETI = 0xD9;

    static constexpr Byte INS_RST_00 = 0xC7;
    static constexpr Byte INS_RST_08 = 0xCF;
    static constexpr Byte INS_RST_10 = 0xD7;
    static constexpr Byte INS_RST_18 = 0xDF;
    static constexpr Byte INS_RST_20 = 0xE7;
    static constexpr Byte INS_RST_28 = 0xEF;
    static constexpr Byte INS_RST_30 = 0xF7;
    static constexpr Byte INS_RST_38 = 0xFF;

    // 16 BITS ARITHMETICS / LOGICAL
    static constexpr Byte INS_INC_BC = 0x03;
    static constexpr Byte INS_INC_DE = 0x13;
    static constexpr Byte INS_INC_HL = 0x23;
    static constexpr Byte INS_INC_SP = 0x33;

    static constexpr Byte INS_DEC_BC = 0x0B;
    static constexpr Byte INS_DEC_DE = 0x1B;
    static constexpr Byte INS_DEC_HL = 0x2B;
    static constexpr Byte INS_DEC_SP = 0x3B;

    static constexpr Byte INS_ADD_HLBC = 0x09;
    static constexpr Byte INS_ADD_HLDE = 0x19;
    static constexpr Byte INS_ADD_HLHL = 0x29;
    static constexpr Byte INS_ADD_HLSP = 0x39;

    static constexpr Byte INS_ADD_SPE8 = 0xE8;

    // 8 BITS ARITHMETICS / LOGICAL
    static constexpr Byte INS_ADD_AB = 0x80;
    static constexpr Byte INS_ADD_AC = 0x81;
    static constexpr Byte INS_ADD_AD = 0x82;
    static constexpr Byte INS_ADD_AE = 0x83;
    static constexpr Byte INS_ADD_AH = 0x84;
    static constexpr Byte INS_ADD_AL = 0x85;
    static constexpr Byte INS_ADD_AHL = 0x86;
    static constexpr Byte INS_ADD_AA = 0x87;
    static constexpr Byte INS_ADD_AN = 0xC6;

    static constexpr Byte INS_ADC_AB = 0x88;
    static constexpr Byte INS_ADC_AC = 0x89;
    static constexpr Byte INS_ADC_AD = 0x8A;
    static constexpr Byte INS_ADC_AE = 0x8B;
    static constexpr Byte INS_ADC_AH = 0x8C;
    static constexpr Byte INS_ADC_AL = 0x8D;
    static constexpr Byte INS_ADC_AHL = 0x8E;
    static constexpr Byte INS_ADC_AA = 0x8F;
    static constexpr Byte INS_ADC_AN = 0xCE;

    static constexpr Byte INS_SUB_AB = 0x90;
    static constexpr Byte INS_SUB_AC = 0x91;
    static constexpr Byte INS_SUB_AD = 0x92;
    static constexpr Byte INS_SUB_AE = 0x93;
    static constexpr Byte INS_SUB_AH = 0x94;
    static constexpr Byte INS_SUB_AL = 0x95;
    static constexpr Byte INS_SUB_AHL = 0x96;
    static constexpr Byte INS_SUB_AA = 0x97;
    static constexpr Byte INS_SUB_AN = 0xD6;

    static constexpr Byte INS_SBC_AB = 0x98;
    static constexpr Byte INS_SBC_AC = 0x99;
    static constexpr Byte INS_SBC_AD = 0x9A;
    static constexpr Byte INS_SBC_AE = 0x9B;
    static constexpr Byte INS_SBC_AH = 0x9C;
    static constexpr Byte INS_SBC_AL = 0x9D;
    static constexpr Byte INS_SBC_AHL = 0x9E;
    static constexpr Byte INS_SBC_AA = 0x9F;
    static constexpr Byte INS_SBC_AN = 0xDE;

    static constexpr Byte INS_AND_AB = 0xA0;
    static constexpr Byte INS_AND_AC = 0xA1;
    static constexpr Byte INS_AND_AD = 0xA2;
    static constexpr Byte INS_AND_AE = 0xA3;
    static constexpr Byte INS_AND_AH = 0xA4;
    static constexpr Byte INS_AND_AL = 0xA5;
    static constexpr Byte INS_AND_AHL = 0xA6;
    static constexpr Byte INS_AND_AA = 0xA7;
    static constexpr Byte INS_AND_AN = 0xE6;

    static constexpr Byte INS_XOR_AB = 0xA8;
    static constexpr Byte INS_XOR_AC = 0xA9;
    static constexpr Byte INS_XOR_AD = 0xAA;
    static constexpr Byte INS_XOR_AE = 0xAB;
    static constexpr Byte INS_XOR_AH = 0xAC;
    static constexpr Byte INS_XOR_AL = 0xAD;
    static constexpr Byte INS_XOR_AHL = 0xAE;
    static constexpr Byte INS_XOR_AA = 0xAF;
    static constexpr Byte INS_XOR_AN = 0xEE;

    static constexpr Byte INS_OR_AB = 0xB0;
    static constexpr Byte INS_OR_AC = 0xB1;
    static constexpr Byte INS_OR_AD = 0xB2;
    static constexpr Byte INS_OR_AE = 0xB3;
    static constexpr Byte INS_OR_AH = 0xB4;
    static constexpr Byte INS_OR_AL = 0xB5;
    static constexpr Byte INS_OR_AHL = 0xB6;
    static constexpr Byte INS_OR_AA = 0xB7;
    static constexpr Byte INS_OR_AN = 0xF6;

    static constexpr Byte INS_CP_AB = 0xB8;
    static constexpr Byte INS_CP_AC = 0xB9;
    static constexpr Byte INS_CP_AD = 0xBA;
    static constexpr Byte INS_CP_AE = 0xBB;
    static constexpr Byte INS_CP_AH = 0xBC;
    static constexpr Byte INS_CP_AL = 0xBD;
    static constexpr Byte INS_CP_AHL = 0xBE;
    static constexpr Byte INS_CP_AA = 0xBF;
    static constexpr Byte INS_CP_AN = 0xFE;

    static constexpr Byte INS_INC_B = 0x04;
    static constexpr Byte INS_INC_C = 0x0C;
    static constexpr Byte INS_INC_D = 0x14;
    static constexpr Byte INS_INC_E = 0x1C;
    static constexpr Byte INS_INC_H = 0x24;
    static constexpr Byte INS_INC_L = 0x2C;
    static constexpr Byte INS_INC_PHL = 0x34;
    static constexpr Byte INS_INC_A = 0x3C;

    static constexpr Byte INS_DEC_B = 0x05;
    static constexpr Byte INS_DEC_C = 0x0D;
    static constexpr Byte INS_DEC_D = 0x15;
    static constexpr Byte INS_DEC_E = 0x1D;
    static constexpr Byte INS_DEC_H = 0x25;
    static constexpr Byte INS_DEC_L = 0x2D;
    static constexpr Byte INS_DEC_PHL = 0x35;
    static constexpr Byte INS_DEC_A = 0x3D;

    static constexpr Byte INS_DAA = 0x27;
    static constexpr Byte INS_SCF = 0x37;
    static constexpr Byte INS_CPL = 0x2F;
    static constexpr Byte INS_CCF = 0x3F;

    u32 execute(Memory& mem) {
        u32 cycles = 0;
        Byte ins = fetch_byte(cycles, mem);
        switch (ins) {
        case INS_NOP: {
            break;
        }
        case INS_LD_BB: {
            B = B;
            break;
        }
        case INS_LD_BC: {
            B = C;
            break;
        }
        case INS_LD_BD: {
            B = D;
            break;
        }
        case INS_LD_BE: {
            B = E;
            break;
        }
        case INS_LD_BH: {
            B = H;
            break;
        }
        case INS_LD_BL: {
            B = L;
            break;
        }
        case INS_LD_BHL: {
            Word addr = L | (H << 8);
            B = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_BA: {
            B = A;
            break;
        }
        case INS_LD_BN: {
            B = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_CB: {
            C = B;
            break;
        }
        case INS_LD_CC: {
            C = C;
            break;
        }
        case INS_LD_CD: {
            C = D;
            break;
        }
        case INS_LD_CE: {
            C = E;
            break;
        }
        case INS_LD_CH: {
            C = H;
            break;
        }
        case INS_LD_CL: {
            C = L;
            break;
        }
        case INS_LD_CHL: {
            Word addr = L | (H << 8);
            C = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_CA: {
            C = A;
            break;
        }
        case INS_LD_CN: {
            C = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_DB: {
            D = B;
            break;
        }
        case INS_LD_DC: {
            D = C;
            break;
        }
        case INS_LD_DD: {
            D = D;
            break;
        }
        case INS_LD_DE: {
            D = E;
            break;
        }
        case INS_LD_DH: {
            D = H;
            break;
        }
        case INS_LD_DL: {
            D = L;
            break;
        }
        case INS_LD_DHL: {
            Word addr = L | (H << 8);
            D = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_DA: {
            D = A;
            break;
        }
        case INS_LD_DN: {
            D = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_EB: {
            E = B;
            break;
        }
        case INS_LD_EC: {
            E = C;
            break;
        }
        case INS_LD_ED: {
            E = D;
            break;
        }
        case INS_LD_EE: {
            E = E;
            break;
        }
        case INS_LD_EH: {
            E = H;
            break;
        }
        case INS_LD_EL: {
            E = L;
            break;
        }
        case INS_LD_EHL: {
            Word addr = L | (H << 8);
            E = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_EA: {
            E = A;
            break;
        }
        case INS_LD_EN: {
            E = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_HB: {
            H = B;
            break;
        }
        case INS_LD_HC: {
            H = C;
            break;
        }
        case INS_LD_HD: {
            H = D;
            break;
        }
        case INS_LD_HE: {
            H = E;
            break;
        }
        case INS_LD_HH: {
            H = H;
            break;
        }
        case INS_LD_HL: {
            H = L;
            break;
        }
        case INS_LD_HHL: {
            Word addr = L | (H << 8);
            H = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_HA: {
            H = A;
            break;
        }
        case INS_LD_HN: {
            H = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_LB: {
            L = B;
            break;
        }
        case INS_LD_LC: {
            L = C;
            break;
        }
        case INS_LD_LD: {
            L = D;
            break;
        }
        case INS_LD_LE: {
            L = E;
            break;
        }
        case INS_LD_LH: {
            L = H;
            break;
        }
        case INS_LD_LL: {
            L = L;
            break;
        }
        case INS_LD_LHL: {
            Word addr = L | (H << 8);
            L = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_LA: {
            L = A;
            break;
        }
        case INS_LD_LN: {
            L = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_HLB: {
            Word addr = L | (H << 8);
            write_byte(addr, B, cycles, mem);
            break;
        }
        case INS_LD_HLC: {
            Word addr = L | (H << 8);
            write_byte(addr, C, cycles, mem);
            break;
        }
        case INS_LD_HLD: {
            Word addr = L | (H << 8);
            write_byte(addr, D, cycles, mem);
            break;
        }
        case INS_LD_HLE: {
            Word addr = L | (H << 8);
            write_byte(addr, E, cycles, mem);
            break;
        }
        case INS_LD_HLH: {
            Word addr = L | (H << 8);
            write_byte(addr, H, cycles, mem);
            break;
        }
        case INS_LD_HLL: {
            Word addr = L | (H << 8);
            write_byte(addr, L, cycles, mem);
            break;
        }
        case INS_LD_HLA: {
            Word addr = L | (H << 8);
            write_byte(addr, A, cycles, mem);
            break;
        }
        case INS_LD_HLN: {
            Word value = fetch_byte(cycles, mem);
            Word addr = L | (H << 8);
            write_byte(addr, value, cycles, mem);
            break;
        }

        case INS_LD_AB: {
            A = B;
            break;
        }
        case INS_LD_AC: {
            A = C;
            break;
        }
        case INS_LD_AD: {
            A = D;
            break;
        }
        case INS_LD_AE: {
            A = E;
            break;
        }
        case INS_LD_AH: {
            A = H;
            break;
        }
        case INS_LD_AL: {
            A = L;
            break;
        }
        case INS_LD_AHL: {
            Word addr = L | (H << 8);
            A = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_AA: {
            A = A;
            break;
        }
        case INS_LD_AN: {
            A = fetch_byte(cycles, mem);
            break;
        }

        case INS_LD_BCA: {
            Word addr = C | (B << 8);
            write_byte(addr, A, cycles, mem);
            break;
        }
        case INS_LD_DEA: {
            Word addr = E | (D << 8);
            write_byte(addr, A, cycles, mem);
            break;
        }

        case INS_LD_ABC: {
            Word addr = C | (B << 8);
            A = read_byte(addr, cycles, mem);
            break;
        }
        case INS_LD_ADE: {
            Word addr = E | (D << 8);
            A = read_byte(addr, cycles, mem);
            break;
        }

        case INS_LD_HLIA: {
            Word addr = L | (H << 8);
            write_byte(addr, A, cycles, mem);
            addr++;
            L = addr & 0x00FF;
            H = ((addr & 0xFF00) >> 8);
            break;
        }
        case INS_LD_HLDA: {
            Word addr = L | (H << 8);
            write_byte(addr, A, cycles, mem);
            addr--;
            L = addr & 0x00FF;
            H = ((addr & 0xFF00) >> 8);
            break;
        }

        case INS_LD_AHLI: {
            Word addr = L | (H << 8);
            A = read_byte(addr, cycles, mem);
            addr++;
            L = addr & 0x00FF;
            H = ((addr & 0xFF00) >> 8);
            break;
        }
        case INS_LD_AHLD: {
            Word addr = L | (H << 8);
            A = read_byte(addr, cycles, mem);
            addr--;
            L = addr & 0x00FF;
            H = ((addr & 0xFF00) >> 8);
            break;
        }

        case INS_LDH_A8A: {
            Byte a8 = fetch_byte(cycles, mem);
            Word addr = 0xFF00 | a8;
            write_byte(addr, A, cycles, mem);
            break;
        }
        case INS_LDH_AA8: {
            Byte a8 = fetch_byte(cycles, mem);
            Word addr = 0xFF00 | a8;
            A = read_byte(addr, cycles, mem);
            break;
        }

        case INS_LDH_CA: {
            Word addr = 0xFF00 | C;
            write_byte(addr, A, cycles, mem);
            break;
        }
        case INS_LDH_AC: {
            Word addr = 0xFF00 | C;
            A = read_byte(addr, cycles, mem);
            break;
        }

        case INS_LDH_A16A: {
            Byte little = fetch_byte(cycles, mem);
            Byte big = fetch_byte(cycles, mem);
            Word addr = little | (big << 8);
            write_byte(addr, A, cycles, mem);
            break;
        }
        case INS_LDH_AA16: {
            Byte little = fetch_byte(cycles, mem);
            Byte big = fetch_byte(cycles, mem);
            Word addr = little | (big << 8);
            A = read_byte(addr, cycles, mem);
            break;
        }

        // 16 bits
        case INS_LD_BCN16: {
            Byte little = fetch_byte(cycles, mem);
            C = little;
            Byte big = fetch_byte(cycles, mem);
            B = big;
            break;
        }
        case INS_LD_DEN16: {
            Byte little = fetch_byte(cycles, mem);
            E = little;
            Byte big = fetch_byte(cycles, mem);
            D = big;
            break;
        }
        case INS_LD_HLN16: {
            Byte little = fetch_byte(cycles, mem);
            L = little;
            Byte big = fetch_byte(cycles, mem);
            H = big;
            break;
        }
        case INS_LD_SPN16: {
            Word data = fetch_word(cycles, mem);
            SP = data;
            break;
        }

        case INS_LD_A16SP: {
            Word addr = fetch_word(cycles, mem);
            write_word(addr, SP, cycles, mem);
            break;
        }

        case INS_LD_SPHL: {
            Word data = L | (H << 8);
            SP = data;
            break;
        }
        case INS_LD_HLSPE8: {
            Byte uOffset = fetch_byte(cycles, mem);
            char offset = (char)uOffset;
            Word data = SP + offset;
            Byte little = data & 0x00FF;
            L = little;
            Byte big = (data & 0xFF00) >> 8;
            H = big;

            z = 0;
            n = 0;
            h = ((SP & 0xF) + (offset & 0xF)) > 0xF;
            c = ((SP & 0xFF) + (offset & 0xFF)) > 0xFF;
            break;
        }

        case INS_PUSH_BC: {
            SP -= 2;
            cycles++;
            write_byte(SP, C, cycles, mem);
            write_byte(SP+1, B, cycles, mem);
            break;
        }
        case INS_PUSH_DE: {
            SP -= 2;
            cycles++;
            write_byte(SP, E, cycles, mem);
            write_byte(SP+1, D, cycles, mem);
            break;
        }
        case INS_PUSH_HL: {
            SP -= 2;
            cycles++;
            write_byte(SP, L, cycles, mem);
            write_byte(SP+1, H, cycles, mem);
            break;
        }
        case INS_PUSH_AF: {
            SP -= 2;
            cycles++;
            Byte F = 0x0 | (z << 7) | (n << 6) | (h << 5) | (c << 4);
            write_byte(SP, F, cycles, mem);
            write_byte(SP+1, A, cycles, mem);
            break;
        }

        case INS_POP_BC: {
            C = read_byte(SP, cycles, mem);
            B = read_byte(SP+1, cycles, mem);
            SP += 2;
            break;
        }
        case INS_POP_DE: {
            E = read_byte(SP, cycles, mem);
            D = read_byte(SP+1, cycles, mem);
            SP += 2;
            break;
        }
        case INS_POP_HL: {
            L = read_byte(SP, cycles, mem);
            H = read_byte(SP+1, cycles, mem);
            SP += 2;
            break;
        }
        case INS_POP_AF: {
            Byte F = read_byte(SP, cycles, mem);
            z = (F >> 7) & 1;
            n = (F >> 6) & 1;
            h = (F >> 5) & 1;
            c = (F >> 4) & 1;
            A = read_byte(SP+1, cycles, mem);
            SP += 2;
            break;
        }

        // JUMPS / CALLS
        case INS_JR: {
            char offset = (char)fetch_byte(cycles, mem);
            PC += offset;
            cycles++;
            break;
        }
        case INS_JR_Z: {
            char offset = (char)fetch_byte(cycles, mem);
            if (z & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_C: {
            char offset = (char)fetch_byte(cycles, mem);
            if (c & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_NZ: {
            char offset = (char)fetch_byte(cycles, mem);
            if (~z & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_NC: {
            char offset = (char)fetch_byte(cycles, mem);
            if (~c & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }

        case INS_JP: {
            Word addr = fetch_word(cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_JP_HL: {
            Word addr = L | (H << 8);
            PC = addr;
            break;
        }
        case INS_JP_Z: {
            Word addr = fetch_word(cycles, mem);
            if (z & 1) {
                PC = addr;
                cycles++;
            }
            break;
        }
        case INS_JP_C: {
            Word addr = fetch_word(cycles, mem);
            if (c & 1) {
                PC = addr;
                cycles++;
            }
            break;
        }
        case INS_JP_NZ: {
            Word addr = fetch_word(cycles, mem);
            if (~z & 1) {
                PC = addr;
                cycles++;
            }
            break;
        }
        case INS_JP_NC: {
            Word addr = fetch_word(cycles, mem);
            if (~c & 1) {
                PC = addr;
                cycles++;
            }
            break;
        }

        case INS_CALL: {
            Word addr = fetch_word(cycles, mem);
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_CALL_Z: {
            Word addr = fetch_word(cycles, mem);
            if (z & 1) {
                SP -= 2;
                write_word(SP, PC, cycles, mem);
                PC = addr;
            }
            cycles++;
            break;
        }
        case INS_CALL_C: {
            Word addr = fetch_word(cycles, mem);
            if (c & 1) {
                SP -= 2;
                write_word(SP, PC, cycles, mem);
                PC = addr;
            }
            cycles++;
            break;
        }
        case INS_CALL_NZ: {
            Word addr = fetch_word(cycles, mem);
            if (~z & 1) {
                SP -= 2;
                write_word(SP, PC, cycles, mem);
                PC = addr;
            }
            cycles++;
            break;
        }
        case INS_CALL_NC: {
            Word addr = fetch_word(cycles, mem);
            if (~c & 1) {
                SP -= 2;
                write_word(SP, PC, cycles, mem);
                PC = addr;
            }
            cycles++;
            break;
        }

        case INS_RET: {
            Byte little = read_byte(SP, cycles, mem);
            Byte big = read_byte(SP+1, cycles, mem);
            SP += 2;
            PC = little | (big << 8);
            cycles++;
            break;
        }
        case INS_RET_Z: {
            if (z & 1) {
                Byte little = read_byte(SP, cycles, mem);
                Byte big = read_byte(SP+1, cycles, mem);
                SP += 2;
                PC = little | (big << 8);
            }
            cycles++;
            break;
        }
        case INS_RET_C: {
            if (c & 1) {
                Byte little = read_byte(SP, cycles, mem);
                Byte big = read_byte(SP+1, cycles, mem);
                SP += 2;
                PC = little | (big << 8);
            }
            cycles++;
            break;
        }
        case INS_RET_NZ: {
            if (~z & 1) {
                Byte little = read_byte(SP, cycles, mem);
                Byte big = read_byte(SP+1, cycles, mem);
                SP += 2;
                PC = little | (big << 8);
            }
            cycles++;
            break;
        }
        case INS_RET_NC: {
            if (~c & 1) {
                Byte little = read_byte(SP, cycles, mem);
                Byte big = read_byte(SP+1, cycles, mem);
                SP += 2;
                PC = little | (big << 8);
            }
            cycles++;
            break;
        }
        case INS_RETI: {
            Byte little = read_byte(SP, cycles, mem);
            Byte big = read_byte(SP+1, cycles, mem);
            SP += 2;
            PC = little | (big << 8);
            // TODO SET IME
            cycles++;
            break;
        }

        case INS_RST_00: {
            Word addr = 0x0000;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_08: {
            Word addr = 0x0008;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_10: {
            Word addr = 0x0010;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_18: {
            Word addr = 0x0018;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_20: {
            Word addr = 0x0020;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_28: {
            Word addr = 0x0028;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_30: {
            Word addr = 0x0030;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }
        case INS_RST_38: {
            Word addr = 0x0038;
            SP -= 2;
            write_word(SP, PC, cycles, mem);
            PC = addr;
            cycles++;
            break;
        }

        // 16 BITS ARITHMETIC / LOGICAL
        case INS_INC_BC: {
            Word data = C | (B << 8);
            data++;
            C = data & 0x00FF;
            B = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_INC_DE: {
            Word data = E | (D << 8);
            data++;
            E = data & 0x00FF;
            D = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_INC_HL: {
            Word data = L | (H << 8);
            data++;
            L = data & 0x00FF;
            H = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_INC_SP: {
            SP++;
            cycles++;
            break;
        }

        case INS_DEC_BC: {
            Word data = C | (B << 8);
            data--;
            C = data & 0x00FF;
            B = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_DEC_DE: {
            Word data = E | (D << 8);
            data--;
            E = data & 0x00FF;
            D = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_DEC_HL: {
            Word data = L | (H << 8);
            data--;
            L = data & 0x00FF;
            H = ((data & 0xFF00) >> 8);
            cycles++;
            break;
        }
        case INS_DEC_SP: {
            SP--;
            cycles++;
            break;
        }

        case INS_ADD_HLBC: {
            Word data = L | (H << 8);
            Word data2 = C | (B << 8);
            Word tot = data + data2;
            L = tot & 0x00FF;
            H = ((tot & 0xFF00) >> 8);
            cycles++;
            n = 0;
            h = ((data & 0xFFF) + (data2 & 0xFFF)) > 0xFFF;
            c = (u32)((data & 0xFFFF) + (data2 & 0xFFFF)) > 0xFFFF;
            break;
        }
        case INS_ADD_HLDE: {
            Word data = L | (H << 8);
            Word data2 = E | (D << 8);
            Word tot = data + data2;
            L = tot & 0x00FF;
            H = ((tot & 0xFF00) >> 8);
            cycles++;
            n = 0;
            h = ((data & 0xFFF) + (data2 & 0xFFF)) > 0xFFF;
            c = (u32)((data & 0xFFFF) + (data2 & 0xFFFF)) > 0xFFFF;
            break;
        }
        case INS_ADD_HLHL: {
            Word data = L | (H << 8);
            Byte tot = data + data;
            L = tot & 0x00FF;
            H = ((tot & 0xFF00) >> 8);
            cycles++;
            n = 0;
            h = ((data & 0xFFF) + (data & 0xFFF)) > 0xFFF;
            c = (u32)((data & 0xFFFF) + (data & 0xFFFF)) > 0xFFFF;
            break;
        }
        case INS_ADD_HLSP: {
            Word data = L | (H << 8);
            Byte tot = data + SP;
            L = tot & 0x00FF;
            H = ((tot & 0xFF00) >> 8);
            cycles++;
            n = 0;
            h = ((data & 0xFFF) + (SP & 0xFFF)) > 0xFFF;
            c = (u32)((data & 0xFFFF) + (SP & 0xFFFF)) > 0xFFFF;
            break;
        }

        case INS_ADD_SPE8: {
            char offset = (char)fetch_byte(cycles, mem);
            z = 0;
            n = 0;
            h = ((SP & 0xF) + (offset & 0xF)) > 0xF;
            c = ((SP & 0xFF) + (offset & 0xFF)) > 0xFF;
            SP += offset;
            cycles += 2;
            break;
        }

        // 8 BITS ARITHMETIC / LOGICAL
        case INS_ADD_AB: {
            n = 0;
            h = ((A & 0xF) + (B & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (B & 0xFF)) > 0xFF;
            A += B;
            z = A == 0;
            break;
        }
        case INS_ADD_AC: {
            n = 0;
            h = ((A & 0xF) + (C & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (C & 0xFF)) > 0xFF;
            A += C;
            z = A == 0;
            break;
        }
        case INS_ADD_AD: {
            n = 0;
            h = ((A & 0xF) + (D & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (D & 0xFF)) > 0xFF;
            A += D;
            z = A == 0;
            break;
        }
        case INS_ADD_AE: {
            n = 0;
            h = ((A & 0xF) + (E & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (E & 0xFF)) > 0xFF;
            A += E;
            z = A == 0;
            break;
        }
        case INS_ADD_AH: {
            n = 0;
            h = ((A & 0xF) + (H & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (H & 0xFF)) > 0xFF;
            A += H;
            z = A == 0;
            break;
        }
        case INS_ADD_AL: {
            n = 0;
            h = ((A & 0xF) + (L & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (L & 0xFF)) > 0xFF;
            A += L;
            z = A == 0;
            break;
        }
        case INS_ADD_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            n = 0;
            h = ((A & 0xF) + (data & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (data & 0xFF)) > 0xFF;
            A += data;
            z = A == 0;
            break;
        }
        case INS_ADD_AA: {
            n = 0;
            h = ((A & 0xF) + (A & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (A & 0xFF)) > 0xFF;
            A += A;
            z = A == 0;
            break;
        }
        case INS_ADD_AN: {
            Byte N = fetch_byte(cycles, mem);
            n = 0;
            h = ((A & 0xF) + (N & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (N & 0xFF)) > 0xFF;
            A += N;
            z = A == 0;
            break;
        }

        case INS_ADC_AB: {
            Byte add = B + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AC: {
            Byte add = C + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AD: {
            Byte add = D + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AE: {
            Byte add = E + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AH: {
            Byte add = H + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AL: {
            Byte add = L + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem) + c;
            n = 0;
            h = ((A & 0xF) + (data & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (data & 0xFF)) > 0xFF;
            A += data;
            z = A == 0;
            break;
        }
        case INS_ADC_AA: {
            Byte add = A + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }
        case INS_ADC_AN: {
            Byte add = fetch_byte(cycles, mem) + c;
            n = 0;
            h = ((A & 0xF) + (add & 0xF)) > 0xF;
            c = (u32)((A & 0xFF) + (add & 0xFF)) > 0xFF;
            A += add;
            z = A == 0;
            break;
        }

        case INS_SUB_AB: {
            n = 1;
            h = ((A & 0x0F) < (B & 0x0F));
            c = A < B;
            A -= B;
            z = A == 0;
            break;
        }
        case INS_SUB_AC: {
            n = 1;
            h = ((A & 0x0F) < (C & 0x0F));
            c = A < C;
            A -= C;
            z = A == 0;
            break;
        }
        case INS_SUB_AD: {
            n = 1;
            h = ((A & 0x0F) < (D & 0x0F));
            c = A < D;
            A -= D;
            z = A == 0;
            break;
        }
        case INS_SUB_AE: {
            n = 1;
            h = ((A & 0x0F) < (E & 0x0F));
            c = A < E;
            A -= E;
            z = A == 0;
            break;
        }
        case INS_SUB_AH: {
            n = 1;
            h = ((A & 0x0F) < (H & 0x0F));
            c = A < H;
            A -= H;
            z = A == 0;
            break;
        }
        case INS_SUB_AL: {
            n = 1;
            h = ((A & 0x0F) < (L & 0x0F));
            c = A < L;
            A -= L;
            z = A == 0;
            break;
        }
        case INS_SUB_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            n = 1;
            h = ((A & 0x0F) < (data & 0x0F));
            c = A < data;
            A -= data;
            z = A == 0;
            break;
        }
        case INS_SUB_AA: {
            n = 1;
            h = ((A & 0x0F) < (A & 0x0F));
            c = A < A;
            A -= A;
            z = A == 0;
            break;
        }
        case INS_SUB_AN: {
            Byte N = fetch_byte(cycles, mem);
            n = 1;
            h = ((A & 0x0F) < (N & 0x0F));
            c = A < N;
            A -= N;
            z = A == 0;
            break;
        }

        case INS_SBC_AB: {
            Byte sub = B + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AC: {
            Byte sub = C + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AD: {
            Byte sub = D + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AE: {
            Byte sub = E + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AH: {
            Byte sub = H + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AL: {
            Byte sub = L + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem) + c;
            n = 1;
            h = ((A & 0x0F) < (data & 0x0F));
            c = A < data;
            A -= data;
            z = A == 0;
            break;
        }
        case INS_SBC_AA: {
            Byte sub = A + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }
        case INS_SBC_AN: {
            Byte sub = fetch_byte(cycles, mem) + c;
            n = 1;
            h = ((A & 0x0F) < (sub & 0x0F));
            c = A < sub;
            A -= sub;
            z = A == 0;
            break;
        }

        case INS_AND_AB: {
            A = A & B;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AC: {
            A = A & C;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AD: {
            A = A & D;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AE: {
            A = A & E;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AH: {
            A = A & H;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AL: {
            A = A & L;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            A = A & data;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AA: {
            A = A & A;
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }
        case INS_AND_AN: {
            A = A & fetch_byte(cycles, mem);
            z = A == 0;
            n = 0;
            h = 1;
            c = 0;
            break;
        }

        case INS_XOR_AB: {
            A = A ^ B;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AC: {
            A = A ^ C;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AD: {
            A = A ^ D;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AE: {
            A = A ^ E;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AH: {
            A = A ^ H;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AL: {
            A = A ^ L;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            A = A ^ data;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AA: {
            A = A ^ A;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_XOR_AN: {
            A = A ^ fetch_byte(cycles, mem);
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }

        case INS_OR_AB: {
            A = A | B;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AC: {
            A = A | C;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AD: {
            A = A | D;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AE: {
            A = A | E;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AH: {
            A = A | H;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AL: {
            A = A | L;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            A = A | data;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AA: {
            A = A | A;
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }
        case INS_OR_AN: {
            A = A | fetch_byte(cycles, mem);
            z = A == 0;
            n = 0;
            h = 0;
            c = 0;
            break;
        }

        case INS_CP_AB: {
            Byte total = A - B;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (B & 0x0F));
            c = A < B;
            break;
        }
        case INS_CP_AC: {
            Byte total = A - C;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (C & 0x0F));
            c = A < C;
            break;
        }
        case INS_CP_AD: {
            Byte total = A - D;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (D & 0x0F));
            c = A < D;
            break;
        }
        case INS_CP_AE: {
            Byte total = A - E;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (E & 0x0F));
            c = A < E;
            break;
        }
        case INS_CP_AH: {
            Byte total = A - H;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (H & 0x0F));
            c = A < H;
            break;
        }
        case INS_CP_AL: {
            Byte total = A - L;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (L & 0x0F));
            c = A < L;
            break;
        }
        case INS_CP_AHL: {
            auto addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            Byte total = A - data;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (data & 0x0F));
            c = A < data;
            break;
        }
        case INS_CP_AA: {
            Byte total = A - A;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (A & 0x0F));
            c = A < A;
            break;
        }
        case INS_CP_AN: {
            Byte N = fetch_byte(cycles, mem);
            Byte total = A - N;
            z = total == 0;
            n = 1;
            h = ((A & 0x0F) < (N & 0x0F));
            c = A < N;
            break;
        }

        case INS_INC_B: {
            n = 0;
            h = ((B & 0xF) + 1) > 0xF;
            B++;
            z = B == 0;
            break;
        }
        case INS_INC_C: {
            n = 0;
            h = ((C & 0xF) + 1) > 0xF;
            C++;
            z = C == 0;
            break;
        }
        case INS_INC_D: {
            n = 0;
            h = ((D & 0xF) + 1) > 0xF;
            D++;
            z = D == 0;
            break;
        }
        case INS_INC_E: {
            n = 0;
            h = ((E & 0xF) + 1) > 0xF;
            E++;
            z = E == 0;
            break;
        }
        case INS_INC_H: {
            n = 0;
            h = ((H & 0xF) + 1) > 0xF;
            H++;
            z = H == 0;
            break;
        }
        case INS_INC_L: {
            n = 0;
            h = ((L & 0xF) + 1) > 0xF;
            L++;
            z = L == 0;
            break;
        }
        case INS_INC_PHL: {
            Word addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            n = 0;
            h = ((data & 0xF) + 1) > 0xF;
            write_byte(addr, data+1, cycles, mem);
            z = (data+1) == 0;
            break;
        }
        case INS_INC_A: {
            n = 0;
            h = ((A & 0xF) + 1) > 0xF;
            A++;
            z = A == 0;
            break;
        }

        case INS_DEC_B: {
            n = 1;
            h = (B & 0xF) < 1;
            B--;
            z = B == 0;
            break;
        }
        case INS_DEC_C: {
            n = 1;
            h = (C & 0xF) < 1;
            C--;
            z = C == 0;
            break;
        }
        case INS_DEC_D: {
            n = 1;
            h = (D & 0xF) < 1;
            D--;
            z = D == 0;
            break;
        }
        case INS_DEC_E: {
            n = 1;
            h = (E & 0xF) < 1;
            E--;
            z = E == 0;
            break;
        }
        case INS_DEC_H: {
            n = 1;
            h = (H & 0xF) < 1;
            H--;
            z = H == 0;
            break;
        }
        case INS_DEC_L: {
            n = 1;
            h = (L & 0xF) < 1;
            L--;
            z = L == 0;
            break;
        }
        case INS_DEC_PHL: {
            Word addr = L | (H << 8);
            Byte data = read_byte(addr, cycles, mem);
            n = 1;
            h = (data & 0xF) < 1;
            write_byte(addr, data-1, cycles, mem);
            z = (data-1) == 0;
            break;
        }
        case INS_DEC_A: {
            n = 1;
            h = (A & 0xF) < 1;
            A--;
            z = A == 0;
            break;
        }

        case INS_DAA: {
            if (n & 1) {
                Byte adj = 0;
                if (h & 1)
                    adj += 0x6;
                if (c & 1)
                    adj += 0x60;
                c = adj > A;
                A -= adj;
                z = A == 0;
            } else {
                Byte adj = 0;
                if (h & 1 || (A & 0xF) > 0x9)
                    adj += 0x6;
                if (c & 1 || A > 0x9F)
                    adj += 0x60;
                c = ((A & 0xFF) + (adj + 0xFF)) > 0xFF;
                A += adj;
                z = A == 0;
            }
            h = 0;
            break;
        }
        case INS_SCF: {
            n = 0;
            h = 0;
            c = 1;
            break;
        }
        case INS_CPL: {
            n = 1;
            h = 1;
            A = ~A;
            break;
        }
        case INS_CCF: {
            n = 0;
            h = 0;
            c = ~c;
            break;
        }

        default: printf("UNKNOWN INSTRUCTION");
        }
        return cycles;
    }

    void debug() {
        DEBUG(A);
        DEBUG(B);
        DEBUG(C);
        DEBUG(D);
        DEBUG(H);
        DEBUG(L);
    }
};

int main() {
    Memory mem;
    CPU cpu;

    mem.init();
    mem[0x00] = CPU::INS_LD_HN; // B
    mem[0x01] = 0xF0;
    mem[0x02] = CPU::INS_LD_LN; // C
    mem[0x03] = 0xFF;
    mem[0x04] = CPU::INS_LD_AN; // D
    mem[0x05] = 0x60;
    mem[0x06] = CPU::INS_LD_HLIA; // A
    u32 cycles = 0;
    u32 instructions = 4;
    for (int i = 0; i < instructions; ++i) {
        cycles += cpu.execute(mem);
    }
    printf("%u\n", cycles);
    DEBUG(mem[0xF0FF]);
    cpu.debug();
    return 0;
}
