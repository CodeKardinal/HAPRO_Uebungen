nasm -f win64 -Ox sse64.asm
golink.exe /entry:Start kernel32.dll user32.dll msvcrt.dll sse64.obj