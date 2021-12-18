#include <timer.h>
#include <interrupts.h>

static timer_context ctx = {0};

timer_context *timer_get_context() {
    return &ctx;
}

void timer_init() {
    ctx.div = 0xAC00;
}

void timer_tick() {
    u16 prev_div = ctx.div;

    ctx.div++;

    bool timer_update = false;

    switch(ctx.tac & (0b11)) {
        case 0b00:
            timer_update = (prev_div & (1 << 9)) && (!(ctx.div & (1 << 9)));
            break;
        case 0b01:
            timer_update = (prev_div & (1 << 3)) && (!(ctx.div & (1 << 3)));
            break;
        case 0b10:
            timer_update = (prev_div & (1 << 5)) && (!(ctx.div & (1 << 5)));
            break;
        case 0b11:
            timer_update = (prev_div & (1 << 7)) && (!(ctx.div & (1 << 7)));
            break;
    }

    if (timer_update && ctx.tac & (1 << 2)) {
        ctx.tima++;

        if (ctx.tima == 0xFF) {
            ctx.tima = ctx.tma;

            cpu_request_interrupt(IT_TIMER);
        }
    }
}

void timer_write(u16 address, u8 value) {
    switch(address) {
        case 0xFF04:
            //DIV
            ctx.div = 0;
            break;

        case 0xFF05:
            //TIMA
            ctx.tima = value;
            break;

        case 0xFF06:
            //TMA
            ctx.tma = value;
            break;

        case 0xFF07:
            //TAC
            ctx.tac = value;
            break;
    }
}

u8 timer_read(u16 address) {
    switch(address) {
        case 0xFF04:
            return ctx.div >> 8;
        case 0xFF05:
            return ctx.tima;
        case 0xFF06:
            return ctx.tma;
        case 0xFF07:
            return ctx.tac;
    }
}