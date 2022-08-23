nasm -f win64 -Ox uebung2.asm
golink.exe /entry:Start kernel32.dll user32.dll uebung2.obj