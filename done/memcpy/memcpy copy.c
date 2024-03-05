// compiled with : gcc -o memcpy memcpy.c -m32 -lm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>

unsigned long long rdtsc(){
        asm("rdtsc");
}

char* slow_memcpy(char* dest, const char* src, size_t len){
	int i;
	for (i=0; i<len; i++) {
		dest[i] = src[i];
	}
	return dest;
}


volatile char* fast_memcpy(char* dest,  char* src, size_t len){
	size_t i;
	// memset(dest, 'P', len);
	char* temp_dest = dest;
	char* temp_src = src;
	memset(src, 's', len);

	// 64-byte block fast copy
	if(len >= 64){
		i = len / 64;
		len &= (64-1);
		while(i-- > 0){
			// printf("BEFORE %d:\ndest: %s\n src: %s ;;;\n\n", i, temp_dest, temp_src);
			printf("dest = %p, /16 = %d\n", dest, (int)dest%16);
			__asm__ __volatile__ (
			"movdqa (%0), %%xmm0\n"
			"movdqa 16(%0), %%xmm1\n"
			"movdqa 32(%0), %%xmm2\n"
			"movdqa 48(%0), %%xmm3\n"
			"movntps %%xmm0, (%1)\n"
			"movntps %%xmm1, 16(%1)\n"
			"movntps %%xmm2, 32(%1)\n"
			"movntps %%xmm3, 48(%1)\n"
			::"r"(src),"r"(dest):"memory");
			dest += 64;
			src += 64;
		}
		// printf("AFTER:\ndest: %s\n src: %s ;;;\n\n", temp_dest, temp_src);
		
		// src = x;
		// x = dest;
	}


	// byte-to-byte slow copy
	if(len) slow_memcpy(dest, src, len);
	return dest;
}

int main(void){

	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IOLBF, 0);

	printf("Hey, I have a boring assignment for CS class.. :(\n");
	printf("The assignment is simple.\n");

	printf("-----------------------------------------------------\n");
	printf("- What is the best implementation of memcpy?        -\n");
	printf("- 1. implement your own slow/fast version of memcpy -\n");
	printf("- 2. compare them with various size of data         -\n");
	printf("- 3. conclude your experiment and submit report     -\n");
	printf("-----------------------------------------------------\n");

	printf("This time, just help me out with my experiment and get flag\n");
	printf("No fancy hacking, I promise :D\n");

	unsigned long long t1, t2, t3, t4, t5 = 0, t6 = 0;
	int e;
	char* src;
	char* dest;
	unsigned int low, high;
	unsigned int size;
	// allocate memory
	char* cache1 = mmap(0, 0x4000, 7, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	char* cache2 = mmap(0, 0x4000, 7, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	src = mmap(0, 0x2000, 7, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	size_t sizes[10];
	int i=0;

	// setup experiment parameters
	for(e=4; e<14; e++){	// 2^13 = 8K
		low = pow(2,e-1);
		high = pow(2,e);
		printf("specify the memcpy amount between %d ~ %d : ", low, high);
		// scanf("%d", &size);
		size = high;
		if( size < low || size > high ){
			printf("don't mess with the experiment.\n");
			exit(0);
		}
		sizes[i++] = size;
	}

	sleep(1);
	printf("ok, lets run the experiment with your configuration\n");
	sleep(1);
	// while(rdtsc() < 0xFFFFFFFF- 10000)
	// 	printf("rdtsc overflow: %llu\n", rdtsc());

	// sleep(1);

	// printf("rdtsc after 1sec: %llu\n", rdtsc());

	int max_size = 0;
	// run experiment
	for(i=0; i<10; i++){
		size = sizes[i];
		// size = i;
		printf("experiment %d : memcpy with buffer size %d\n", i+1, size);
		dest = malloc( size );

		memcpy(cache1, cache2, 0x4000);		// to eliminate cache effect
		t1 = rdtsc();
		slow_memcpy(dest, src, size);		// byte-to-byte memcpy
		t2 = rdtsc();
		printf("ellapsed CPU cycles for slow_memcpy : %llu\n", t2-t1);

		memset(dest, 'd', size);

		memcpy(cache1, cache2, 0x4000);		// to eliminate cache effect
		t3 = rdtsc();
		fast_memcpy(dest, src, size);		// block-to-block memcpy
		t4 = rdtsc();
		printf("ellapsed CPU cycles for fast_memcpy : %llu\n", t2-t1);
		// if (t2 - t1 >1000 &&  t4 - t3 > 1000)
		// 	printf("size %d: slow: %llu fast: %llu, current: %llu\n", size, t2-t1, t4-t3, t4);
		// if (t5 < t2 - t1 && t6 < t4 - t3) {
		// 	t5 = t2 - t1;
		// 	t6 = t4 - t3;
		// 	max_size = size;
		// }
	}
	// printf("max size: %d, slow: %llu, fast: %llu \n", max_size, t5, t6);

	printf("thanks for helping my experiment!\n");
	printf("flag : ----- erased in this source code -----\n");
	return 0;
}
