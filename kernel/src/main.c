#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "libc/include/string.h"
#include "libc/include/ioport.h"
#include "libc/include/debug.h"
#include "libc/include/heap.h"
#include "libc/include/asm.h"
#include "libc/include/process.h"
#include "libc/include/idt.h"

// Set the base revision to 2, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.

void test() 
{
    qemu_writeline("Hello, World from process!");
}

void kmain(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    serial_init();

    init_memory_pool();
    idt_init();
    qemu_writeline("Allocating memory...");
    char *str = malloc(5 * sizeof(char));
    if (str == NULL) {
        qemu_writeline("Failed to allocate memory");
        hcf();
    }
    qemu_writeline("Successfully allocated");
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    qemu_writeline("Writing string...");
    qemu_writeline(str);
    qemu_writeline("Freeing memory...");
    free(str);
    if (str == NULL) {
        qemu_writeline("String is null");
        hcf();
    }

    asm volatile (
        "mov $0, %eax\n"
        "int $128"
    );

    process_t *proc = malloc(sizeof(process_t));
    proc->text = (void *)test;
    proc->heap = malloc(1024);
    proc->registers = malloc(sizeof(process_regs_t));
    proc->stack = malloc(1024);

    execute_process(proc);

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    for (size_t i = 0; i < 100; i++) {
        volatile uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }

    // We're done, just hang...
    hcf();
}
