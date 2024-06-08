bits 16

section .data
    dirname db "NEWDIR", 0 
section _TEXT class=CODE

global __wcpp_4_undefed_cdtor__


__wcpp_4_undefed_cdtor__:
ret

global __U4M
__U4M:
    shl edx, 16         ; dx to upper half of edx
    mov dx, ax          ; m1 in edx
    mov eax, edx        ; m1 in eax

    shl ecx, 16         ; cx to upper half of ecx
    mov cx, bx          ; m2 in ecx

    mul ecx             ; result in edx:eax (we only need eax)
    mov edx, eax        ; move upper half to dx
    shr edx, 16

    ret

global __U4D

__U4D:
    shl edx, 16
    mov dx, ax
    mov eax, edx
    xor edx, edx

    shl ecx, 16
    mov cx, bx

    div ecx

    mov ebx, edx
    mov ecx, edx
    shr ecx, 16

    mov edx, eax
    shr edx, 16

    ret

;MARK: CONVENTION
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

global _x86_Video_WriteCharTeletype
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

_x86_Video_WriteNumber:

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


; void _cdecl x86_Disk_Reset(uint8_t drive);
global _x86_Disk_Reset

_x86_Disk_Reset:
    push bp
    mov bp, sp 

    mov ah, 0
    mov dl, [bp + 4] ;dl drive
    stc 
    int 13h

    mov ax, 1
    sbb ax, 0

    mov sp, bp
    pop bp 
    ret

; void _cdecl x86_Disk_Read(uint8_t drive, uint8_t cylinder, uint8_t head, uint8_t sector, uint8_t count, uint8_t __far *dataOut);

global _x86_Disk_Read

_x86_Disk_Read:
 ; make new call frame
    push bp             ; save old call frame
    mov bp, sp          ; initialize new call frame

    ; save modified regs
    push bx
    push es

    ; setup args
    mov dl, [bp + 4]    ; dl - drive

    mov ch, [bp + 6]    ; ch - cylinder (lower 8 bits)
    mov cl, [bp + 7]    ; cl - cylinder to bits 6-7
    shl cl, 6
    
    mov al, [bp + 8]    ; cl - sector to bits 0-5
    and al, 3Fh
    or cl, al

    mov dh, [bp + 10]   ; dh - head

    mov al, [bp + 12]   ; al - count

    mov bx, [bp + 16]   ; es:bx - far pointer to data out
    mov es, bx
    mov bx, [bp + 14]

    ; call int13h
    mov ah, 02h
    stc
    int 13h

    ; set return value
    mov ax, 1
    sbb ax, 0           ; 1 on success, 0 on fail   

    ; restore regs
    pop es
    pop bx

    ; restore old call frame
    mov sp, bp
    pop bp
    ret
; void _cdecl x86_Disk_GetDriveParams(uint8_t drive, uint8_t *driveTypeOut, uint16_t* cylinderOut, uint16_t *sectorsOut, uint16_t *headsOut);

global _x86_Disk_GetDriveParams

_x86_Disk_GetDriveParams:
    push bp
    mov bp, sp 

    push es 
    push bx
    push si
    push di

    mov dl, [bp + 4]
    mov ah, 08h
    mov di, 0   ;es:di -> 0000:0000
    mov es, di 

    stc
    int 13h

    mov ax, 1
    sbb ax, 0


    ;mov [bp + 6], bl ;To check if this can be done like this as well

    mov si, [bp + 6]
    mov [si], bl 

    mov bl, ch 
    mov bh, cl 
    shr bh, 6

    mov si, [bp + 8]
    mov [si], bx


    xor ch, ch 
    and cl, 3Fh     
    mov si, [bp + 10]
    mov [si], cx    

    mov cl, dh
    mov si, [bp + 12]
    mov [si], dh



    pop es 
    pop di
    pop bx
    pop si 

    mov sp, bp 
    pop bp 
    ret

; char _cdecl x86_Read_Character();

global _x86_Read_Character

_x86_Read_Character:
    push bp
    mov bp, sp 

    mov ah, 0
    int 16h

    mov si, [bp + 4]
    mov [si], al

    mov sp, bp
    pop bp

    ret

;void _cdecl x86_Create_File(char *fileName)
global _x86_Create_File

_x86_Create_File:
    push bp
    mov bp, sp 
    
    mov ah, 3Ch
    mov cx, 0
    mov si, [bp + 4]
    mov dx, [si]

    int 21h
    
    mov ax, 1
    sbb ax, 0

    mov sp, bp
    pop bp
    ret




global _x86_Create_Dir

_x86_Create_Dir:
    push bp
    mov bp, sp 
    
    mov ah, 39h
    ; mov si, [bp + 4]
    mov dx, dirname

    int 21h
    
    mov ax, 1
    sbb ax, 0

    mov sp, bp
    pop bp
    ret

global _x86_Clear_Line

_x86_Clear_Line:

    push bx

    mov ah, 0x02
    xor bh, bh    ; Page number 
    xor dh, dh    ; Row number 
    mov dl, 0     ; Column number
    int 0x10

    mov ah, 0x06  ; Scroll window up
    mov al, 0     ; Number of lines to scroll
    mov cx, 0     ; Set to 0
    mov dh, 50     ; Top row
    mov dl, 79    ; Rightmost column
    mov bh, 7     ; Set to 7
    int 0x10

    pop bx 
    ret


global _x86_Clear_Screen


_x86_Clear_Screen:
    
    push bx

    mov ah, 0x02
    xor bh, bh    ; Page number
    xor dh, dh    ; Row number 
    mov dl, 0     ; Column number
    int 0x10

    mov ah, 0x06  ; Scroll up
    mov al, 0     ; Number of lines to scroll
    mov cx, 0     ; Set to 0
    mov dh, 50    ; Top row
    mov dl, 79    ; Rightmost column
    mov bh, 7     ; Set to 7
    int 0x10

    pop bx 
    ret


global _x86_Draw_Pixel

_x86_Draw_Pixel:
    
    push bp
    mov bp, sp 

    mov cx, [bp + 4]
    mov dx, [bp + 6]

    mov ah, 0x0C
    mov al, [bp + 8]

    int 0x10
  
    mov sp, bp
    pop bp

    ret


global _x86_Initiate_Video_Mode

_x86_Initiate_Video_Mode:

    mov ah, 0x00
    mov al, 0x13

    int 0x10

    ret

global _x86_Exit_Video_Mode

_x86_Exit_Video_Mode:
    mov ah, 0x00
    mov al, 0x03

    int 0x10
    ret

global _x86_Wait_Keyboard_Input

_x86_Wait_Keyboard_Input:

    mov ah, 0x00
    int 0x16

    ret
