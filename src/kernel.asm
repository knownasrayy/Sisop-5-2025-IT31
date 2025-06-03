bits 16         ; Tell NASM to generate 16-bit code

; kernel.asm

; Declare global symbols for linking with C
global _putInMemory
global _interrupt
global _getBiosTick

section .text   ; Define the code section, standard practice for ELF

; unsigned int getBiosTick()
; Returns the BIOS tick count (lower 16 bits) in AX.
_getBiosTick:
    mov ah, 0x00    ; BIOS function to get system time
    int 0x1A        ; Call BIOS video service
    mov ax, dx      ; Tick count (low word) is in DX
    ret

; void putInMemory(int segment, int address, char character)
; Puts a character into a specific memory location.
_putInMemory:
    push bp
    mov bp, sp
    push ds         ; Save original DS

    mov ax, [bp+4]  ; segment parameter from C
    mov si, [bp+6]  ; address parameter from C
    mov cl, [bp+8]  ; character parameter from C (char is 1 byte, so CL is fine)

    mov ds, ax      ; Set DS to the target segment
    mov [si], cl    ; Write the character to memory ES:[DI]

    pop ds          ; Restore original DS
    pop bp
    ret

; int interrupt(int number, int AX_c, int BX_c, int CX_c, int DX_c)
; Calls a software interrupt with specified register values.
; Returns the value of AX after the interrupt.
_interrupt:
    push bp
    mov bp, sp
    push ds         ; Save original DS

    mov ax, [bp+6]  ; Load AX_c into AX
    mov bx, [bp+8]  ; Load BX_c into BX
    mov cx, [bp+10] ; Load CX_c into CX
    mov dx, [bp+12] ; Load DX_c into DX

    push cs
    pop ds          ; DS now points to the Code Segment (CS)

    mov al, byte [bp+4] ; Load 'number' (interrupt vector byte) into AL
    mov byte [intr_instruction_byte], al ; Modify the 0x00 in 'int 0x00' with AL

    pop ds          ; Restore original DS

intr_instruction_byte:
    int 0x00        ; This 0x00 will be replaced by the actual interrupt number.
                    ; AX will hold the return value from the interrupt.
    pop bp
    ret
