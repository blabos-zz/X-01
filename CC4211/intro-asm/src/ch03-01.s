.section .data
.section .text
.globl _start
_start:
movl $1, %eax   # Coloca o valor 1 no registrador eax
movl $0, %ebx   # Coloca o valor 2 no registrador ebx
int $0x80       # Chama a interrupcao 0x80
