#include <instructions.h>
#include <cpu.h>
#include <bus.h>

instruction instructions[0x100] = {
    [0x00] = {IN_NOP, AM_IMP},
    [0x01] = {IN_LD, AM_R_D16, RT_BC},
    [0x02] = {IN_LD, AM_MR_R, RT_BC, RT_A},
    [0x03] = {IN_INC, AM_R, RT_BC},
    [0x04] = {IN_INC, AM_R, RT_B},
    [0x05] = {IN_DEC, AM_R, RT_B},
    [0x06] = {IN_LD, AM_R_D8, RT_B},
    [0x07] = {IN_RLCA},
    [0x08] = {IN_LD, AM_A16_R, RT_NONE, RT_SP},
    [0x09] = {IN_ADD, AM_R_R, RT_HL, RT_BC},
    [0x0A] = {IN_LD, AM_R_MR, RT_A, RT_BC},
    [0x0B] = {IN_DEC, AM_R, RT_BC},
    [0x0C] = {IN_INC, AM_R, RT_C},
    [0x0D] = {IN_DEC, AM_R, RT_C},
    [0x0E] = {IN_LD, AM_R_D8, RT_C},
    [0x0F] = {IN_RRCA},

    //0x1X
    [0x10] = {IN_STOP},
    [0x11] = {IN_LD, AM_R_D16, RT_DE},
    [0x12] = {IN_LD, AM_MR_R, RT_DE, RT_A},
    [0x13] = {IN_INC, AM_R, RT_DE},
    [0x14] = {IN_INC, AM_R, RT_D},
    [0x15] = {IN_DEC, AM_R, RT_D},
    [0x16] = {IN_LD, AM_R_D8, RT_D},
    [0x17] = {IN_RLA},
    [0x18] = {IN_JR, AM_D8},
    [0x19] = {IN_ADD, AM_R_R, RT_HL, RT_DE},
    [0x1A] = {IN_LD, AM_R_MR, RT_A, RT_DE},
    [0x1B] = {IN_DEC, AM_R, RT_DE},
    [0x1C] = {IN_INC, AM_R, RT_E},
    [0x1D] = {IN_DEC, AM_R, RT_E},
    [0x1E] = {IN_LD, AM_R_D8, RT_E},
    [0x1F] = {IN_RRA},

    //0x2X
    [0x20] = {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NZ},
    [0x21] = {IN_LD, AM_R_D16, RT_HL},
    [0x22] = {IN_LD, AM_HLI_R, RT_HL, RT_A},
    [0x23] = {IN_INC, AM_R, RT_HL},
    [0x24] = {IN_INC, AM_R, RT_H},
    [0x25] = {IN_DEC, AM_R, RT_H},
    [0x26] = {IN_LD, AM_R_D8, RT_H},
    [0x27] = {IN_DAA},
    [0x28] = {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_Z},
    [0x29] = {IN_ADD, AM_R_R, RT_HL, RT_HL},
    [0x2A] = {IN_LD, AM_R_HLI, RT_A, RT_HL},
    [0x2B] = {IN_DEC, AM_R, RT_HL},
    [0x2C] = {IN_INC, AM_R, RT_L},
    [0x2D] = {IN_DEC, AM_R, RT_L},
    [0x2E] = {IN_LD, AM_R_D8, RT_L},
    [0x2F] = {IN_CPL},

    //0x3X
    [0x30] = {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NC},
    [0x31] = {IN_LD, AM_R_D16, RT_SP},
    [0x32] = {IN_LD, AM_HLD_R, RT_HL, RT_A},
    [0x33] = {IN_INC, AM_R, RT_SP},
    [0x34] = {IN_INC, AM_MR, RT_HL},
    [0x35] = {IN_DEC, AM_MR, RT_HL},
    [0x36] = {IN_LD, AM_MR_D8, RT_HL},
    [0x37] = {IN_SCF},
    [0x38] = {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_C},
    [0x39] = {IN_ADD, AM_R_R, RT_HL, RT_SP},
    [0x3A] = {IN_LD, AM_R_HLD, RT_A, RT_HL},
    [0x3B] = {IN_DEC, AM_R, RT_SP},
    [0x3C] = {IN_INC, AM_R, RT_A},
    [0x3D] = {IN_DEC, AM_R, RT_A},
    [0x3E] = {IN_LD, AM_R_D8, RT_A},
    [0x3F] = {IN_CCF},

    //0x4X
    [0x40] = {IN_LD, AM_R_R, RT_B, RT_B},
    [0x41] = {IN_LD, AM_R_R, RT_B, RT_C},
    [0x42] = {IN_LD, AM_R_R, RT_B, RT_D},
    [0x43] = {IN_LD, AM_R_R, RT_B, RT_E},
    [0x44] = {IN_LD, AM_R_R, RT_B, RT_H},
    [0x45] = {IN_LD, AM_R_R, RT_B, RT_L},
    [0x46] = {IN_LD, AM_R_MR, RT_B, RT_HL},
    [0x47] = {IN_LD, AM_R_R, RT_B, RT_A},
    [0x48] = {IN_LD, AM_R_R, RT_C, RT_B},
    [0x49] = {IN_LD, AM_R_R, RT_C, RT_C},
    [0x4A] = {IN_LD, AM_R_R, RT_C, RT_D},
    [0x4B] = {IN_LD, AM_R_R, RT_C, RT_E},
    [0x4C] = {IN_LD, AM_R_R, RT_C, RT_H},
    [0x4D] = {IN_LD, AM_R_R, RT_C, RT_L},
    [0x4E] = {IN_LD, AM_R_MR, RT_C, RT_HL},
    [0x4F] = {IN_LD, AM_R_R, RT_C, RT_A},

    //0x5X
    [0x50] = {IN_LD, AM_R_R,  RT_D, RT_B},
    [0x51] = {IN_LD, AM_R_R,  RT_D, RT_C},
    [0x52] = {IN_LD, AM_R_R,  RT_D, RT_D},
    [0x53] = {IN_LD, AM_R_R,  RT_D, RT_E},
    [0x54] = {IN_LD, AM_R_R,  RT_D, RT_H},
    [0x55] = {IN_LD, AM_R_R,  RT_D, RT_L},
    [0x56] = {IN_LD, AM_R_MR, RT_D, RT_HL},
    [0x57] = {IN_LD, AM_R_R,  RT_D, RT_A},
    [0x58] = {IN_LD, AM_R_R,  RT_E, RT_B},
    [0x59] = {IN_LD, AM_R_R,  RT_E, RT_C},
    [0x5A] = {IN_LD, AM_R_R,  RT_E, RT_D},
    [0x5B] = {IN_LD, AM_R_R,  RT_E, RT_E},
    [0x5C] = {IN_LD, AM_R_R,  RT_E, RT_H},
    [0x5D] = {IN_LD, AM_R_R,  RT_E, RT_L},
    [0x5E] = {IN_LD, AM_R_MR, RT_E, RT_HL},
    [0x5F] = {IN_LD, AM_R_R,  RT_E, RT_A},

    //0x6X
    [0x60] = {IN_LD, AM_R_R,  RT_H, RT_B},
    [0x61] = {IN_LD, AM_R_R,  RT_H, RT_C},
    [0x62] = {IN_LD, AM_R_R,  RT_H, RT_D},
    [0x63] = {IN_LD, AM_R_R,  RT_H, RT_E},
    [0x64] = {IN_LD, AM_R_R,  RT_H, RT_H},
    [0x65] = {IN_LD, AM_R_R,  RT_H, RT_L},
    [0x66] = {IN_LD, AM_R_MR, RT_H, RT_HL},
    [0x67] = {IN_LD, AM_R_R,  RT_H, RT_A},
    [0x68] = {IN_LD, AM_R_R,  RT_L, RT_B},
    [0x69] = {IN_LD, AM_R_R,  RT_L, RT_C},
    [0x6A] = {IN_LD, AM_R_R,  RT_L, RT_D},
    [0x6B] = {IN_LD, AM_R_R,  RT_L, RT_E},
    [0x6C] = {IN_LD, AM_R_R,  RT_L, RT_H},
    [0x6D] = {IN_LD, AM_R_R,  RT_L, RT_L},
    [0x6E] = {IN_LD, AM_R_MR, RT_L, RT_HL},
    [0x6F] = {IN_LD, AM_R_R,  RT_L, RT_A},

    //0x7X
    [0x70] = {IN_LD, AM_MR_R,  RT_HL, RT_B},
    [0x71] = {IN_LD, AM_MR_R,  RT_HL, RT_C},
    [0x72] = {IN_LD, AM_MR_R,  RT_HL, RT_D},
    [0x73] = {IN_LD, AM_MR_R,  RT_HL, RT_E},
    [0x74] = {IN_LD, AM_MR_R,  RT_HL, RT_H},
    [0x75] = {IN_LD, AM_MR_R,  RT_HL, RT_L},
    [0x76] = {IN_HALT},
    [0x77] = {IN_LD, AM_MR_R,  RT_HL, RT_A},
    [0x78] = {IN_LD, AM_R_R,  RT_A, RT_B},
    [0x79] = {IN_LD, AM_R_R,  RT_A, RT_C},
    [0x7A] = {IN_LD, AM_R_R,  RT_A, RT_D},
    [0x7B] = {IN_LD, AM_R_R,  RT_A, RT_E},
    [0x7C] = {IN_LD, AM_R_R,  RT_A, RT_H},
    [0x7D] = {IN_LD, AM_R_R,  RT_A, RT_L},
    [0x7E] = {IN_LD, AM_R_MR, RT_A, RT_HL},
    [0x7F] = {IN_LD, AM_R_R,  RT_A, RT_A},

    //0x8X
    [0x80] = {IN_ADD, AM_R_R, RT_A, RT_B},
    [0x81] = {IN_ADD, AM_R_R, RT_A, RT_C},
    [0x82] = {IN_ADD, AM_R_R, RT_A, RT_D},
    [0x83] = {IN_ADD, AM_R_R, RT_A, RT_E},
    [0x84] = {IN_ADD, AM_R_R, RT_A, RT_H},
    [0x85] = {IN_ADD, AM_R_R, RT_A, RT_L},
    [0x86] = {IN_ADD, AM_R_MR, RT_A, RT_HL},
    [0x87] = {IN_ADD, AM_R_R, RT_A, RT_A},
    [0x88] = {IN_ADC, AM_R_R, RT_A, RT_B},
    [0x89] = {IN_ADC, AM_R_R, RT_A, RT_C},
    [0x8A] = {IN_ADC, AM_R_R, RT_A, RT_D},
    [0x8B] = {IN_ADC, AM_R_R, RT_A, RT_E},
    [0x8C] = {IN_ADC, AM_R_R, RT_A, RT_H},
    [0x8D] = {IN_ADC, AM_R_R, RT_A, RT_L},
    [0x8E] = {IN_ADC, AM_R_MR, RT_A, RT_HL},
    [0x8F] = {IN_ADC, AM_R_R, RT_A, RT_A},

    //0x9X
    [0x90] = {IN_SUB, AM_R_R, RT_A, RT_B},
    [0x91] = {IN_SUB, AM_R_R, RT_A, RT_C},
    [0x92] = {IN_SUB, AM_R_R, RT_A, RT_D},
    [0x93] = {IN_SUB, AM_R_R, RT_A, RT_E},
    [0x94] = {IN_SUB, AM_R_R, RT_A, RT_H},
    [0x95] = {IN_SUB, AM_R_R, RT_A, RT_L},
    [0x96] = {IN_SUB, AM_R_MR, RT_A, RT_HL},
    [0x97] = {IN_SUB, AM_R_R, RT_A, RT_A},
    [0x98] = {IN_SBC, AM_R_R, RT_A, RT_B},
    [0x99] = {IN_SBC, AM_R_R, RT_A, RT_C},
    [0x9A] = {IN_SBC, AM_R_R, RT_A, RT_D},
    [0x9B] = {IN_SBC, AM_R_R, RT_A, RT_E},
    [0x9C] = {IN_SBC, AM_R_R, RT_A, RT_H},
    [0x9D] = {IN_SBC, AM_R_R, RT_A, RT_L},
    [0x9E] = {IN_SBC, AM_R_MR, RT_A, RT_HL},
    [0x9F] = {IN_SBC, AM_R_R, RT_A, RT_A},


    //0xAX
    [0xA0] = {IN_AND, AM_R_R, RT_A, RT_B},
    [0xA1] = {IN_AND, AM_R_R, RT_A, RT_C},
    [0xA2] = {IN_AND, AM_R_R, RT_A, RT_D},
    [0xA3] = {IN_AND, AM_R_R, RT_A, RT_E},
    [0xA4] = {IN_AND, AM_R_R, RT_A, RT_H},
    [0xA5] = {IN_AND, AM_R_R, RT_A, RT_L},
    [0xA6] = {IN_AND, AM_R_MR, RT_A, RT_HL},
    [0xA7] = {IN_AND, AM_R_R, RT_A, RT_A},
    [0xA8] = {IN_XOR, AM_R_R, RT_A, RT_B},
    [0xA9] = {IN_XOR, AM_R_R, RT_A, RT_C},
    [0xAA] = {IN_XOR, AM_R_R, RT_A, RT_D},
    [0xAB] = {IN_XOR, AM_R_R, RT_A, RT_E},
    [0xAC] = {IN_XOR, AM_R_R, RT_A, RT_H},
    [0xAD] = {IN_XOR, AM_R_R, RT_A, RT_L},
    [0xAE] = {IN_XOR, AM_R_MR, RT_A, RT_HL},
    [0xAF] = {IN_XOR, AM_R_R, RT_A, RT_A},

    //0xBX
    [0xB0] = {IN_OR, AM_R_R, RT_A, RT_B},
    [0xB1] = {IN_OR, AM_R_R, RT_A, RT_C},
    [0xB2] = {IN_OR, AM_R_R, RT_A, RT_D},
    [0xB3] = {IN_OR, AM_R_R, RT_A, RT_E},
    [0xB4] = {IN_OR, AM_R_R, RT_A, RT_H},
    [0xB5] = {IN_OR, AM_R_R, RT_A, RT_L},
    [0xB6] = {IN_OR, AM_R_MR, RT_A, RT_HL},
    [0xB7] = {IN_OR, AM_R_R, RT_A, RT_A},
    [0xB8] = {IN_CP, AM_R_R, RT_A, RT_B},
    [0xB9] = {IN_CP, AM_R_R, RT_A, RT_C},
    [0xBA] = {IN_CP, AM_R_R, RT_A, RT_D},
    [0xBB] = {IN_CP, AM_R_R, RT_A, RT_E},
    [0xBC] = {IN_CP, AM_R_R, RT_A, RT_H},
    [0xBD] = {IN_CP, AM_R_R, RT_A, RT_L},
    [0xBE] = {IN_CP, AM_R_MR, RT_A, RT_HL},
    [0xBF] = {IN_CP, AM_R_R, RT_A, RT_A},

    [0xC0] = {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NZ},
    [0xC1] = {IN_POP, AM_R, RT_BC},
    [0xC2] = {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    [0xC3] = {IN_JP, AM_D16},
    [0xC4] = {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    [0xC5] = {IN_PUSH, AM_R, RT_BC},
    [0xC6] = {IN_ADD, AM_R_D8, RT_A},
    [0xC7] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00},
    [0xC8] = {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_Z},
    [0xC9] = {IN_RET},
    [0xCA] = {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_Z},
    [0xCB] = {IN_CB, AM_D8},
    [0xCC] = {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_Z},
    [0xCD] = {IN_CALL, AM_D16},
    [0xCE] = {IN_ADC, AM_R_D8, RT_A},
    [0xCF] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x08},

    [0xD0] = {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NC},
    [0xD1] = {IN_POP, AM_R, RT_DE},
    [0xD2] = {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NC},
    [0xD4] = {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NC},
    [0xD5] = {IN_PUSH, AM_R, RT_DE},
    [0xD6] = {IN_SUB, AM_R_D8, RT_A},
    [0xD7] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x10},
    [0xD8] = {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_C},
    [0xD9] = {IN_RETI},
    [0xDA] = {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_C},
    [0xDC] = {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_C},
    [0xDE] = {IN_SBC, AM_R_D8, RT_A},
    [0xDF] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x18},

    //0xEX
    [0xE0] = {IN_LDH, AM_A8_R, RT_NONE, RT_A},
    [0xE1] = {IN_POP, AM_R, RT_HL},
    [0xE2] = {IN_LD, AM_MR_R, RT_C, RT_A},
    [0xE5] = {IN_PUSH, AM_R, RT_HL},
    [0xE6] = {IN_AND, AM_R_D8, RT_A},
    [0xE7] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x20},
    [0xE8] = {IN_ADD, AM_R_D8, RT_SP},
    [0xE9] = {IN_JP, AM_R, RT_HL},
    [0xEA] = {IN_LD, AM_A16_R, RT_NONE, RT_A},
    [0xEE] = {IN_XOR, AM_R_D8, RT_A},
    [0xEF] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x28},


    //0xFX
    [0xF0] = {IN_LDH, AM_R_A8, RT_A},
    [0xF1] = {IN_POP, AM_R, RT_AF},
    [0xF2] = {IN_LD, AM_R_MR, RT_A, RT_C},
    [0xF3] = {IN_DI},
    [0xF5] = {IN_PUSH, AM_R, RT_AF},
    [0xF6] = {IN_OR, AM_R_D8, RT_A},
    [0xF7] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x30},
    [0xF8] = {IN_LD, AM_HL_SPR, RT_HL, RT_SP},
    [0xF9] = {IN_LD, AM_R_R, RT_SP, RT_HL},
    [0xFA] = {IN_LD, AM_R_A16, RT_A},
    [0xFB] = {IN_EI},
    [0xFE] = {IN_CP, AM_R_D8, RT_A},
    [0xFF] = {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x38},
};



instruction *instruction_by_opcode(u8 opcode) {
    return &instructions[opcode];
}

char *inst_lookup[] = {
    "<NONE>",
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "POP",
    "JP",
    "PUSH",
    "RET",
    "CB",
    "CALL",
    "RETI",
    "LDH",
    "JPHL",
    "DI",
    "EI",
    "RST",
    "IN_ERR",
    "IN_RLC", 
    "IN_RRC",
    "IN_RL", 
    "IN_RR",
    "IN_SLA", 
    "IN_SRA",
    "IN_SWAP", 
    "IN_SRL",
    "IN_BIT", 
    "IN_RES", 
    "IN_SET"
};

char *inst_name(in_type t) {
    return inst_lookup[t];
}

static char *rt_lookup[] = {
    "<NONE>",
    "A",
    "F",
    "B",
    "C",
    "D",
    "E",
    "H",
    "L",
    "AF",
    "BC",
    "DE",
    "HL",
    "SP",
    "PC"
};

void inst_to_str(cpu_context *ctx, char *str) {
    instruction *inst = ctx->cur_inst;
    sprintf(str, "%s ", inst_name(inst->type));

    switch(inst->mode) {
        case AM_IMP:
            return;

        case AM_R_D16:
        case AM_R_A16:
            sprintf(str, "%s %s,$%04X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data);
            return;

        case AM_R:
            sprintf(str, "%s %s", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_R: 
            sprintf(str, "%s %s,%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR_R:
            sprintf(str, "%s (%s),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR:
            sprintf(str, "%s (%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_MR:
            sprintf(str, "%s %s,(%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_D8:
        case AM_R_A8:
            sprintf(str, "%s %s,$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_R_HLI:
            sprintf(str, "%s %s,(%s+)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_HLD:
            sprintf(str, "%s %s,(%s-)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLI_R:
            sprintf(str, "%s (%s+),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLD_R:
            sprintf(str, "%s (%s-),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_A8_R:
            sprintf(str, "%s $%02X,%s", inst_name(inst->type), 
                bus_read(ctx->regs.pc - 1), rt_lookup[inst->reg_2]);

            return;

        case AM_HL_SPR:
            sprintf(str, "%s (%s),SP+%d", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_D8:
            sprintf(str, "%s $%02X", inst_name(inst->type), 
                ctx->fetched_data & 0xFF);
            return;

        case AM_D16:
            sprintf(str, "%s $%04X", inst_name(inst->type), 
                ctx->fetched_data);
            return;

        case AM_MR_D8:
            sprintf(str, "%s (%s),$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_A16_R:
            sprintf(str, "%s ($%04X),%s", inst_name(inst->type), 
                ctx->fetched_data, rt_lookup[inst->reg_2]);
            return;

        default:
            fprintf(stderr, "INVALID AM: %d\n", inst->mode);
            NO_IMPL
    }
}