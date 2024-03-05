#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i =32;
void func(int key){
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!
    for(; i < 52; i++)
    {
        // printf("%c", (unsigned)(unsigned char)overflowme[i]);
        printf("\\x%1x", (unsigned)(unsigned char)overflowme[i]);
    }
    printf("\nkey=%x\n", key);
	if(key == 0xcafebabe){
        // printf("SUCCESS!");
		// printf("/bin/sh");
		system("/bin/sh");
	}
	else{
		printf("Nah..\n");
	}
}
int main(int argc, char* argv[]){
	func(0xdeadbeef);
	return 0;
}
