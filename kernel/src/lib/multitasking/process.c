#include "../../libc/include/process.h"

void execute_process(process_t *process) 
{
    asm volatile (
        "call *%0" 
        : 
        : "r"(process->text)
    );
}