section .text
global procesar_gini

; float en xmm0, devuelve int en eax
procesar_gini:
    push rbp
    mov rbp, rsp

    ; convertir float (xmm0) a int (redondeo)
    cvttss2si eax, xmm0
    add eax, 1

    pop rbp
    ret
