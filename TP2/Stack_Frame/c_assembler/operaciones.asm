global suma, resta, mul, division

section .text

suma:               ; int suma(int a, int b)
    mov rax, rdi    ; rax = a
    add rax, rsi    ; rax += b
    ret

resta:              ; int resta(int a, int b)
    mov rax, rdi    ; rax = a
    sub rax, rsi    ; rax -= b
    ret

mul:                ; int mul(int a, int b)
    mov rax, rdi    ; rax = a
    imul rsi        ; rax *= b (multiplicación con signo)
    ret

division:           ; int division(int a, int b)
    mov rax, rdi    ; rax = a (dividendo)
    cqo             ; extiende el signo de rax a rdx para dividir
    idiv rsi        ; rax = a / b (división con signo)
    ret
