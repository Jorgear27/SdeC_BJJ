[BITS 16]
[ORG 0x7C00]

start:
    cli                     ; desactiva interrupciones
    lgdt [gdt_descriptor]   ; carga la GDT
    mov eax, cr0
    or eax, 1
    mov cr0, eax            ; activa el modo protegido
    jmp 0x08:protected_mode ; salto lejano al selector de código

; -------------------------
; GDT (Global Descriptor Table)
; -------------------------

gdt_start:
    dq 0x0000000000000000       ; descriptor nulo
    dq 0x00CF9A000000FFFF       ; código: base=0, límite=FFFFF, rx
    dq 0x00CF92000000FFFF       ; datos: base=0, límite=FFFFF, rw

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

; -------------------------
; Modo protegido
; -------------------------
[BITS 32]
protected_mode:
    mov ax, 0x10        ; selector de datos
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Provocar excepción de protección general 
    ; mov dword [0x00100000], 0x12345678

    mov esi, mensaje
    call print_string
    hlt

print_string:
.loop:
    lodsb
    or al, al
    jz .end
    mov ah, 0x0E
    int 0x10
    jmp .loop
.end:
    ret

mensaje db "Hola desde modo protegido", 0

times 510-($-$$) db 0
dw 0xAA55
