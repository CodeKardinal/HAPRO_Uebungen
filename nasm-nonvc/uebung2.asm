; This line is a comment.

bits 64

%include "win32n.inc"

global Start

section .text
Start:
    ; 1. Bits 7…4 von EAX sollen in die Bits 3…0 übertragen und negiert werden
    xor rax, rax    ;rax=0
    mov al, 160     ;             al=10100000
    mov ah, al      ;             ah=10100000
    shr al, 4       ;rechts-shift al=00001010
    or al, 240      ;             al=11111010
    not al          ;negation     al=00000101
    xor al, ah      ;             al=10100101


    ; 2. …in umgekehrter Reihenfolge
    xor rax, rax    ;rax=0
    mov al, 10     ;            al=00001010 01010000
    
    mov rbx, 8

    jump:
    Dec rbx
    rcr al, 1
    rcl ah, 1
    jnz jump
 
    ; 3. Multiplikation von A123h mit BX=7 
    ;xor rax, rax



