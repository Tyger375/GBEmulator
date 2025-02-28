#include "cpu.hpp"

void CPU::exec_op(u32 &cycles, Memory& mem) {
    switch (Byte ins = fetch_byte(cycles, mem)) {
        case INS_NOP: {
            break;
        }
        case INS_STOP: {
            std::cerr << "STOP instruction not implemented" << std::endl;
            break;
        }
        case INS_HALT: {
            std::cerr << "HALT instruction not implemented" << std::endl;
            break;
        }
        case INS_DI: {
            IME = 0;
            break;
        }
        case INS_EI: {
            IME = 1;
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
            Byte value = fetch_byte(cycles, mem);
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
            auto offset = static_cast<signed char>(uOffset);
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
            Byte F = 0x0 | ((z & 1) << 7) | ((n & 1) << 6) | ((h & 1) << 5) | ((c & 1) << 4);
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
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
            PC += offset;
            cycles++;
            break;
        }
        case INS_JR_Z: {
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
            if (z & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_C: {
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
            if (c & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_NZ: {
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
            if (~z & 1) {
                PC += offset;
                cycles++;
            }
            break;
        }
        case INS_JR_NC: {
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
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
            IME = 1;
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
            Word tot = data + data;
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
            Word tot = data + SP;
            L = tot & 0x00FF;
            H = ((tot & 0xFF00) >> 8);
            cycles++;
            n = 0;
            h = ((data & 0xFFF) + (SP & 0xFFF)) > 0xFFF;
            c = (u32)((data & 0xFFFF) + (SP & 0xFFFF)) > 0xFFFF;
            break;
        }

        case INS_ADD_SPE8: {
            auto offset = static_cast<signed char>(fetch_byte(cycles, mem));
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

        case INS_RLCA: {
            Byte last = (A & 0x80) > 0;
            A <<= 1;
            A |= last;
            c = last;
            z = 0;
            n = 0;
            h = 0;
            break;
        }
        case INS_RRCA: {
            Byte first = A & 1;
            A >>= 1;
            A |= first << 7;
            c = first;
            z = 0;
            n = 0;
            h = 0;
            break;
        }
        case INS_RLA: {
            Byte last = (A & 0x80) > 0;
            A <<= 1;
            A |= c & 1;
            c = last;
            z = 0;
            n = 0;
            h = 0;
            break;
        }
        case INS_RRA: {
            Byte first = A & 1;
            A >>= 1;
            A |= (c & 1) << 7;
            c = first;
            z = 0;
            n = 0;
            h = 0;
            break;
        }
        case INS_PREFIX: {
            Byte prefix_ins = fetch_byte(cycles, mem);
            switch (prefix_ins) {
            case INS_RLC_B: {
                B = rlc_r(B);
                break;
            }
            case INS_RLC_C: {
                C = rlc_r(C);
                break;
            }
            case INS_RLC_D: {
                D = rlc_r(D);
                break;
            }
            case INS_RLC_E: {
                E = rlc_r(E);
                break;
            }
            case INS_RLC_H: {
                H = rlc_r(H);
                break;
            }
            case INS_RLC_L: {
                L = rlc_r(L);
                break;
            }
            case INS_RLC_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = rlc_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RLC_A: {
                A = rlc_r(A);
                break;
            }

            case INS_RRC_B: {
                B = rrc_r(B);
                break;
            }
            case INS_RRC_C: {
                C = rrc_r(C);
                break;
            }
            case INS_RRC_D: {
                D = rrc_r(D);
                break;
            }
            case INS_RRC_E: {
                E = rrc_r(E);
                break;
            }
            case INS_RRC_H: {
                H = rrc_r(H);
                break;
            }
            case INS_RRC_L: {
                L = rrc_r(L);
                break;
            }
            case INS_RRC_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = rrc_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RRC_A: {
                A = rrc_r(A);
                break;
            }

            case INS_RL_B: {
                B = rl_r(B);
                break;
            }
            case INS_RL_C: {
                C = rl_r(C);
                break;
            }
            case INS_RL_D: {
                D = rl_r(D);
                break;
            }
            case INS_RL_E: {
                E = rl_r(E);
                break;
            }
            case INS_RL_H: {
                H = rl_r(H);
                break;
            }
            case INS_RL_L: {
                L = rl_r(L);
                break;
            }
            case INS_RL_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = rl_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RL_A: {
                A = rl_r(A);
                break;
            }

            case INS_RR_B: {
                B = rr_r(B);
                break;
            }
            case INS_RR_C: {
                C = rr_r(C);
                break;
            }
            case INS_RR_D: {
                D = rr_r(D);
                break;
            }
            case INS_RR_E: {
                E = rr_r(E);
                break;
            }
            case INS_RR_H: {
                H = rr_r(H);
                break;
            }
            case INS_RR_L: {
                L = rr_r(L);
                break;
            }
            case INS_RR_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = rr_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RR_A: {
                A = rr_r(A);
                break;
            }

            case INS_SLA_B: {
                B = sla_r(B);
                break;
            }
            case INS_SLA_C: {
                C = sla_r(C);
                break;
            }
            case INS_SLA_D: {
                D = sla_r(D);
                break;
            }
            case INS_SLA_E: {
                E = sla_r(E);
                break;
            }
            case INS_SLA_H: {
                H = sla_r(H);
                break;
            }
            case INS_SLA_L: {
                L = sla_r(L);
                break;
            }
            case INS_SLA_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = sla_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SLA_A: {
                A = sla_r(A);
                break;
            }

            case INS_SRA_B: {
                B = sra_r(B);
                break;
            }
            case INS_SRA_C: {
                C = sra_r(C);
                break;
            }
            case INS_SRA_D: {
                D = sra_r(D);
                break;
            }
            case INS_SRA_E: {
                E = sra_r(E);
                break;
            }
            case INS_SRA_H: {
                H = sra_r(H);
                break;
            }
            case INS_SRA_L: {
                L = sra_r(L);
                break;
            }
            case INS_SRA_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = sra_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SRA_A: {
                A = sra_r(A);
                break;
            }

            case INS_SWAP_B: {
                B = swap_r(B);
                break;
            }
            case INS_SWAP_C: {
                C = swap_r(C);
                break;
            }
            case INS_SWAP_D: {
                D = swap_r(D);
                break;
            }
            case INS_SWAP_E: {
                E = swap_r(E);
                break;
            }
            case INS_SWAP_H: {
                H = swap_r(H);
                break;
            }
            case INS_SWAP_L: {
                L = swap_r(L);
                break;
            }
            case INS_SWAP_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = swap_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SWAP_A: {
                A = swap_r(A);
                break;
            }

            case INS_SRL_B: {
                B = srl_r(B);
                break;
            }
            case INS_SRL_C: {
                C = srl_r(C);
                break;
            }
            case INS_SRL_D: {
                D = srl_r(D);
                break;
            }
            case INS_SRL_E: {
                E = srl_r(E);
                break;
            }
            case INS_SRL_H: {
                H = srl_r(H);
                break;
            }
            case INS_SRL_L: {
                L = srl_r(L);
                break;
            }
            case INS_SRL_HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = srl_r(data);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SRL_A: {
                A = srl_r(A);
                break;
            }

            case INS_BIT_0B: {
                bit_r(B, 0);
                break;
            }
            case INS_BIT_0C: {
                bit_r(C, 0);
                break;
            }
            case INS_BIT_0D: {
                bit_r(D, 0);
                break;
            }
            case INS_BIT_0E: {
                bit_r(E, 0);
                break;
            }
            case INS_BIT_0H: {
                bit_r(H, 0);
                break;
            }
            case INS_BIT_0L: {
                bit_r(L, 0);
                break;
            }
            case INS_BIT_0HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 0);
                break;
            }
            case INS_BIT_0A: {
                bit_r(A, 0);
                break;
            }

            case INS_BIT_1B: {
                bit_r(B, 1);
                break;
            }
            case INS_BIT_1C: {
                bit_r(C, 1);
                break;
            }
            case INS_BIT_1D: {
                bit_r(D, 1);
                break;
            }
            case INS_BIT_1E: {
                bit_r(E, 1);
                break;
            }
            case INS_BIT_1H: {
                bit_r(H, 1);
                break;
            }
            case INS_BIT_1L: {
                bit_r(L, 1);
                break;
            }
            case INS_BIT_1HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 1);
                break;
            }
            case INS_BIT_1A: {
                bit_r(A, 1);
                break;
            }

            case INS_BIT_2B: {
                bit_r(B, 2);
                break;
            }
            case INS_BIT_2C: {
                bit_r(C, 2);
                break;
            }
            case INS_BIT_2D: {
                bit_r(D, 2);
                break;
            }
            case INS_BIT_2E: {
                bit_r(E, 2);
                break;
            }
            case INS_BIT_2H: {
                bit_r(H, 2);
                break;
            }
            case INS_BIT_2L: {
                bit_r(L, 2);
                break;
            }
            case INS_BIT_2HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 2);
                break;
            }
            case INS_BIT_2A: {
                bit_r(A, 2);
                break;
            }

            case INS_BIT_3B: {
                bit_r(B, 3);
                break;
            }
            case INS_BIT_3C: {
                bit_r(C, 3);
                break;
            }
            case INS_BIT_3D: {
                bit_r(D, 3);
                break;
            }
            case INS_BIT_3E: {
                bit_r(E, 3);
                break;
            }
            case INS_BIT_3H: {
                bit_r(H, 3);
                break;
            }
            case INS_BIT_3L: {
                bit_r(L, 3);
                break;
            }
            case INS_BIT_3HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 3);
                break;
            }
            case INS_BIT_3A: {
                bit_r(A, 3);
                break;
            }

            case INS_BIT_4B: {
                bit_r(B, 4);
                break;
            }
            case INS_BIT_4C: {
                bit_r(C, 4);
                break;
            }
            case INS_BIT_4D: {
                bit_r(D, 4);
                break;
            }
            case INS_BIT_4E: {
                bit_r(E, 4);
                break;
            }
            case INS_BIT_4H: {
                bit_r(H, 4);
                break;
            }
            case INS_BIT_4L: {
                bit_r(L, 4);
                break;
            }
            case INS_BIT_4HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 4);
                break;
            }
            case INS_BIT_4A: {
                bit_r(A, 4);
                break;
            }

            case INS_BIT_5B: {
                bit_r(B, 5);
                break;
            }
            case INS_BIT_5C: {
                bit_r(C, 5);
                break;
            }
            case INS_BIT_5D: {
                bit_r(D, 5);
                break;
            }
            case INS_BIT_5E: {
                bit_r(E, 5);
                break;
            }
            case INS_BIT_5H: {
                bit_r(H, 5);
                break;
            }
            case INS_BIT_5L: {
                bit_r(L, 5);
                break;
            }
            case INS_BIT_5HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 5);
                break;
            }
            case INS_BIT_5A: {
                bit_r(A, 5);
                break;
            }

            case INS_BIT_6B: {
                bit_r(B, 6);
                break;
            }
            case INS_BIT_6C: {
                bit_r(C, 6);
                break;
            }
            case INS_BIT_6D: {
                bit_r(D, 6);
                break;
            }
            case INS_BIT_6E: {
                bit_r(E, 6);
                break;
            }
            case INS_BIT_6H: {
                bit_r(H, 6);
                break;
            }
            case INS_BIT_6L: {
                bit_r(L, 6);
                break;
            }
            case INS_BIT_6HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 6);
                break;
            }
            case INS_BIT_6A: {
                bit_r(A, 6);
                break;
            }

            case INS_BIT_7B: {
                bit_r(B, 7);
                break;
            }
            case INS_BIT_7C: {
                bit_r(C, 7);
                break;
            }
            case INS_BIT_7D: {
                bit_r(D, 7);
                break;
            }
            case INS_BIT_7E: {
                bit_r(E, 7);
                break;
            }
            case INS_BIT_7H: {
                bit_r(H, 7);
                break;
            }
            case INS_BIT_7L: {
                bit_r(L, 7);
                break;
            }
            case INS_BIT_7HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                bit_r(data, 7);
                break;
            }
            case INS_BIT_7A: {
                bit_r(A, 7);
                break;
            }

            case INS_RES_0B: {
                B = res_r(B, 0);
                break;
            }
            case INS_RES_0C: {
                C = res_r(C, 0);
                break;
            }
            case INS_RES_0D: {
                D = res_r(D, 0);
                break;
            }
            case INS_RES_0E: {
                E = res_r(E, 0);
                break;
            }
            case INS_RES_0H: {
                H = res_r(H, 0);
                break;
            }
            case INS_RES_0L: {
                L = res_r(L, 0);
                break;
            }
            case INS_RES_0HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 0);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_0A: {
                A = res_r(A, 0);
                break;
            }

            case INS_RES_1B: {
                B = res_r(B, 1);
                break;
            }
            case INS_RES_1C: {
                C = res_r(C, 1);
                break;
            }
            case INS_RES_1D: {
                D = res_r(D, 1);
                break;
            }
            case INS_RES_1E: {
                E = res_r(E, 1);
                break;
            }
            case INS_RES_1H: {
                H = res_r(H, 1);
                break;
            }
            case INS_RES_1L: {
                L = res_r(L, 1);
                break;
            }
            case INS_RES_1HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 1);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_1A: {
                A = res_r(A, 1);
                break;
            }

            case INS_RES_2B: {
                B = res_r(B, 2);
                break;
            }
            case INS_RES_2C: {
                C = res_r(C, 2);
                break;
            }
            case INS_RES_2D: {
                D = res_r(D, 2);
                break;
            }
            case INS_RES_2E: {
                E = res_r(E, 2);
                break;
            }
            case INS_RES_2H: {
                H = res_r(H, 2);
                break;
            }
            case INS_RES_2L: {
                L = res_r(L, 2);
                break;
            }
            case INS_RES_2HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 2);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_2A: {
                A = res_r(A, 2);
                break;
            }

            case INS_RES_3B: {
                B = res_r(B, 3);
                break;
            }
            case INS_RES_3C: {
                C = res_r(C, 3);
                break;
            }
            case INS_RES_3D: {
                D = res_r(D, 3);
                break;
            }
            case INS_RES_3E: {
                E = res_r(E, 3);
                break;
            }
            case INS_RES_3H: {
                H = res_r(H, 3);
                break;
            }
            case INS_RES_3L: {
                L = res_r(L, 3);
                break;
            }
            case INS_RES_3HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 3);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_3A: {
                A = res_r(A, 3);
                break;
            }

            case INS_RES_4B: {
                B = res_r(B, 4);
                break;
            }
            case INS_RES_4C: {
                C = res_r(C, 4);
                break;
            }
            case INS_RES_4D: {
                D = res_r(D, 4);
                break;
            }
            case INS_RES_4E: {
                E = res_r(E, 4);
                break;
            }
            case INS_RES_4H: {
                H = res_r(H, 4);
                break;
            }
            case INS_RES_4L: {
                L = res_r(L, 4);
                break;
            }
            case INS_RES_4HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 4);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_4A: {
                A = res_r(A, 4);
                break;
            }

            case INS_RES_5B: {
                B = res_r(B, 5);
                break;
            }
            case INS_RES_5C: {
                C = res_r(C, 5);
                break;
            }
            case INS_RES_5D: {
                D = res_r(D, 5);
                break;
            }
            case INS_RES_5E: {
                E = res_r(E, 5);
                break;
            }
            case INS_RES_5H: {
                H = res_r(H, 5);
                break;
            }
            case INS_RES_5L: {
                L = res_r(L, 5);
                break;
            }
            case INS_RES_5HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 5);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_5A: {
                A = res_r(A, 5);
                break;
            }

            case INS_RES_6B: {
                B = res_r(B, 6);
                break;
            }
            case INS_RES_6C: {
                C = res_r(C, 6);
                break;
            }
            case INS_RES_6D: {
                D = res_r(D, 6);
                break;
            }
            case INS_RES_6E: {
                E = res_r(E, 6);
                break;
            }
            case INS_RES_6H: {
                H = res_r(H, 6);
                break;
            }
            case INS_RES_6L: {
                L = res_r(L, 6);
                break;
            }
            case INS_RES_6HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 6);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_6A: {
                A = res_r(A, 6);
                break;
            }

            case INS_RES_7B: {
                B = res_r(B, 7);
                break;
            }
            case INS_RES_7C: {
                C = res_r(C, 7);
                break;
            }
            case INS_RES_7D: {
                D = res_r(D, 7);
                break;
            }
            case INS_RES_7E: {
                E = res_r(E, 7);
                break;
            }
            case INS_RES_7H: {
                H = res_r(H, 7);
                break;
            }
            case INS_RES_7L: {
                L = res_r(L, 7);
                break;
            }
            case INS_RES_7HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = res_r(data, 7);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_RES_7A: {
                A = res_r(A, 7);
                break;
            }

            case INS_SET_0B: {
                B = set_r(B, 0);
                break;
            }
            case INS_SET_0C: {
                C = set_r(C, 0);
                break;
            }
            case INS_SET_0D: {
                D = set_r(D, 0);
                break;
            }
            case INS_SET_0E: {
                E = set_r(E, 0);
                break;
            }
            case INS_SET_0H: {
                H = set_r(H, 0);
                break;
            }
            case INS_SET_0L: {
                L = set_r(L, 0);
                break;
            }
            case INS_SET_0HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 0);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_0A: {
                A = set_r(A, 0);
                break;
            }

            case INS_SET_1B: {
                B = set_r(B, 1);
                break;
            }
            case INS_SET_1C: {
                C = set_r(C, 1);
                break;
            }
            case INS_SET_1D: {
                D = set_r(D, 1);
                break;
            }
            case INS_SET_1E: {
                E = set_r(E, 1);
                break;
            }
            case INS_SET_1H: {
                H = set_r(H, 1);
                break;
            }
            case INS_SET_1L: {
                L = set_r(L, 1);
                break;
            }
            case INS_SET_1HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 1);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_1A: {
                A = set_r(A, 1);
                break;
            }

            case INS_SET_2B: {
                B = set_r(B, 2);
                break;
            }
            case INS_SET_2C: {
                C = set_r(C, 2);
                break;
            }
            case INS_SET_2D: {
                D = set_r(D, 2);
                break;
            }
            case INS_SET_2E: {
                E = set_r(E, 2);
                break;
            }
            case INS_SET_2H: {
                H = set_r(H, 2);
                break;
            }
            case INS_SET_2L: {
                L = set_r(L, 2);
                break;
            }
            case INS_SET_2HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 2);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_2A: {
                A = set_r(A, 2);
                break;
            }

            case INS_SET_3B: {
                B = set_r(B, 3);
                break;
            }
            case INS_SET_3C: {
                C = set_r(C, 3);
                break;
            }
            case INS_SET_3D: {
                D = set_r(D, 3);
                break;
            }
            case INS_SET_3E: {
                E = set_r(E, 3);
                break;
            }
            case INS_SET_3H: {
                H = set_r(H, 3);
                break;
            }
            case INS_SET_3L: {
                L = set_r(L, 3);
                break;
            }
            case INS_SET_3HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 3);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_3A: {
                A = set_r(A, 3);
                break;
            }

            case INS_SET_4B: {
                B = set_r(B, 4);
                break;
            }
            case INS_SET_4C: {
                C = set_r(C, 4);
                break;
            }
            case INS_SET_4D: {
                D = set_r(D, 4);
                break;
            }
            case INS_SET_4E: {
                E = set_r(E, 4);
                break;
            }
            case INS_SET_4H: {
                H = set_r(H, 4);
                break;
            }
            case INS_SET_4L: {
                L = set_r(L, 4);
                break;
            }
            case INS_SET_4HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 4);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_4A: {
                A = set_r(A, 4);
                break;
            }

            case INS_SET_5B: {
                B = set_r(B, 5);
                break;
            }
            case INS_SET_5C: {
                C = set_r(C, 5);
                break;
            }
            case INS_SET_5D: {
                D = set_r(D, 5);
                break;
            }
            case INS_SET_5E: {
                E = set_r(E, 5);
                break;
            }
            case INS_SET_5H: {
                H = set_r(H, 5);
                break;
            }
            case INS_SET_5L: {
                L = set_r(L, 5);
                break;
            }
            case INS_SET_5HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 5);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_5A: {
                A = set_r(A, 5);
                break;
            }

            case INS_SET_6B: {
                B = set_r(B, 6);
                break;
            }
            case INS_SET_6C: {
                C = set_r(C, 6);
                break;
            }
            case INS_SET_6D: {
                D = set_r(D, 6);
                break;
            }
            case INS_SET_6E: {
                E = set_r(E, 6);
                break;
            }
            case INS_SET_6H: {
                H = set_r(H, 6);
                break;
            }
            case INS_SET_6L: {
                L = set_r(L, 6);
                break;
            }
            case INS_SET_6HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 6);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_6A: {
                A = set_r(A, 6);
                break;
            }

            case INS_SET_7B: {
                B = set_r(B, 7);
                break;
            }
            case INS_SET_7C: {
                C = set_r(C, 7);
                break;
            }
            case INS_SET_7D: {
                D = set_r(D, 7);
                break;
            }
            case INS_SET_7E: {
                E = set_r(E, 7);
                break;
            }
            case INS_SET_7H: {
                H = set_r(H, 7);
                break;
            }
            case INS_SET_7L: {
                L = set_r(L, 7);
                break;
            }
            case INS_SET_7HL: {
                Word addr = L | (H << 8);
                Byte data = read_byte(addr, cycles, mem);
                data = set_r(data, 7);
                write_byte(addr, data, cycles, mem);
                break;
            }
            case INS_SET_7A: {
                A = set_r(A, 7);
                break;
            }

            default: {
                printf("INVALID PREFIX INSTRUCTION\n");
            }
            }
            break;
        }

        default: printf("UNKNOWN INSTRUCTION: %d at %d\n", ins, PC);
        }
}
