#include "os.h"

// Define task stacks (3 tasks, 1024 words each)
uint32_t task_stacks[MAX_TASKS][STACK_SIZE];

Task tasks[MAX_TASKS];
int current_task = 0;

// The timer interval
#define TIMER_INTERVAL 10000000

// We need to set mtvec to trap_vector
extern void trap_vector();

void init_task(int id, void (*task_func)()) {
    tasks[id].id = id;
    
    // Set the stack pointer to the top of the stack for this task
    // (Stacks grow downwards)
    uint32_t *sp = &task_stacks[id][STACK_SIZE];

    // Allocate space for the Context (32 registers, 128 bytes)
    sp -= 32;
    
    Context *ctx = (Context *)sp;
    
    // Initialize the context to 0
    for (int i = 0; i < 32; i++) {
        ((uint32_t *)ctx)[i] = 0;
    }
    
    // Set the correct stack pointer in the context (top of the stack)
    ctx->sp = (uint32_t)&task_stacks[id][STACK_SIZE];
    
    // Inherit the global pointer from the OS
    uint32_t gp;
    __asm__ volatile("mv %0, gp" : "=r"(gp));
    ctx->gp = gp;
    
    // Set MEPC to the task function so `mret` jumps there
    ctx->mepc = (uint32_t)task_func;
    
    // Save the SP in the task structure
    tasks[id].sp = sp;
}

void init_timer() {
    *CLINT_MTIMECMP = *CLINT_MTIME + TIMER_INTERVAL;
    
    // Enable timer interrupts in MIE (Machine Interrupt Enable) register
    // MIE bit 7 is MTIE (Machine Timer Interrupt Enable)
    uint32_t mie;
    __asm__ volatile("csrr %0, mie" : "=r"(mie));
    mie |= (1 << 7);
    __asm__ volatile("csrw mie, %0" : : "r"(mie));
}

uint32_t handle_trap(uint32_t sp) {
    // Read MCAUSE to determine the cause of the trap
    uint32_t mcause;
    __asm__ volatile("csrr %0, mcause" : "=r"(mcause));

    // Check if it's a Machine Timer Interrupt (mcause == 0x80000007)
    // The highest bit is set for interrupts.
    if (mcause == 0x80000007) {
        // Acknowledge the interrupt by setting the next timer event
        *CLINT_MTIMECMP = *CLINT_MTIME + TIMER_INTERVAL;

        // Save the stack pointer of the currently running task
        tasks[current_task].sp = (uint32_t *)sp;

        // Round-robin scheduling: pick the next task
        current_task = current_task + 1;
        if (current_task >= MAX_TASKS) {
            current_task = 0;
        }

        uart_puts("\n[Context Switch] -> Task ");
        uart_putc('1' + current_task);
        uart_puts("\n\n");

        // Return the stack pointer of the next task
        return (uint32_t)tasks[current_task].sp;
    }

    // If it's not a timer interrupt, just return the same stack pointer
    return sp;
}
