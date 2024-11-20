#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char** command1 = new char*[argc];
    char** command2 = new char*[argc];

    int c1 = 0; int c2 = 0;
    bool changeCommand = false;

    for (int i = 0; i < argc-1; ++i) {

        if ( ! strcmp(argv[i+1], "|") ) {
            changeCommand = true;
        } else {
            int len = strlen(argv[i+1]);
            if (changeCommand) {
                char* w = new char[len];
                strncpy(w, argv[i+1], sizeof(argv[i+1]));
                command2[c2] = w;
                c2++;
            } else {
                char* w = new char[len];
                strncpy(w, argv[i+1], sizeof(argv[i+1]));
                command1[c1] = w;
                c1++;
            }
        }
    }
    command1[c1] = NULL;
    command2[c2] = NULL;

    int i;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "|")) {
            argv[i] = nullptr;
            break;
        }
    }
    if (i == argc) {
        exit(1);
    }

    ///////////////////


    pid_t f = fork();
    int pipefd[2];

    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    if (f == 0) {
        // fils
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        execv(command1[0], command1);

    } else {
        // père
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execv(command2[0], command2);

    }
    

    return 0;
}
