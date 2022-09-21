nasm -f win64 -Ox fibonacci.asm
golink.exe /entry:Start kernel32.dll user32.dll fibonacci.obj