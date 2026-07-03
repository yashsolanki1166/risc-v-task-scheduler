#ifndef OS_H
#define OS_H

#include <stdint.h>

#define MAX_TASKS 3
#define STACK_SIZE 1024

// QEMU virt UART address for basic printing
#define UART0_BASE 0x10000000
// QEMU virt CLINT (Core Local Interruptor) for timer
#define CLINT_BASE 0x02000000
#define CLINT_MTIMECMP ((volatile uint64_t *)(CLINT_BASE + 0x4000))
#define CLINT_MTIME    ((volatile uint64_t *)(CLINT_BASE + 0xBFF8))

// Context saved by trap_vector (128 bytes)
typedef struct {
    uint32_t ra;
    uint32_t sp;
    uint32_t gp;
    uint32_t tp;
    uint32_t t0, t1, t2;
    uint32_t s0, s1;
    uint32_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint32_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    uint32_t t3, t4, t5, t6;
    uint32_t mepc;
} Context;

typedef struct {
    uint32_t *sp; // Stack pointer
    int id;
} Task;

extern Task tasks[MAX_TASKS];

// Function prototypes
void uart_putc(char c);
void uart_puts(char *s);
void os_main();
void task1();
void task2();
void task3();

uint32_t handle_trap(uint32_t sp);
void init_timer();

#endif
