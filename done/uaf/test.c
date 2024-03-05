#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
    if (argc <= 1){
        printf("Provide an argument as the username :)\n");
        exit(0);
    }
    printf("Basic ARM Heap overflow challenge \n");

    char *name = malloc(64);
    char *cmd = malloc(64);

    strcpy(cmd,"whoami");

    strcpy(name,argv[1]);

    printf("%s is executing the command %s",name,cmd);
    printf("\n\n");

    system(cmd);

}

prev_size
name_size
name_data - 64
prev_size == name_size
cmd_size
cmd_data