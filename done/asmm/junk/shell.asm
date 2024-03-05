section .data
    filename db 'flag', 0

section .bss
    fd resb 1
    buf resb 100

section .text
    global _start
_start:
    ; open the file
    mov eax, 5 ; syscall number for open
    mov ebx, filename ; pointer to the filename
    xor ecx, ecx ; flags
    xor edx, edx ; mode
    int 0x80 ; make the system call
    mov [fd], eax ; store the file descriptor

    ; read from the file
    mov eax, 3 ; syscall number for read
    mov ebx, [fd] ; file descriptor
    mov ecx, buf ; buffer
    mov edx, 100 ; number of bytes to read
    int 0x80 ; make the system call

    ; write to standard output
    mov eax, 4 ; syscall number for write
    mov ebx, 1 ; file descriptor for stdout
    mov ecx, buf ; buffer
    mov edx, 100 ; number of bytes to write
    int 0x80 ; make the system call

    ; exit
    mov eax, 1 ; syscall number for exit
    xor ebx, ebx ; exit code
    int 0x80 ; make the system call