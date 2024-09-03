#include "../../libc/include/debug.h"
#include "../../libc/include/ioport.h"
#include <stddef.h>

#define QEMU_DEBUG_PORT 0x2F8 

void qemu_debug_putc(char c) {
    if (c == NULL) {
        qemu_writeline("Exception: NULL value cannot be written to debug");
        return;
    }
    while (serial_is_transmit_fifo_empty() == 0);
    outb(SERIAL_PORT, c);
}

void qemu_send_msg(const char *str) {
    while (*str) {
        qemu_debug_putc(*str++);
    }
}
void qemu_writeline(const char *str) {
    qemu_send_msg(str); qemu_send_msg("\n");
}

void perror(char* err) {
    qemu_send_msg("Exception: "); qemu_send_msg(err); qemu_send_msg("\n");
}