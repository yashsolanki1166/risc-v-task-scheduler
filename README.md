**RISC-V Task Scheduler Simulation**

A bare-metal RISC-V task scheduler simulation built as part of a literature survey on RISC-V based embedded systems at IIT Gandhinagar. The project demonstrates core embedded OS concepts — bare-metal startup, round-robin scheduling, and task management — without requiring physical hardware.

---

**Project Structure**

```
riscv-kernel/
├── boot.S         # startup assembly, stack init, jumps to main
├── start.S        # low-level entry point setup
├── kernel.c       # round-robin scheduler and task definitions
├── linker.ld      # custom linker script, memory layout
└── README.md
```

---

**What It Does**

On execution, the scheduler boots, initializes the stack, and cycles through three concurrent tasks in round-robin order:

- **Task 0** — count-up counter, increments on every tick
- **Task 1** — count-down counter, decrements from a starting value
- **Task 2** — GPIO toggle simulation, alternates between ON and OFF states

Each tick prints the current task and its state to the console, demonstrating live context switching.

---

**Tools Required**

- WSL (Windows Subsystem for Linux)
- riscv64-unknown-elf-gcc
- riscv64-unknown-elf-ld
- riscv64-unknown-elf-objdump
- QEMU (for execution — planned)

**Install toolchain in WSL:**
```bash
sudo apt update
sudo apt install gcc-riscv64-unknown-elf
```

---

**Build**

```bash
riscv64-unknown-elf-gcc -nostdlib -T linker.ld boot.S start.S kernel.c -o kernel.elf
```

**Inspect disassembly:**
```bash
riscv64-unknown-elf-objdump -d kernel.elf
```

---

**Run on QEMU**

```bash
qemu-system-riscv32 -nographic -machine virt -kernel kernel.elf
```

---

**Concepts Demonstrated**

- Bare-metal startup sequence (stack initialization, entry point)
- Custom linker script and memory section layout (.text, .data, .bss)
- Round-robin task scheduling
- Cross-compilation workflow for RISC-V embedded targets
- GPIO peripheral simulation

---

**Context**

This project is the practical component of a literature survey on RISC-V based embedded systems, covering RISC-V architecture fundamentals, comparison with ARM, IoT and low-power applications, security mechanisms, and AI edge computing. The implementation grounds the survey findings in hands-on bare-metal RISC-V development.

---

**References**

- RISC-V Unprivileged ISA Specification — riscv.org/technical/specifications
- RISC-V Privileged ISA Specification — riscv.org/technical/specifications
- Patterson & Hennessy, Computer Organization and Design: RISC-V Edition
- Patterson & Waterman, The RISC-V Reader
