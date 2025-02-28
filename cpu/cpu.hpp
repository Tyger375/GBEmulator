#pragma once
#include "../defs.hpp"
#include "../memory/memory.hpp"
#include <iostream>
#include <fstream>
#define DEBUG(byte) printf("%#02X\n", byte)

struct CPU {
    Byte A{}, B{}, C{}, D{}, E{}, H{}, L{};

    Word SP{};
    Word PC{};

    // flags
    Byte z{}, n{}, h{}, c{}, IME{};

	bool old_lcd_int_flag = false;

    bool is_boot = false;
    Byte rom_first[0x100]{};

    Byte fetch_byte(u32& cycles, Memory& mem);
    Word fetch_word(u32& cycles, Memory& mem);
    Byte read_byte(Word addr, u32& cycles, Memory& mem);
    void write_byte(Word addr, Byte value, u32& cycles, Memory& mem);
    void write_word(Word addr, Word data, u32& cycles, Memory& mem);
    Byte rlc_r(Byte data);
    Byte rrc_r(Byte data);
    Byte rl_r(Byte data);
    Byte rr_r(Byte data);
    Byte sla_r(Byte data);
    Byte sra_r(Byte data);
    Byte srl_r(Byte data);
    Byte swap_r(Byte data);
    void bit_r(Byte data, Byte bit);
    Byte res_r(Byte data, Byte bit);
    Byte set_r(Byte data, Byte bit);

    void load_bootup(const char* filename, Memory& mem);
    void load_rom(const char* filename, Memory& mem);

	static constexpr Word IE_REG = 0xFFFF;
	static constexpr Word IF_REG = 0xFF0F;

    static constexpr Byte INS_NOP = 0x00;
    static constexpr Byte INS_HALT = 0x76;
    static constexpr Byte INS_STOP = 0x10;
    static constexpr Byte INS_DI = 0xF3;
    static constexpr Byte INS_EI = 0xFB;

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
    static constexpr Byte INS_LD_SPHL= 0xF9;

    static constexpr Byte INS_PUSH_BC= 0xC5;
    static constexpr Byte INS_PUSH_DE= 0xD5;
    static constexpr Byte INS_PUSH_HL= 0xE5;
    static constexpr Byte INS_PUSH_AF= 0xF5;

    static constexpr Byte INS_POP_BC = 0xC1;
    static constexpr Byte INS_POP_DE = 0xD1;
    static constexpr Byte INS_POP_HL = 0xE1;
    static constexpr Byte INS_POP_AF = 0xF1;

    // JUMPS / CALLS
    static constexpr Byte INS_JR     = 0x18;
    static constexpr Byte INS_JR_Z   = 0x28;
    static constexpr Byte INS_JR_C   = 0x38;
    static constexpr Byte INS_JR_NZ  = 0x20;
    static constexpr Byte INS_JR_NC  = 0x30;

    static constexpr Byte INS_JP     = 0xC3;
    static constexpr Byte INS_JP_HL  = 0xE9;
    static constexpr Byte INS_JP_Z   = 0xCA;
    static constexpr Byte INS_JP_C   = 0xDA;
    static constexpr Byte INS_JP_NZ  = 0xC2;
    static constexpr Byte INS_JP_NC  = 0xD2;

    static constexpr Byte INS_CALL    = 0xCD;
    static constexpr Byte INS_CALL_Z  = 0xCC;
    static constexpr Byte INS_CALL_C  = 0xDC;
    static constexpr Byte INS_CALL_NZ = 0xC4;
    static constexpr Byte INS_CALL_NC = 0xD4;

    static constexpr Byte INS_RET    = 0xC9;
    static constexpr Byte INS_RET_Z  = 0xC8;
    static constexpr Byte INS_RET_C  = 0xD8;
    static constexpr Byte INS_RET_NZ = 0xC0;
    static constexpr Byte INS_RET_NC = 0xD0;
    static constexpr Byte INS_RETI   = 0xD9;

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
    static constexpr Byte INS_ADD_AHL= 0x86;
    static constexpr Byte INS_ADD_AA = 0x87;
    static constexpr Byte INS_ADD_AN = 0xC6;

    static constexpr Byte INS_ADC_AB = 0x88;
    static constexpr Byte INS_ADC_AC = 0x89;
    static constexpr Byte INS_ADC_AD = 0x8A;
    static constexpr Byte INS_ADC_AE = 0x8B;
    static constexpr Byte INS_ADC_AH = 0x8C;
    static constexpr Byte INS_ADC_AL = 0x8D;
    static constexpr Byte INS_ADC_AHL= 0x8E;
    static constexpr Byte INS_ADC_AA = 0x8F;
    static constexpr Byte INS_ADC_AN = 0xCE;

    static constexpr Byte INS_SUB_AB = 0x90;
    static constexpr Byte INS_SUB_AC = 0x91;
    static constexpr Byte INS_SUB_AD = 0x92;
    static constexpr Byte INS_SUB_AE = 0x93;
    static constexpr Byte INS_SUB_AH = 0x94;
    static constexpr Byte INS_SUB_AL = 0x95;
    static constexpr Byte INS_SUB_AHL= 0x96;
    static constexpr Byte INS_SUB_AA = 0x97;

    static constexpr Byte INS_SUB_AN = 0xD6;

    static constexpr Byte INS_SBC_AB = 0x98;
    static constexpr Byte INS_SBC_AC = 0x99;
    static constexpr Byte INS_SBC_AD = 0x9A;
    static constexpr Byte INS_SBC_AE = 0x9B;
    static constexpr Byte INS_SBC_AH = 0x9C;
    static constexpr Byte INS_SBC_AL = 0x9D;
    static constexpr Byte INS_SBC_AHL= 0x9E;
    static constexpr Byte INS_SBC_AA = 0x9F;
    static constexpr Byte INS_SBC_AN = 0xDE;

    static constexpr Byte INS_AND_AB = 0xA0;
    static constexpr Byte INS_AND_AC = 0xA1;
    static constexpr Byte INS_AND_AD = 0xA2;
    static constexpr Byte INS_AND_AE = 0xA3;
    static constexpr Byte INS_AND_AH = 0xA4;
    static constexpr Byte INS_AND_AL = 0xA5;
    static constexpr Byte INS_AND_AHL= 0xA6;
    static constexpr Byte INS_AND_AA = 0xA7;
    static constexpr Byte INS_AND_AN = 0xE6;

    static constexpr Byte INS_XOR_AB = 0xA8;
    static constexpr Byte INS_XOR_AC = 0xA9;
    static constexpr Byte INS_XOR_AD = 0xAA;
    static constexpr Byte INS_XOR_AE = 0xAB;
    static constexpr Byte INS_XOR_AH = 0xAC;
    static constexpr Byte INS_XOR_AL = 0xAD;
    static constexpr Byte INS_XOR_AHL= 0xAE;
    static constexpr Byte INS_XOR_AA = 0xAF;
    static constexpr Byte INS_XOR_AN = 0xEE;

    static constexpr Byte INS_OR_AB  = 0xB0;
    static constexpr Byte INS_OR_AC  = 0xB1;
    static constexpr Byte INS_OR_AD  = 0xB2;
    static constexpr Byte INS_OR_AE  = 0xB3;
    static constexpr Byte INS_OR_AH  = 0xB4;
    static constexpr Byte INS_OR_AL  = 0xB5;
    static constexpr Byte INS_OR_AHL = 0xB6;
    static constexpr Byte INS_OR_AA  = 0xB7;
    static constexpr Byte INS_OR_AN  = 0xF6;

    static constexpr Byte INS_CP_AB  = 0xB8;
    static constexpr Byte INS_CP_AC  = 0xB9;
    static constexpr Byte INS_CP_AD  = 0xBA;
    static constexpr Byte INS_CP_AE  = 0xBB;
    static constexpr Byte INS_CP_AH  = 0xBC;
    static constexpr Byte INS_CP_AL  = 0xBD;
    static constexpr Byte INS_CP_AHL = 0xBE;
    static constexpr Byte INS_CP_AA  = 0xBF;
    static constexpr Byte INS_CP_AN  = 0xFE;

    static constexpr Byte INS_INC_B  = 0x04;
    static constexpr Byte INS_INC_C  = 0x0C;
    static constexpr Byte INS_INC_D  = 0x14;
    static constexpr Byte INS_INC_E  = 0x1C;
    static constexpr Byte INS_INC_H  = 0x24;
    static constexpr Byte INS_INC_L  = 0x2C;
    static constexpr Byte INS_INC_PHL= 0x34;
    static constexpr Byte INS_INC_A  = 0x3C;

    static constexpr Byte INS_DEC_B  = 0x05;
    static constexpr Byte INS_DEC_C  = 0x0D;
    static constexpr Byte INS_DEC_D  = 0x15;
    static constexpr Byte INS_DEC_E  = 0x1D;
    static constexpr Byte INS_DEC_H  = 0x25;
    static constexpr Byte INS_DEC_L  = 0x2D;
    static constexpr Byte INS_DEC_PHL= 0x35;
    static constexpr Byte INS_DEC_A  = 0x3D;

    static constexpr Byte INS_DAA    = 0x27;
    static constexpr Byte INS_SCF    = 0x37;
    static constexpr Byte INS_CPL    = 0x2F;
    static constexpr Byte INS_CCF    = 0x3F;

    // 8 BITS SHIFT / ROTATE / BIT INSTRUCTION
    static constexpr Byte INS_RLCA   = 0x07;
    static constexpr Byte INS_RRCA   = 0x0F;
    static constexpr Byte INS_RLA    = 0x17;
    static constexpr Byte INS_RRA    = 0x1F;

    static constexpr Byte INS_PREFIX = 0xCB;

    static constexpr Byte INS_RLC_B  = 0x00;
    static constexpr Byte INS_RLC_C  = 0x01;
    static constexpr Byte INS_RLC_D  = 0x02;
    static constexpr Byte INS_RLC_E  = 0x03;
    static constexpr Byte INS_RLC_H  = 0x04;
    static constexpr Byte INS_RLC_L  = 0x05;
    static constexpr Byte INS_RLC_HL = 0x06;
    static constexpr Byte INS_RLC_A  = 0x07;

    static constexpr Byte INS_RRC_B  = 0x08;
    static constexpr Byte INS_RRC_C  = 0x09;
    static constexpr Byte INS_RRC_D  = 0x0A;
    static constexpr Byte INS_RRC_E  = 0x0B;
    static constexpr Byte INS_RRC_H  = 0x0C;
    static constexpr Byte INS_RRC_L  = 0x0D;
    static constexpr Byte INS_RRC_HL = 0x0E;
    static constexpr Byte INS_RRC_A  = 0x0F;

    static constexpr Byte INS_RL_B   = 0x10;
    static constexpr Byte INS_RL_C   = 0x11;
    static constexpr Byte INS_RL_D   = 0x12;
    static constexpr Byte INS_RL_E   = 0x13;
    static constexpr Byte INS_RL_H   = 0x14;
    static constexpr Byte INS_RL_L   = 0x15;
    static constexpr Byte INS_RL_HL  = 0x16;
    static constexpr Byte INS_RL_A   = 0x17;

    static constexpr Byte INS_RR_B   = 0x18;
    static constexpr Byte INS_RR_C   = 0x19;
    static constexpr Byte INS_RR_D   = 0x1A;
    static constexpr Byte INS_RR_E   = 0x1B;
    static constexpr Byte INS_RR_H   = 0x1C;
    static constexpr Byte INS_RR_L   = 0x1D;
    static constexpr Byte INS_RR_HL  = 0x1E;
    static constexpr Byte INS_RR_A   = 0x1F;

    static constexpr Byte INS_SLA_B  = 0x20;
    static constexpr Byte INS_SLA_C  = 0x21;
    static constexpr Byte INS_SLA_D  = 0x22;
    static constexpr Byte INS_SLA_E  = 0x23;
    static constexpr Byte INS_SLA_H  = 0x24;
    static constexpr Byte INS_SLA_L = 0x25;
    static constexpr Byte INS_SLA_HL = 0x26;
    static constexpr Byte INS_SLA_A  = 0x27;

    static constexpr Byte INS_SRA_B  = 0x28;
    static constexpr Byte INS_SRA_C  = 0x29;
    static constexpr Byte INS_SRA_D  = 0x2A;
    static constexpr Byte INS_SRA_E  = 0x2B;
    static constexpr Byte INS_SRA_H  = 0x2C;
    static constexpr Byte INS_SRA_L  = 0x2D;
    static constexpr Byte INS_SRA_HL = 0x2E;
    static constexpr Byte INS_SRA_A  = 0x2F;

    static constexpr Byte INS_SWAP_B = 0x30;
    static constexpr Byte INS_SWAP_C = 0x31;
    static constexpr Byte INS_SWAP_D = 0x32;
    static constexpr Byte INS_SWAP_E = 0x33;
    static constexpr Byte INS_SWAP_H = 0x34;
    static constexpr Byte INS_SWAP_L = 0x35;
    static constexpr Byte INS_SWAP_HL= 0x36;
    static constexpr Byte INS_SWAP_A = 0x37;

    static constexpr Byte INS_SRL_B  = 0x38;
    static constexpr Byte INS_SRL_C  = 0x39;
    static constexpr Byte INS_SRL_D  = 0x3A;
    static constexpr Byte INS_SRL_E  = 0x3B;
    static constexpr Byte INS_SRL_H  = 0x3C;
    static constexpr Byte INS_SRL_L  = 0x3D;
    static constexpr Byte INS_SRL_HL = 0x3E;
    static constexpr Byte INS_SRL_A  = 0x3F;

    static constexpr Byte INS_BIT_0B = 0x40;
    static constexpr Byte INS_BIT_0C = 0x41;
    static constexpr Byte INS_BIT_0D = 0x42;
    static constexpr Byte INS_BIT_0E = 0x43;
    static constexpr Byte INS_BIT_0H = 0x44;
    static constexpr Byte INS_BIT_0L = 0x45;
    static constexpr Byte INS_BIT_0HL= 0x46;
    static constexpr Byte INS_BIT_0A = 0x47;

    static constexpr Byte INS_BIT_1B = 0x48;
    static constexpr Byte INS_BIT_1C = 0x49;
    static constexpr Byte INS_BIT_1D = 0x4A;
    static constexpr Byte INS_BIT_1E = 0x4B;
    static constexpr Byte INS_BIT_1H = 0x4C;
    static constexpr Byte INS_BIT_1L = 0x4D;
    static constexpr Byte INS_BIT_1HL= 0x4E;
    static constexpr Byte INS_BIT_1A = 0x4F;

    static constexpr Byte INS_BIT_2B = 0x50;
    static constexpr Byte INS_BIT_2C = 0x51;
    static constexpr Byte INS_BIT_2D = 0x52;
    static constexpr Byte INS_BIT_2E = 0x53;
    static constexpr Byte INS_BIT_2H = 0x54;
    static constexpr Byte INS_BIT_2L = 0x55;
    static constexpr Byte INS_BIT_2HL= 0x56;
    static constexpr Byte INS_BIT_2A = 0x57;

    static constexpr Byte INS_BIT_3B = 0x58;
    static constexpr Byte INS_BIT_3C = 0x59;
    static constexpr Byte INS_BIT_3D = 0x5A;
    static constexpr Byte INS_BIT_3E = 0x5B;
    static constexpr Byte INS_BIT_3H = 0x5C;
    static constexpr Byte INS_BIT_3L = 0x5D;
    static constexpr Byte INS_BIT_3HL= 0x5E;
    static constexpr Byte INS_BIT_3A = 0x5F;

    static constexpr Byte INS_BIT_4B = 0x60;
    static constexpr Byte INS_BIT_4C = 0x61;
    static constexpr Byte INS_BIT_4D = 0x62;
    static constexpr Byte INS_BIT_4E = 0x63;
    static constexpr Byte INS_BIT_4H = 0x64;
    static constexpr Byte INS_BIT_4L = 0x65;
    static constexpr Byte INS_BIT_4HL= 0x66;
    static constexpr Byte INS_BIT_4A = 0x67;

    static constexpr Byte INS_BIT_5B = 0x68;
    static constexpr Byte INS_BIT_5C = 0x69;
    static constexpr Byte INS_BIT_5D = 0x6A;
    static constexpr Byte INS_BIT_5E = 0x6B;
    static constexpr Byte INS_BIT_5H = 0x6C;
    static constexpr Byte INS_BIT_5L = 0x6D;
    static constexpr Byte INS_BIT_5HL= 0x6E;
    static constexpr Byte INS_BIT_5A = 0x6F;

    static constexpr Byte INS_BIT_6B = 0x70;
    static constexpr Byte INS_BIT_6C = 0x71;
    static constexpr Byte INS_BIT_6D = 0x72;
    static constexpr Byte INS_BIT_6E = 0x73;
    static constexpr Byte INS_BIT_6H = 0x74;
    static constexpr Byte INS_BIT_6L = 0x75;
    static constexpr Byte INS_BIT_6HL= 0x76;
    static constexpr Byte INS_BIT_6A = 0x77;

    static constexpr Byte INS_BIT_7B = 0x78;
    static constexpr Byte INS_BIT_7C = 0x79;
    static constexpr Byte INS_BIT_7D = 0x7A;
    static constexpr Byte INS_BIT_7E = 0x7B;
    static constexpr Byte INS_BIT_7H = 0x7C;
    static constexpr Byte INS_BIT_7L = 0x7D;
    static constexpr Byte INS_BIT_7HL= 0x7E;
    static constexpr Byte INS_BIT_7A = 0x7F;

    static constexpr Byte INS_RES_0B = 0x80;
    static constexpr Byte INS_RES_0C = 0x81;
    static constexpr Byte INS_RES_0D = 0x82;
    static constexpr Byte INS_RES_0E = 0x83;
    static constexpr Byte INS_RES_0H = 0x84;
    static constexpr Byte INS_RES_0L = 0x85;
    static constexpr Byte INS_RES_0HL= 0x86;
    static constexpr Byte INS_RES_0A = 0x87;

    static constexpr Byte INS_RES_1B = 0x88;
    static constexpr Byte INS_RES_1C = 0x89;
    static constexpr Byte INS_RES_1D = 0x8A;
    static constexpr Byte INS_RES_1E = 0x8B;
    static constexpr Byte INS_RES_1H = 0x8C;
    static constexpr Byte INS_RES_1L = 0x8D;
    static constexpr Byte INS_RES_1HL= 0x8E;
    static constexpr Byte INS_RES_1A = 0x8F;

    static constexpr Byte INS_RES_2B = 0x90;
    static constexpr Byte INS_RES_2C = 0x91;
    static constexpr Byte INS_RES_2D = 0x92;
    static constexpr Byte INS_RES_2E = 0x93;
    static constexpr Byte INS_RES_2H = 0x94;
    static constexpr Byte INS_RES_2L = 0x95;
    static constexpr Byte INS_RES_2HL= 0x96;
    static constexpr Byte INS_RES_2A = 0x97;

    static constexpr Byte INS_RES_3B = 0x98;
    static constexpr Byte INS_RES_3C = 0x99;
    static constexpr Byte INS_RES_3D = 0x9A;
    static constexpr Byte INS_RES_3E = 0x9B;
    static constexpr Byte INS_RES_3H = 0x9C;
    static constexpr Byte INS_RES_3L = 0x9D;
    static constexpr Byte INS_RES_3HL= 0x9E;
    static constexpr Byte INS_RES_3A = 0x9F;

    static constexpr Byte INS_RES_4B = 0xA0;
    static constexpr Byte INS_RES_4C = 0xA1;
    static constexpr Byte INS_RES_4D = 0xA2;
    static constexpr Byte INS_RES_4E = 0xA3;
    static constexpr Byte INS_RES_4H = 0xA4;
    static constexpr Byte INS_RES_4L = 0xA5;
    static constexpr Byte INS_RES_4HL= 0xA6;
    static constexpr Byte INS_RES_4A = 0xA7;

    static constexpr Byte INS_RES_5B = 0xA8;
    static constexpr Byte INS_RES_5C = 0xA9;
    static constexpr Byte INS_RES_5D = 0xAA;
    static constexpr Byte INS_RES_5E = 0xAB;
    static constexpr Byte INS_RES_5H = 0xAC;
    static constexpr Byte INS_RES_5L = 0xAD;
    static constexpr Byte INS_RES_5HL= 0xAE;
    static constexpr Byte INS_RES_5A = 0xAF;

    static constexpr Byte INS_RES_6B = 0xB0;
    static constexpr Byte INS_RES_6C = 0xB1;
    static constexpr Byte INS_RES_6D = 0xB2;
    static constexpr Byte INS_RES_6E = 0xB3;
    static constexpr Byte INS_RES_6H = 0xB4;
    static constexpr Byte INS_RES_6L = 0xB5;
    static constexpr Byte INS_RES_6HL= 0xB6;
    static constexpr Byte INS_RES_6A = 0xB7;

    static constexpr Byte INS_RES_7B = 0xB8;
    static constexpr Byte INS_RES_7C = 0xB9;
    static constexpr Byte INS_RES_7D = 0xBA;
    static constexpr Byte INS_RES_7E = 0xBB;
    static constexpr Byte INS_RES_7H = 0xBC;
    static constexpr Byte INS_RES_7L = 0xBD;
    static constexpr Byte INS_RES_7HL= 0xBE;
    static constexpr Byte INS_RES_7A = 0xBF;

    static constexpr Byte INS_SET_0B = 0xC0;
    static constexpr Byte INS_SET_0C = 0xC1;
    static constexpr Byte INS_SET_0D = 0xC2;
    static constexpr Byte INS_SET_0E = 0xC3;
    static constexpr Byte INS_SET_0H = 0xC4;
    static constexpr Byte INS_SET_0L = 0xC5;
    static constexpr Byte INS_SET_0HL= 0xC6;
    static constexpr Byte INS_SET_0A = 0xC7;

    static constexpr Byte INS_SET_1B = 0xC8;
    static constexpr Byte INS_SET_1C = 0xC9;
    static constexpr Byte INS_SET_1D = 0xCA;
    static constexpr Byte INS_SET_1E = 0xCB;
    static constexpr Byte INS_SET_1H = 0xCC;
    static constexpr Byte INS_SET_1L = 0xCD;
    static constexpr Byte INS_SET_1HL= 0xCE;
    static constexpr Byte INS_SET_1A = 0xCF;

    static constexpr Byte INS_SET_2B = 0xD0;
    static constexpr Byte INS_SET_2C = 0xD1;
    static constexpr Byte INS_SET_2D = 0xD2;
    static constexpr Byte INS_SET_2E = 0xD3;
    static constexpr Byte INS_SET_2H = 0xD4;
    static constexpr Byte INS_SET_2L = 0xD5;
    static constexpr Byte INS_SET_2HL= 0xD6;
    static constexpr Byte INS_SET_2A = 0xD7;

    static constexpr Byte INS_SET_3B = 0xD8;
    static constexpr Byte INS_SET_3C = 0xD9;
    static constexpr Byte INS_SET_3D = 0xDA;
    static constexpr Byte INS_SET_3E = 0xDB;
    static constexpr Byte INS_SET_3H = 0xDC;
    static constexpr Byte INS_SET_3L = 0xDD;
    static constexpr Byte INS_SET_3HL= 0xDE;
    static constexpr Byte INS_SET_3A = 0xDF;

    static constexpr Byte INS_SET_4B = 0xE0;
    static constexpr Byte INS_SET_4C = 0xE1;
    static constexpr Byte INS_SET_4D = 0xE2;
    static constexpr Byte INS_SET_4E = 0xE3;
    static constexpr Byte INS_SET_4H = 0xE4;
    static constexpr Byte INS_SET_4L = 0xE5;
    static constexpr Byte INS_SET_4HL= 0xE6;
    static constexpr Byte INS_SET_4A = 0xE7;

    static constexpr Byte INS_SET_5B = 0xE8;
    static constexpr Byte INS_SET_5C = 0xE9;
    static constexpr Byte INS_SET_5D = 0xEA;
    static constexpr Byte INS_SET_5E = 0xEB;
    static constexpr Byte INS_SET_5H = 0xEC;
    static constexpr Byte INS_SET_5L = 0xED;
    static constexpr Byte INS_SET_5HL= 0xEE;
    static constexpr Byte INS_SET_5A = 0xEF;

    static constexpr Byte INS_SET_6B = 0xF0;
    static constexpr Byte INS_SET_6C = 0xF1;
    static constexpr Byte INS_SET_6D = 0xF2;
    static constexpr Byte INS_SET_6E = 0xF3;
    static constexpr Byte INS_SET_6H = 0xF4;
    static constexpr Byte INS_SET_6L = 0xF5;
    static constexpr Byte INS_SET_6HL= 0xF6;
    static constexpr Byte INS_SET_6A = 0xF7;

    static constexpr Byte INS_SET_7B = 0xF8;
    static constexpr Byte INS_SET_7C = 0xF9;
    static constexpr Byte INS_SET_7D = 0xFA;
    static constexpr Byte INS_SET_7E = 0xFB;
    static constexpr Byte INS_SET_7H = 0xFC;
    static constexpr Byte INS_SET_7L = 0xFD;
    static constexpr Byte INS_SET_7HL= 0xFE;
    static constexpr Byte INS_SET_7A = 0xFF;

	void call_int(Memory&, Word);
    void ack_int(Memory&, int);
	void handle_interrupts(Memory&);
	void exec_op(u32&, Memory&);

    u32 execute(Memory& mem);
};
