AS = nasm
CC = gcc
LD = ld

AS_FLAGS = -f elf32
CC_FLAGS = -I./ -c -m32 -fno-pie -fno-pic -ffreestanding -nostdlib

TARGET = Sph55.iso

OBJECT_FILES = build/console.o build/main.o build/entry.asm.o build/string.o build/gdt.o build/traps.o build/io.asm.o build/keyboard.o build/unistd.o build/sched.o build/mm.o build/mm.asm.o

QEMU = qemu-system-x86_64

all:
	clear
	$(AS) $(AS_FLAGS) kernel/entry.asm -o build/entry.asm.o
	$(AS) $(AS_FLAGS) kernel/io.asm -o build/io.asm.o
	$(AS) $(AS_FLAGS) mm/mm.asm -o build/mm.asm.o

	$(CC) $(CC_FLAGS) kernel/console.c -o build/console.o
	$(CC) $(CC_FLAGS) kernel/keyboard.c -o build/keyboard.o
	$(CC) $(CC_FLAGS) kernel/main.c -o build/main.o
	$(CC) $(CC_FLAGS) kernel/gdt.c -o build/gdt.o
	$(CC) $(CC_FLAGS) kernel/traps.c -o build/traps.o
	$(CC) $(CC_FLAGS) libc/string.c -o build/string.o
	$(CC) $(CC_FLAGS) libc/unistd.c -o build/unistd.o
	$(CC) $(CC_FLAGS) kernel/sched.c -o build/sched.o
	$(CC) $(CC_FLAGS) mm/mm.c -o build/mm.o

	$(LD) -m elf_i386 -T linker.ld -o iso/boot/kernel $(OBJECT_FILES)
	grub-mkrescue -o $(TARGET) iso/

	$(QEMU) -d cpu_reset -D qemu.log $(TARGET)

clean:
	clear
	rm -rf build/*.o build/*.asm.o
	rm -rf $(TARGET)