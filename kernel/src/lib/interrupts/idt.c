#include "../../libc/include/idt.h"
#include "../../libc/include/asm.h"
#include <stdint.h>

#define KERNEL_CODE_SEGMENT 0x28

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idt_descriptor;
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq33();
extern void irq44();

void set_idt_entry(int vector, void (*isr)(), uint8_t type_attr) {
    idt[vector].offset_1 = (uint16_t)((uint64_t)isr & 0xFFFF);
    idt[vector].selector = KERNEL_CODE_SEGMENT;
    idt[vector].ist = 0;  // Typically 0 unless using an alternate stack
    idt[vector].type_attributes = type_attr;
    idt[vector].offset_2 = (uint16_t)(((uint64_t)isr >> 16) & 0xFFFF);
    idt[vector].offset_3 = (uint32_t)(((uint64_t)isr >> 32) & 0xFFFFFFFF);
    idt[vector].zero = 0;
}

void load_idt() {
    idt_descriptor.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idt_descriptor.base = (uint64_t)&idt;

    asm volatile ("lidt %0" : : "m"(idt_descriptor));
}

void setup_reserved_ints() 
{
    set_idt_entry(0, isr0, IDT_INTERRUPT_GATE);
    set_idt_entry(1, isr1, IDT_TRAP_GATE);
    set_idt_entry(2, isr2, IDT_INTERRUPT_GATE);
    set_idt_entry(3, isr3, IDT_TRAP_GATE);
    set_idt_entry(4, isr4, IDT_TRAP_GATE);
    set_idt_entry(5, isr5, IDT_INTERRUPT_GATE);
    set_idt_entry(6, isr6, IDT_INTERRUPT_GATE);
    set_idt_entry(7, isr7, IDT_INTERRUPT_GATE);
    set_idt_entry(8, isr8, IDT_INTERRUPT_GATE);
    set_idt_entry(9, isr9, IDT_INTERRUPT_GATE);
    set_idt_entry(10, isr10, IDT_INTERRUPT_GATE);
    set_idt_entry(11, isr11, IDT_INTERRUPT_GATE);
    set_idt_entry(12, isr12, IDT_INTERRUPT_GATE);
    set_idt_entry(13, isr13, IDT_INTERRUPT_GATE);
    set_idt_entry(14, isr14, IDT_INTERRUPT_GATE);
    set_idt_entry(15, isr15, IDT_INTERRUPT_GATE);
    set_idt_entry(16, isr16, IDT_INTERRUPT_GATE);
    set_idt_entry(17, isr17, IDT_INTERRUPT_GATE);
    set_idt_entry(18, isr18, IDT_INTERRUPT_GATE);
    set_idt_entry(19, isr19, IDT_INTERRUPT_GATE);
    set_idt_entry(20, isr20, IDT_INTERRUPT_GATE);
    set_idt_entry(21, isr21, IDT_INTERRUPT_GATE);
    set_idt_entry(22, isr22, IDT_INTERRUPT_GATE);
    set_idt_entry(23, isr23, IDT_INTERRUPT_GATE);
    set_idt_entry(24, isr24, IDT_INTERRUPT_GATE);
    set_idt_entry(25, isr25, IDT_INTERRUPT_GATE);
    set_idt_entry(26, isr26, IDT_INTERRUPT_GATE);
    set_idt_entry(27, isr27, IDT_INTERRUPT_GATE);
    set_idt_entry(28, isr28, IDT_INTERRUPT_GATE);
    set_idt_entry(29, isr29, IDT_INTERRUPT_GATE);
    set_idt_entry(30, isr30, IDT_INTERRUPT_GATE);
    set_idt_entry(31, isr31, IDT_INTERRUPT_GATE);
    set_idt_entry(33, irq33, IDT_INTERRUPT_GATE);
    set_idt_entry(44, irq44, IDT_INTERRUPT_GATE);
}

void idt_init() 
{
    disable_ints();
    setup_reserved_ints();
    load_idt();
    enable_ints();
}