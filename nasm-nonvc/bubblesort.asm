; This line is a comment.

bits 64

%include "win32n.inc"

global Start

segment .data
array   dd  14, 10, 23, 45, 17, 9, 54, 22, 1, 76
size    dd  10

segment .text

Start:
xor ebx, ebx
xor eax, eax
xor ecx, ecx
mov ebx, 0  ;counter

compare:
mov eax, dword[ebx + array]
cmp eax, dword[ebx + array + 4]
jg swap
jl notswap

swap:
mov ecx, dword[ebx + array + 4]
mov dword[ebx + array + 4], eax
mov [ebx + array], ecx

notswap:
add ebx, 4  
jmp compare  

end: 
    ret