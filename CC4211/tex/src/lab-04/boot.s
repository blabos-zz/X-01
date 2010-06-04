##--------------------------------------------------------------------
## boot.s
.code16
.section .text
.globl _start
_start:
    mov $0xb800, %ax
    mov %ax, %ds
    movb $'X', 0
    movb $0x1e, 1
idle:
    jmp idle
##--------------------------------------------------------------------
