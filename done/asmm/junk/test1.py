filename = "this_is_pwnable.kr_flag_file_please_read_this_file.sorry_the_file_name_is_very_loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0000000000000000000000000ooooooooooooooooooooooo000000000000o0o0o0o0o0o0ong\x00"[::-1]
chunks = [filename[i:i+8] for i in range(0, len(filename), 8)]

# print("section .text")
# print("    global _start")
# print("_start:")
# print("    ; open the file")
# print("    xor eax, eax")
# print("    mov al, 5 ; syscall number for open")

for chunk in chunks:
    print(f"    push 0x{''.join([hex(ord(c))[2:] for c in chunk])} ; \"{chunk[::-1]}\"")
# for chunk in reversed(chunks):
#     chunk += b'\x00' * (4 - len(chunk))  # pad chunk to 4 bytes
#     print(f"    push 0x{chunk.hex()} ; \"{chunk.decode('utf-8', 'ignore')}\"")

# print("    mov ebx, esp ; pointer to the filename")
# print("    xor ecx, ecx ; flags")
# print("    xor edx, edx ; mode")
# print("    int 0x80 ; make the system call")
# print("    ; rest of the code...")