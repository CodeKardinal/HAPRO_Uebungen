; This line is a comment.

bits 64

%include "win32n.inc"

global Start
;test
section .text
Start:
    ; 1. Bits 7…4 von EAX sollen in die Bits 3…0 übertragen und negiert werden
    xor rax, rax    ;rax=0
    mov al, 160     ;             al=10100000
    shr al, 4       ;rechts-shift al=00001010
    xor al, 255     ;negation     al=11110101

    ; 2. …in umgekehrter Reihenfolge
    xor rax, rax    ;rax=0
    mov al, 160     ;            al=10100000
    shl al, 4       ;links-shift al=00000000
    xor al, 255     ;negation    al=11111111

    ; 3. Multiplikation von A123h mit BX=7 
    xor rax, rax



