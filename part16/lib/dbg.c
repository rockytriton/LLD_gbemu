#include <dbg.h>
#include <bus.h>

static char dbg_msg[1024] = {0};
static int msg_size = 0;

void dbg_update() {
    if (bus_read(0xFF02) == 0x81) {
        char c = bus_read(0xFF01);

        dbg_msg[msg_size++] = c;

        bus_write(0xFF02, 0);
    }
}

void dbg_print() {
    if (dbg_msg[0]) {
        //printf("DBG: %s\n", dbg_msg);
    }
}
