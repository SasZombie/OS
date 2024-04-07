org 0x7C00
bits 16

start:
    jmp main
;Function to easally print stuff on the screen
puts:
    push si
    push ax 

.loop:
    lodsb
    or al, al 
    jz .done 
    
    mov ah, 0x0e
    int 0x10
    jmp .loop

.done:
    pop si 
    pop ax
    ret 

main:

    mov ax, 0
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7C00

    lea si, msg
    call puts

    hlt 

.halt:
    jmp .halt


msg: db "Hello World",0x0D, 0x0A, 0
times 510-($-$$) db 0

dw 0AA55h