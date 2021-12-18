
#pragma once

#include <cpu.h>

typedef enum {
    IT_VBLANK = 1,
    IT_LCD_STAT = 2,
    IT_TIMER = 4,
    IT_SERIAL = 8,
    IT_JOYPAD = 16
} interrupt_type;

void cpu_request_interrupt(interrupt_type t);

void cpu_handle_interrupts(cpu_context *ctx);
