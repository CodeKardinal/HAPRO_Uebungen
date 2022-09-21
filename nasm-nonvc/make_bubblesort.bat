nasm -f win64 -Ox bubblesort.asm
golink.exe /entry:Start kernel32.dll user32.dll bubblesort.obj