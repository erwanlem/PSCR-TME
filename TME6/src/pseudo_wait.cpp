#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <wait.h>


int wait_till_pid(pid_t pid) {
    if (kill(pid, 0) != 0) return -1;

    while (wait(NULL) != pid) {
        continue;
    }

    return pid;
}

int wait_till_pid (pid_t pid, int sec) {
    if (kill(pid, 0) != 0) return -1;

    sigset_t setSig;
    sigemptyset(&setSig);
    sigaddset(&setSig, SIGALRM);
    sigaddset(&setSig, SIGCHLD);

    sigprocmask(SIG_BLOCK, &setSig, NULL);

    alarm(sec);

    int sig;
    sigwait(&setSig, &sig);   

    if (sig == SIGCHLD) {
        alarm(0);
        wait(NULL);
        return pid;
    }
    else return 0;
}

int main(int argc, char const *argv[])
{
    
    pid_t f = fork();
    if (f == 0) {
        sleep(3);
    } else {
        std::cout << "pid = " << wait_till_pid(f, 2) << std::endl;
    }

    return 0;
}
