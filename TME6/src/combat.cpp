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
    std::cout << "";
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
    struct sigaction act;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = &handler;


    if (kill(adversaire, SIGINT) == -1 ) exit(0);
    

    randsleep();
}

void defense() {
    signal(SIGINT, SIG_IGN);

    randsleep();
}

void combat(pid_t adversaire) {
    while (true) {
        defense();
        attaque(adversaire);
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    pid_t f = fork();

    if (f == 0) {
        name = "Luke";
        combat(getppid());
    } else {
        signal(SIGCHLD, exitHandler);

        name = "Vader";
        combat(f);
    }

    return 0;
}
