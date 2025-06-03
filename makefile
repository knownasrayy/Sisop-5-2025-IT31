prepare:
	mkdir -p bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin

stdlib:
	gcc -m32 -ffreestanding -c src/std_lib.c -o bin/std_lib.o -Iinclude

shell:
	gcc -m32 -ffreestanding -c src/shell.c -o bin/shell.o -Iinclude

kernel:
	gcc -m32 -ffreestanding -c src/kernel.c -o bin/kernel.o -Iinclude
	nasm -f elf src/kernel.asm -o bin/kernel_asm.o

link:
	ld -m elf_i386 -Ttext 0x1000 bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o -o bin/kernel.bin
	cat bin/bootloader.bin bin/kernel.bin > bin/floppy.img

build: prepare bootloader stdlib shell kernel link
