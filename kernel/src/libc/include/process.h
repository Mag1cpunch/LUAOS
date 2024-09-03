#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    int64_t rax;
    int64_t rbx;
    int64_t rcx;
    int64_t rdx;
    
    int64_t rsp;
    int64_t rbp;

    int64_t rip;

    int64_t rflags;
} process_regs_t;

typedef struct {
    uint16_t pid;
    uint8_t priority;
    uint16_t time_slice;
    process_regs_t *registers;
    void *text;
    void *stack;
    size_t code_size;
    void *heap;
} process_t;

void execute_process(process_t *process);

#endif