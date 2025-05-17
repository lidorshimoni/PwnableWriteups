#!/usr/bin/python3
from pwn import *

elf = context.binary = ELF("fix")
# libc = ELF(elf.runpath + b"/libc.so.6") # elf.libc broke again

gs = ''
# continue
# '''
def start():
    if args.SSH:
        s=ssh(host='pwnable.kr',user='unlink',password='guest',port=2222)
        io=s.process('./unlink')
        # pass
    else:
        io = process(elf.path)
        if args.GDB:
            gdb.attach(io, gdbscript=gs)
    return io

# Select the "malloc" option, send size & data.
# def malloc(size, data):
#     io.send(b"1")
#     io.sendafter(b"size: ", f"{size}".encode())
#     io.sendafter(b"data: ", data)
#     io.recvuntil(b"> ")

# Calculate the "wraparound" distance between two addresses.
# def delta(x, y):
#     return (0xffffffffffffffff - x) + y

io = start()

# This binary leaks the address of puts(), use it to resolve the libc load address.
# io.recvuntil(b"puts() @ ")
# libc.address = int(io.recvline(), 16) - libc.sym.puts

# This binary leaks the heap start address.
# io.recvuntil(b"heap @ ")
# heap = int(io.recvline(), 16)
# io.recvuntil(b"fixed : ")
# io.timeout = 0.1

# io.send(b"1")
# io.send(b"1")

# =============================================================================

# =-=-=- EXAMPLE -=-=-=

# The "heap" variable holds the heap start address.
# info(f"heap: 0x{heap:02x}")

# Program symbols are available via "elf.sym.<symbol name>".
# info(f"target: 0x{elf.sym.target:02x}")

# The malloc() function chooses option 1 from the menu.
# Its arguments are "size" and "data".
# malloc(24, b"Y"*24+b"\xff"*8)

# The delta() function finds the "wraparound" distance between two addresses.
# info(f"delta between heap & main(): 0x{delta(heap, elf.sym.main):02x}")

# =============================================================================


io.interactive()
