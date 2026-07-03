.section .text
.global _start
_start:
    # Setup stack pointer to the end of RAM
    la sp, _memory_end

    # Setup the global pointer
.option push
.option norelax
    la gp, __global_pointer$
.option pop

    # Clear the .bss section
    la a0, _bss_start
    la a1, _bss_end
    bge a0, a1, end_clear_bss
clear_bss:
    sw zero, 0(a0)
    addi a0, a0, 4
    blt a0, a1, clear_bss
end_clear_bss:

    # Jump to main C function
    call os_main

loop:
    j loop
