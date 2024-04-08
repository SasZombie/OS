org 0x7C00
bits 16


jmp short start
nop

bdb_oem: db 'MSWIN4.1'  ;8 bytes
bdb_bytes_per_sector: dw 512 ;Little endian
bdb_sectors_per_clusters:   db 1
bdb_reserved_sectors:   dw 1
bdb_fat_count: db 2
bdb_dir_entries_count: dw 0E0h
bdb_total_sectors: dw 2880
bdb_media_descriptor_type: db 0F0h
bdb_sectors_per_fat: dw 9
bdb_sectors_per_track: dw 18
bdb_heads: dw 2
bdb_hidden_sectors: dd 0
bdb_larger_sector_count: dd 0

; Boot record
ebr_driver_number:   db 0
                     db 0

ebr_signature:  db 29h
ebr_volume_id: db 12h, 11h, 34h, 69h ;Serial Number
ebr_volume_label: db 'SAS OS V123'; Volume label. Doesnt matter what is here just to be 11 bytes
ebr_system_id:  db 'FAT12   '; 8 bythes padded with space


start:

    mov ax, 0
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7C00          ;Stack decreses from where we are. This is where we start



    push es                ;Some bioses start at 07C0:0000 instead of 0000:7C00. We need to make sure we are in the right place

    push word .after
    retf

.after:
 
    ;Read from floppy disk
    mov [ebr_driver_number], dl ;dl is the drive number

    lea si, loading
    call puts

    ;Read some parameters

    push es 
    mov ah, 08h
    int 13h
    jc floppy_error
    pop es                  ;Disk could be coruppted so bios telling us is safer

    and cl, 0x3F            ;Remove the first 2 bits
    xor ch, ch              ;Reset ch

    mov [bdb_sectors_per_track], cx ;Sector count

    inc dh
    mov [bdb_heads], dh


    ;Reading FAT root directory
    ;LBA of root is: reserved + nrOfFats * sectorsPerFat

    mov ax, [bdb_sectors_per_fat]
    mov bl, [bdb_fat_count]
    xor bh, bh
    mul bx                          ;dx:ax = nrOfFats * sectorsPerFat
    add ax, [bdb_reserved_sectors]

    ;We need the size of root directory: 32 * nr_of_entries / bytes_per_sector
    push ax

    mov ax, [bdb_sectors_per_fat]
    shl ax, 5                               ;Multiply by 2 ^ 5 = 32
    xor dx, dx
    div word [bdb_bytes_per_sector]         ;bdb_bytes_per_sector is a word. We need to specify that. This is the nr of sectors we need to read

    test dx, dx                             ;if dx != 0, we need to add 1
    jz root_dir_after
    inc ax                                  ;This happens when we have a sector that is only partially filled with entries


root_dir_after:
    mov cl, al                              ;size of root directory == numbers of sectors to read
    pop ax                                  ;LBA of root directory
    mov dl, [ebr_driver_number]
    mov bx, buffer
    call disk_read

    ;search for kerner

    xor bx, bx

    mov di, buffer

.search_stage2:
    lea si, file_stage2_bin
    mov cx, 11              ;Length of stage2 file name
    push di
    repe cmpsb              ;Compare 2 strings from si and di. Repe = repeat while equal
    pop di
    je .found_stage2

    add di, 32
    inc bx

    cmp bx, [bdb_dir_entries_count]
    jl .search_stage2

    jmp stage2_not_found


.found_stage2:
    
    ;di should have the same address

    mov ax, [di + 26]
    mov [stage2_cluster], ax    ;First cluster has offset 26

    ;Load FAT from disk

    mov ax, [bdb_reserved_sectors]
    mov bx, buffer
    mov cl, [bdb_sectors_per_fat]
    mov dl, [ebr_driver_number]
    call disk_read    

    ;read stage2 and process FAT chain -> ->
    mov bx, stage2_LOAD_SEGMENT
    mov es, bx
    mov bx, stage2_LOAD_OFFSET

.load_stage2_loop:
    ;We need to read all the clusters
    mov ax, [stage2_cluster]
    add ax, 31                          ;Hard Coded value. This will only work for 1.44 megabyter floppy disk

    mov cl, 1
    mov dl, [ebr_driver_number]
    call disk_read

    add bx, [bdb_bytes_per_sector]      
    ;We need to compute the location of the next cluster

    mov ax, [stage2_cluster]
    mov cx, 3
    mul cx
    mov cx, 2
    div cx                  ;ax = index of entry in FAT, dx = cluster % 2

    lea si, buffer
    add si, ax
    mov ax, [ds:si]     

    or dx, dx
    jz .even

.add:
    shr ax, 4
    jmp .next_cluster_after

.even:
    add ax, 0x0FFF

.next_cluster_after:
    cmp ax, 0x0FF8
    jae .read_finish

    mov [stage2_cluster], ax
    jmp .load_stage2_loop

.read_finish:
    ;Boot device in dl
    mov dl, [ebr_driver_number]
    mov ax, stage2_LOAD_SEGMENT

    mov ds, ax
    mov es, ax 

    jmp stage2_LOAD_SEGMENT:stage2_LOAD_OFFSET

    ;Should never happen :c
    jmp wait_and_reboot


    cli
    hlt 

stage2_not_found:
    lea si, file_stage2_error
    call puts
    jmp wait_and_reboot



floppy_error:

    lea si, msg_read_fail
    call puts
    jmp wait_and_reboot


wait_and_reboot:
    mov ah, 0
    int 16h
    jmp 0FFFFh:0        ;reset

.halt:
    cli
    hlt


;Function to display msg on screen 
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


;Disk Routines
;From LBA address to a CHS
;Bootloader expects:
; cx[bits 0-5] sector number
; cx[bits 6-15] cylinder
; dh head

lba_to_chs:

    push ax
    push dx

    xor dx, dx                          ; clear dx
    div word [bdb_sectors_per_track]    ; ax = LBA % sectorsPertrack

    inc dx                              ; sector = lba % sectorsPertrack + 1
    mov cx, dx                          ; save sector

    xor dx, dx                          ;dx = 0
    div word [bdb_heads]                ;ax = lba/sectorsPerTrack / heads = cylinder
                                        ;dx = lba/sectorsPerTrack % heads = head

    mov dh, dl                          ; dh = head
    mov ch, al                          ; ch = cylinder

    shl ah, 6                           ;put upper 2 bits in CL
    or cl, ah

    pop ax                              ;restore DL
    mov dl, al

    pop ax

    ret


disk_read:

    push ax
    push bx
    push cx
    push dx
    push di

    push cx              ;Save how many to read

    call lba_to_chs
    pop ax              ;Number of sectors to read

    mov ah, 02h
    int 13h

    mov di, 3

.retry:                 ;Documentation states to retry this at least 3 times
    pusha               ;We need to save all the reg
    stc                 ;Set carry flag
    int 13h
    jnc .done

    popa
    call disk_reset

    dec di
    cmp di, 0
    jne .retry

.fail:
    jmp floppy_error


.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax

disk_reset:
    pusha

    mov ah, 0
    int 13h
    jc floppy_error
    popa
    ret

loading: db "Working on it", 0x0D, 0x0A, 0
msg_read_fail: db "Faild to read disck", 0x0D, 0x0A, 0
file_stage2_bin: db 'STAGE2  BIN'      ;This is how fat expects the stage2
file_stage2_error: db "Cannot find stage2", 0x0D, 0x0A, 0
stage2_cluster: db 0
stage2_LOAD_SEGMENT equ 0x2000      ;Constant value
stage2_LOAD_OFFSET  equ 0
times 510-($-$$) db 0

dw 0AA55h

buffer: