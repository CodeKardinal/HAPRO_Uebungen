; This line is a comment.

bits 64

%include "win32n.inc"

extern MessageBoxA
extern ExitProcess

	;extern sprintf 

global Start					; make our main label visible to the linker


section .data 

	title db "hello",0
	message db "hello world",0
	stra db "Number is %d", 10, 0   ; endline, null terminator
	strb db "Hello World! Number=%d", 10, 0   ; endline, null terminator
	
	
section .text
Start:
	; Uebung
	mov rax, 1
	mov rbx, 2
	add rax, rbx

	xor rax, rax
	xor rbx, rbx

	mov rax, 10
	mov rbx, 15
	mul rbx

	sub rsp, 40					; allocate stack space for 4x8Byte parameters and 1x8Byte return address
	mov rcx, 0            		; Parameter 1: hWnd = HWND_DESKTOP
	mov rdx, qword message      ; Parameter 2: LPCSTR lpText
	mov r8, qword title         ; Parameter 3: LPCSTR lpCaption
	mov r9d, 0            		; Parameter 4: uType = MP_OK
	call MessageBoxA			; https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxa
	add rsp, 40					; clean stack space
	  
	
	; playing with the stack
	mov ax, 0xDEAD
	push ax
	push ax
	push ax
	push ax
	pop rax
	
	
	sub rsp, 40
	mov ecx, eax          		; Parameter 1: uExitCode
	call ExitProcess
	add rsp, 40

	ret							; can be ommitted
