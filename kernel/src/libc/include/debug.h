#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void qemu_debug_putc(char c);
void qemu_send_msg(const char *s);
void qemu_writeline(const char *str);
void perror(char* err);

#endif