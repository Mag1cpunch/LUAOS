section .text

global isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7
global isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15
global isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23
global isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
global irq33, irq44

extern handle_ints
extern handle_irqs

%macro pushlr 0
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro poplr 0
    add rsp, 8
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro isr_no_error 1
    isr%+%1:
        push 0                ; error_code
        push %1               ; int_num
        jmp isr_common_stub
%endmacro

%macro isr_with_error 1
    isr%+%1:
        push %1               ; int_num (error code is already pushed by CPU)
        jmp isr_common_stub
%endmacro

%macro irq_no_error 1
    irq%+%1:
        push %1               ; IRQ number
        jmp irq_common_stub
%endmacro

isr_common_stub:
    pushlr

    mov rdi, rsp
    call handle_ints

    poplr

    add rsp, 16

    iretq

irq_common_stub:
    pushlr

    mov rdi, rsp
    call handle_irqs

    poplr

    add rsp, 16

    iretq
; Interrupts without error codes
isr_no_error 0
isr_no_error 1
isr_no_error 2
isr_no_error 3
isr_no_error 4
isr_no_error 5
isr_no_error 6
isr_no_error 7
isr_no_error 9
isr_no_error 15
isr_no_error 16
isr_no_error 21
isr_no_error 22
isr_no_error 23
isr_no_error 24
isr_no_error 25
isr_no_error 26
isr_no_error 27
isr_no_error 28
isr_no_error 29
isr_no_error 31

; Interrupts with error codes
isr_with_error 8
isr_with_error 10
isr_with_error 11
isr_with_error 12
isr_with_error 13
isr_with_error 14
isr_with_error 17
isr_with_error 18
isr_with_error 19
isr_with_error 20
isr_with_error 30

irq_no_error 33 ; reserved for keyboard
irq_no_error 44 ; reserved for ps/2 mouse
