#ifndef ASM_H
#define ASM_H

static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}
static void disable_ints(void) {
    asm ("cli");
}
static void enable_ints(void) {
    asm ("sti");
}

#endif