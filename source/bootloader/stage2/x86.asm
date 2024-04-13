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

    ;[bp + 0] => old call frame
    ;[bp + 2] => return address. We use small memorry model so 2 bytes per char
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

global _x86_div64_32
_x86_div64_32:

    ; make new call frame
    push bp             ; save old call frame
    mov bp, sp          ; initialize new call frame

    push bx

    ; divide upper 32 bits
    mov eax, [bp + 8]   ; eax <- upper 32 bits of dividend
    mov ecx, [bp + 12]  ; ecx <- divisor
    xor edx, edx
    div ecx             ; eax - quot, edx - remainder

    ; store upper 32 bits of quotient
    mov bx, [bp + 16]
    mov [bx + 4], eax

    ; divide lower 32 bits
    mov eax, [bp + 4]   ; eax <- lower 32 bits of dividend
                        ; edx <- old remainder
    div ecx

    ; store results
    mov [bx], eax
    mov bx, [bp + 18]
    mov [bx], edx

    pop bx

    ; restore old call frame
    mov sp, bp
    pop bp
    ret


global _x86_Video_WriteNumber

x86_Video_WriteNumber:

print_number:            ; Function entry point
    push bp              ; Save base pointer
    mov bp, sp           ; Set up base pointer
; 
    mov bx, 10           ; Divisor for division by 10
; 
next_digit:
    xor dx, dx           ; Clear DX register
    div bx               ; Divide AX by 10
    add dl, '0'          ; Convert remainder to ASCII
    push dx              ; Save ASCII digit on stack
    test ax, ax          ; Check if quotient is zero
    jnz next_digit       ; If not zero, repeat the process

print_digit:
    pop dx               ; Get ASCII digit from stack
    mov ah, 0x0E         ; BIOS teletype output function
    int 0x10             ; Call BIOS interrupt
    test dx, dx          ; Check if all digits printed
    jnz print_digit      ; If not, print next digit

    pop bp               ; Restore base pointer
    ret                   ; Return to caller
