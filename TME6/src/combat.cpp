#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "rsleep.h"
#include <string>
#include <wait.h>

int vie = 3;
std::string name;

using namespace std;


void exitHandler(int sig) { exit(0); }


void defenseHandler(int sig) {
    std::cout << "Coup paré !" << endl;
}


void handler(int sig) {
    std::cout << "Touché !" << std::endl;
    vie--;
    if (vie == 0) {
        cout << name << " died" << endl;
        exit(1);
    }

    signal(SIGINT, &handler);
}


void attaque(pid_t adversaire) {
    signal(SIGINT, handler);

    if (kill(adversaire, SIGINT) == -1 ) exit(0);
    

    randsleep();
}

void defense() {
    struct sigaction act;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = &defenseHandler;
    sigaction(SIGINT, &act, NULL);

    randsleep();
}


void defenseLuke() {
    struct sigaction act;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = &defenseHandler;
    sigaction(SIGINT, &act, NULL);

    sigset_t setPos, oldMask;
    sigemptyset(&setPos);
    sigaddset(&setPos, SIGINT);
    sigprocmask(SIG_BLOCK, &setPos, &oldMask);

    randsleep();

    sigsuspend(&oldMask);
    sigprocmask( SIG_UNBLOCK, &setPos, NULL );
}

void combat(pid_t adversaire) {
    while (true) {
        if (name == "Luke") defenseLuke();
        else defense();

        attaque(adversaire);
    }
}



int main(int argc, char const *argv[])
{
    pid_t f = fork();

    if (f == 0) {
        srand(time(NULL));
        name = "Luke";
        combat(getppid());
    } else {
        srand(time(NULL));
        signal(SIGCHLD, exitHandler);

        name = "Vader";
        combat(f);
    }

    return 0;
}
