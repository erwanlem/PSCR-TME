#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

    int i;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "|")) {
            argv[i] = NULL;
            break;
        }
    }
    if (i == argc) {
        exit(1);
    }

    ///////////////////

    int pipefd[2];

    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t f = fork();
    if (f == 0) {
        // fils
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        if (execv(argv[1], (char*const*)argv+1) == -1) {
            perror("execv");
            exit(1);
        }

    } else {
        // père
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (execv(argv[i+1], (char*const*)argv+(i+1)) == -1) {
            perror("execv");
            exit(1);
        }

    }
    

    return 0;
}
