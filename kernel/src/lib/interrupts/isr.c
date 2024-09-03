#include "../../libc/include/debug.h"
#include "../../libc/include/asm.h"
#include "../../libc/include/int.h"
#include "../../libc/include/ioport.h"
#include "../../libc/include/idt.h"

void handle_syscalls(Regs_t* r) 
{
    if (r->rax == 0) // Set syscall handling mode, 0 - Default, 1 - MSDOS 
    {
        qemu_send_msg("Syscall 0: Not implemented");
    }
}

void handle_ints(Regs_t* r) 
{
    if (r->int_no == 0) {
        qemu_send_msg("Fatal Exception: Divide by zero, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 1) {
        qemu_send_msg("Exception: Debug, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
    }
    else if (r->int_no == 2) {
        qemu_send_msg("Fatal Exception: Non-maskable Interrupt, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 3) {
        qemu_writeline("Stopped Execution: Breakpoint");
        asm ("hlt");
    }
    else if (r->int_no == 4) {
        qemu_send_msg("Exception: Overflow, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 5) {
        qemu_send_msg("Fatal Exception: Bound range exceeded, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 6) {
        qemu_send_msg("Fatal Exception: Invalid OPCode, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 7) {
        qemu_send_msg("Fatal Exception: Device Not Available, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 8) {
        qemu_send_msg("Fatal Exception: Double Fault, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 9) {
        qemu_send_msg("Fatal Exception: Coprocessor Segment Overrun, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 10) {
        qemu_send_msg("Fatal Exception: Invalid TSS, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 11) {
        qemu_send_msg("Fatal Exception: Segment Not Present, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 12) {
        qemu_send_msg("Fatal Exception: Stack-Segment Fault, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 13) {
        qemu_send_msg("Fatal Exception: General Protection Fault, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 14) {
        qemu_send_msg("Fatal Exception: Page Fault, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 16) {
        qemu_send_msg("Fatal Exception: x87 Floating-Point Exception, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 17) {
        qemu_send_msg("Fatal Exception: Alignment Check, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 18) {
        qemu_send_msg("Fatal Exception: Machine Check, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no == 19) {
        qemu_send_msg("Fatal Exception: SIMD Floating-Point Exception, Error code: "); qemu_send_msg(to_string((int)r->err_code)); qemu_send_msg("\n");
        hcf();
    }
    else if (r->int_no > 19 && r->int_no < 32)
        qemu_writeline("Got architecture reserved interrupt, nothing to do");
    else if (r->int_no == 128)
        handle_syscalls(r);
    else {
        qemu_send_msg("Interrupt "); qemu_send_msg(to_string((int)r->int_no)); qemu_send_msg("is not implemented"); qemu_send_msg("\n");
    }
}

void handle_irqs(Regs_t* r) 
{
    if (r->int_no == 33) {
        qemu_writeline("Got reserved for keyboard interrupt");
    }
    else if (r->int_no == 44) {
        qemu_writeline("Got reserved for ps/2 mouse interrupt");
    }
}