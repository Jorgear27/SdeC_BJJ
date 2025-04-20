global suma, resta, mul, division

section .text

; int suma(int a, int b)
suma:
    mov rax, rdi
    add rax, rsi
    ret

resta:
    mov rax, rdi
    sub rax, rsi
    ret

mul:
    mov rax, rdi
    imul rsi
    ret

division:
    mov rax, rdi
    cqo
    idiv rsi
    ret
