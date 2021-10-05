#include <cpu.h>
#include <bus.h>
#include <emu.h>
#include <interrupts.h>

cpu_context ctx = {0};

void cpu_init() {
    ctx.regs.pc = 0x100;
    ctx.regs.a = 0x01;
}

static void fetch_instruction() {
    ctx.cur_opcode = bus_read(ctx.regs.pc++);
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);
}

void fetch_data();

static void execute() {
    IN_PROC proc = inst_get_processor(ctx.cur_inst->type);

    if (!proc) {
        NO_IMPL
    }

    proc(&ctx);
}

bool cpu_step() {
    
    if (!ctx.halted) {
        u16 pc = ctx.regs.pc;

        fetch_instruction();
        emu_cycles(1);
        fetch_data();

        char flags[16];
        sprintf(flags, "%c%c%c%c", 
            ctx.regs.f & (1 << 7) ? 'Z' : '-',
            ctx.regs.f & (1 << 6) ? 'N' : '-',
            ctx.regs.f & (1 << 5) ? 'H' : '-',
            ctx.regs.f & (1 << 4) ? 'C' : '-'
        );

        printf("%08lX - %04X: %-7s (%02X %02X %02X) A: %02X F: %s BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
            emu_get_context()->ticks,
            pc, inst_name(ctx.cur_inst->type), ctx.cur_opcode,
            bus_read(pc + 1), bus_read(pc + 2), ctx.regs.a, flags, ctx.regs.b, ctx.regs.c,
            ctx.regs.d, ctx.regs.e, ctx.regs.h, ctx.regs.l);

        if (ctx.cur_inst == NULL) {
            printf("Unknown Instruction! %02X\n", ctx.cur_opcode);
            exit(-7);
        }

        execute();
    } else {
        //is halted...
        emu_cycles(1);

        if (ctx.int_flags) {
            ctx.halted = false;
        }
    }

    if (ctx.int_master_enabled) {
        cpu_handle_interrupts(&ctx);
        ctx.enabling_ime = false;
    }

    if (ctx.enabling_ime) {
        ctx.int_master_enabled = true;
    }

    return true;
}

u8 cpu_get_ie_register() {
    return ctx.ie_register;
}

void cpu_set_ie_register(u8 n) {
    ctx.ie_register = n;
}

