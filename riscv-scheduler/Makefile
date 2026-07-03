CC = riscv64-unknown-elf-gcc
CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -march=rv32i_zicsr -mabi=ilp32 -g -Wall -T linker.ld
QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

OBJS = boot.o trap.o scheduler.o main.o

all: os.elf

os.elf: $(OBJS)
	$(CC) $(CFLAGS) -o os.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

run: os.elf
	$(QEMU) $(QFLAGS) -kernel os.elf

clean:
	rm -f *.o os.elf
