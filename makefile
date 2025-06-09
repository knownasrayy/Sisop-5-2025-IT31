prepare:
	mkdir -p bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin

stdlib:
	bcc -ansi -c -o bin/std_lib.o src/std_lib.c -Iinclude

shell:
	bcc -ansi -c -o bin/shell.o src/shell.c -Iinclude

kernel:
	bcc -ansi -c -o bin/kernel.o src/kernel.c -Iinclude
	nasm -f as86 src/kernel.asm -o bin/kernel_asm.o

link:
	ld86 -o bin/kernel.sys -d bin/kernel.o bin/kernel_asm.o bin/shell.o bin/std_lib.o
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	dd if=bin/kernel.sys of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link
