; This line is a comment.

%include "win32n.inc"

	extern MessageBoxA
	import MessageBoxA user32.dll
	extern ExitProcess
	import ExitProcess kernel32.dll

	extern printf 
	import printf msvcrt.dll
	
	extern sprintf 
	import sprintf msvcrt.dll

	segment .data USE32

	title db "hello",0
	message db "hello world",0
	stra db "Number is %d", 10, 0   ; endline, null terminator
	strb db "Hello World! Number=%d", 10, 0   ; endline, null terminator
	
	
segment .bss USE32

	buffer resb 1024

segment .code USE32

..start:

	push 0xDEADBEEF
	push dword strb
	call [printf]
	add esp, 8
	
	
	; use sprintf to fill messagebox
	push 0x00000001
	push dword stra
	push dword buffer
	call [sprintf]
	add esp, 12 ; clean stack -- cdecl thing

	; use messagebox
	push dword MB_OK
	push dword title
	push dword buffer
	push dword 0
	call [MessageBoxA]


	push dword 0
	call [ExitProcess]