#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int stdin_pipe_fd[2];
    int stderr_pipe_fd[2];
    pid_t cpid;
    // char argv_buf[] = "3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 9999 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3";
    
    char *argv[] = { "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "\x00", "\x20\x0a\x0d", "21299", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", 0 };
    char *envp[] =
    {
        "\xde\xad\xbe\xef=\xca\xfe\xba\xbe",
        0
    };
    // printf("kaki=%s\n", argv['B']);
    // return;
    pipe(stdin_pipe_fd); /* first pair of pipe descriptors */
    pipe(stderr_pipe_fd); /* second pair of pipe descriptors */

    switch (fork()) {
    case 0: /* child */
        /* close write ends of both pipes */
        close(stdin_pipe_fd[1]);
        close(stderr_pipe_fd[1]);

        /* redirect stdin to read end of first pipe, 4 to read end of second pipe */
        dup2(stdin_pipe_fd[0], 0);
        dup2(stderr_pipe_fd[0], 2);
        // dup2(stderr_pipe_fd[0], 4);

        /* the original read ends of the pipes are not needed anymore */
        close(stdin_pipe_fd[0]);
        close(stderr_pipe_fd[0]);
        // chdir("/home/input2/");
        FILE* fp = fopen("\x0a", "w");
        fwrite("\x00\x00\x00\x00", 4, 1, fp);
        fclose(fp);
        execve("/home/input2/input", argv, envp);
        break;

    case -1:
        /* could not fork child */
        break;

    default: /* parent */
        /* close read ends of both pipes */
        close(stderr_pipe_fd[0]);
        close(stdin_pipe_fd[0]);

        /* write to first pipe (delivers to stdin in the child) */
        write(stdin_pipe_fd[1], "\x00\x0a\x00\xff", 4);
        /* write to second pipe (delivers to 4 in the child) */
        write(stderr_pipe_fd[1], "\x00\x0a\x02\xff", 4);
        printf("Parent is out!");
        break;
    }
}