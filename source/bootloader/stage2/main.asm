org 0x0
bits 16

start:

    lea si, msg
    call puts

.halt:
    cli
    hlt 

   
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


msg: db "Hello World FROM KERNEL!!",0x0D, 0x0A, 0
