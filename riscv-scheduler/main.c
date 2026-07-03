#include "os.h"

void uart_putc(char c) {
    volatile char *uart = (volatile char *)UART0_BASE;
    *uart = c;
}

void uart_puts(char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

// Simple delay function since we don't have standard library
void delay() {
    for (volatile int i = 0; i < 5000000; i++);
}

void task1() {
    while (1) {
        uart_puts("Task 1 is running...\n");
        delay();
    }
}

void task2() {
    while (1) {
        uart_puts("Task 2 is running...\n");
        delay();
    }
}

void task3() {
    while (1) {
        uart_puts("Task 3 is running...\n");
        delay();
    }
}

extern void init_task(int id, void (*task_func)());

void os_main() {
    uart_puts("RISC-V Bare-metal OS Starting...\n");

    // Set the trap vector address
    extern void trap_vector();
    __asm__ volatile("csrw mtvec, %0" : : "r"(trap_vector));

    // Initialize 3 tasks
    init_task(0, task1);
    init_task(1, task2);
    init_task(2, task3);

    // Initialize the timer interrupt
    init_timer();

    uart_puts("Tasks initialized. Enabling interrupts and starting Task 1...\n\n");

    // Enable Global Interrupts properly for mret
    // mret sets MIE to MPIE, and privilege mode to MPP.
    // We want to enter Machine mode (MPP = 3) with interrupts enabled (MPIE = 1)
    uint32_t mstatus;
    __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus));
    mstatus |= (1 << 7) | (3 << 11); // MPIE is bit 7, MPP is bits 11:12
    __asm__ volatile("csrw mstatus, %0" : : "r"(mstatus));

    // Manually jump to the first task
    __asm__ volatile(
        "mv sp, %0 \n"
        "lw t0, 124(sp) \n"
        "csrw mepc, t0 \n"
        "addi sp, sp, 128 \n"
        "mret \n"
        : : "r"(tasks[0].sp)
    );

    // Should never reach here
    while (1);
}
