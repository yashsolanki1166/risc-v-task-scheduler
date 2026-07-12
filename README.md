**RISC-V Task Scheduler Simulation**

A bare-metal RISC-V task scheduler simulation built as part of a literature survey on RISC-V based embedded systems at IIT Gandhinagar. The project demonstrates core embedded OS concepts — bare-metal startup, trap handling, and round-robin scheduling — without requiring physical hardware.

---

**Project Structure**

```
.
├── Makefile        # build system
├── boot.S          # startup assembly, stack init, jumps to main
├── trap.S          # trap handler, exception and interrupt entry point
├── main.c          # kernel entry point, initialization
├── scheduler.c     # round-robin scheduler and task definitions
├── os.h            # shared kernel headers and declarations
├── linker.ld       # custom linker script, memory layout
└── os.elf          # compiled output binary
```

---

**What It Does**

On execution the kernel boots, initializes the stack via `boot.S`, sets up the trap handler via `trap.S`, and cycles through three concurrent tasks in round-robin order via the scheduler:

- **Task 0** — count-up counter, increments on every tick
- **Task 1** — count-down counter, decrements from a starting value
- **Task 2** — GPIO toggle simulation, alternates between ON and OFF states

---

**Tools Required**

- WSL (Windows Subsystem for Linux)
- riscv64-unknown-elf-gcc
- riscv64-unknown-elf-ld
- riscv64-unknown-elf-objdump
- QEMU (for execution)

**Install toolchain in WSL:**
```bash
sudo apt update
sudo apt install gcc-riscv64-unknown-elf
```

---

**Build**

```bash
make
```

Or manually:
```bash
riscv64-unknown-elf-gcc -nostdlib -T linker.ld boot.S trap.S main.c scheduler.c -o os.elf
```

**Inspect disassembly:**
```bash
riscv64-unknown-elf-objdump -d os.elf
```

---

**Run on QEMU**

```bash
qemu-system-riscv32 -nographic -machine virt -kernel os.elf
```

---

**Concepts Demonstrated**

- Bare-metal startup sequence (stack initialization, entry point)
- Trap handling in assembly (exceptions and interrupts)
- Custom linker script and memory section layout (.text, .data, .bss)
- Round-robin task scheduling in C
- Cross-compilation workflow for RISC-V embedded targets
- GPIO peripheral simulation

---

**Context**

This project is the practical component of a literature survey on RISC-V based embedded systems, covering RISC-V architecture fundamentals, comparison with ARM, IoT and low-power applications, security mechanisms, and AI edge computing.

---

**References**

- RISC-V Unprivileged ISA Specification — riscv.org/technical/specifications
- RISC-V Privileged ISA Specification — riscv.org/technical/specifications
- Patterson & Hennessy, Computer Organization and Design: RISC-V Edition
- Patterson & Waterman, The RISC-V Reader
