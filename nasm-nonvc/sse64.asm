; This line is a comment.

bits 64

%include "win32n.inc"

extern sprintf
extern MessageBoxA
extern ExitProcess

global Start					; make our main label visible to the linker


section .data 

	title db "Hello",0
	format_str db "Ergebnis: %f",0
	sprintf_result resb 128

	a dq 3.14159027				; reserve quad-word (64-bit), double precision float
	b dq 2.0
	c dq 0.0
	
section .text
Start:
	
	; berechnet 2*pi
	movsd xmm0, [a]
	movsd xmm1, [b]
	mulsd xmm0, xmm1
	

	; sprintf(sprintf_result, "Ergebnis: %f", xmm0)
	sub rsp, 40
	lea rcx, [sprintf_result]	; auch: mov rcx, sprintf_result
	lea rdx, [format_str]
	
	; sprintf erwartet den wert für %f in r8 UND xmm2!
	movupd xmm2, xmm0
	movupd [c], xmm0
	mov r8, [c]
	
	call sprintf
	add rsp, 40
	
	; MessageBoxA(0, "Hello", sprintf_result, 0)
	sub rsp, 40					; allocate stack space for 4x8Byte parameters and 1x8Byte return address
	mov rcx, 0            		; Parameter 1: hWnd = HWND_DESKTOP
	mov rdx, qword sprintf_result
	mov r8, qword title         ; Parameter 3: LPCSTR lpCaption
	mov r9, 0            		; Parameter 4: uType = MP_OK
	call MessageBoxA			; https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxa
	add rsp, 40					; clean stack space
	  
	; ExitProcess(0)
	sub rsp, 40
	mov rcx, 0          		; Parameter 1: uExitCode
	call ExitProcess
	add rsp, 40

	ret							; can be ommitted
