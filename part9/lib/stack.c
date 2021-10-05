#include <stack.h>
#include <cpu.h>
#include <bus.h>

/*
    STACK

    SP=0xDFFF

    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 00
    0xDFFE: 00
    0xDFFF: 00 <- SP

    PUSH 0x55

    SP-- = 0xDFFE
    MEMORY[0xDFFE] = 0x55

    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 00
    0xDFFE: 55 <- SP
    0xDFFF: 00

    PUSH 0x77

    SP-- = 0xDFFD
    MEMORY[0xDFFD] = 0x77

    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 77 <- SP
    0xDFFE: 55
    0xDFFF: 00

    val = POP

    val = MEMORY[0xDFFD] = 0x77
    SP++ = 0xDFFE

    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 77 
    0xDFFE: 55 <- SP
    0xDFFF: 00


    PUSH 0x88

    SP-- = 0xDFFD
    MEMORY[0xDFFD] = 0x88

    MEMORY:
    0xDFF7: 00
    0xDFF8: 00
    0xDFF9: 00
    0xDFFA: 00
    0xDFFB: 00
    0xDFFC: 00
    0xDFFD: 88 <- SP
    0xDFFE: 55 
    0xDFFF: 00
*/

void stack_push(u8 data) {
    cpu_get_regs()->sp--;
    bus_write(cpu_get_regs()->sp, data);
}

void stack_push16(u16 data) {
    stack_push((data >> 8) & 0xFF);
    stack_push(data & 0xFF);
}

u8 stack_pop() {
    return bus_read(cpu_get_regs()->sp++);
}

u16 stack_pop16() {
    u16 lo = stack_pop();
    u16 hi = stack_pop();

    return (hi << 8) | lo;
}
