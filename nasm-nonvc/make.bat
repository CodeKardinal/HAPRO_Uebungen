nasm -f win64 -Ox hello64.asm
golink.exe /entry:Start kernel32.dll user32.dll hello64.obj