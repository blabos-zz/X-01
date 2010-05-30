entry start
start:
    mov ax, #0xB800
    mov es, ax
    
    seg es
    mov [0], #0x41
    
    seg es
    mov [1], #0x1F
    
loop1: jmp loop1
