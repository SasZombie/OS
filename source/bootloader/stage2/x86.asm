bits 16

section _TEXT class=CODE

global _x86_Video_WriteCharTeletype
;CALL CONVENTION CDECL:
;ARGS: 
;       -PASSED THROUGH STACK
;       -PUSSHED FROM RIGHT TO LEFT
;       -CALLER REMOVES PARAMETERS FROM STACK
;RETURN:
;       -INTEGERS, POINTERS: EAX
;       -FLOATING POINTS: ST0
;REGISTERS:
;       -EAX, ECX, EDX SAVED BY CALLER
;       -ALL OTHERS BY THE CALLEE; THAT IS ALL THE REGISTERS SHOULD BE RESTORED TO THE ORIGINAL VALUES BEFORE RETURINING!!
;NAME: PREPEND FUNCTIONS WITH _
_x86_Video_WriteCharTeletype:

    push bp
    mov bp, sp      ;Intel supports 'enter' function
    ;Using bx. Need to save it
    push bx

    ;[bp + 0] =? old call frame
    ;[bp + 2] => return address. We use small memorry model so 2 bytes per number
    ;[bp + 4] => first argv; Bytes need to be converted to words; Cant push bytes on stack
    ;[bp + 6] => seccond argv(page)
    
    mov ah, 0Eh
    mov al, [bp + 4]
    mov bh, [bp + 6]
    int 10h

    pop bx

    mov sp, bp
    pop bp        ;Intel supports 'leave' function

    ret