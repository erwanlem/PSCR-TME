#include "chat_common.h"
#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

bool quit = false;

void quit_handler(int sig) {
    quit = true;
}



void send(string id, message tosend) {
    int fd;

    if ((fd = shm_open(id.c_str(), O_RDWR, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

	message* m = (message*) mmap(NULL, sizeof(message), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(m->content, tosend.content);
    m->type = 1;

    close(fd);
    munmap(m, sizeof(message));
}



int main(int argc, char const *argv[])
{

    signal(SIGINT, quit_handler);

    int fd;
    myshm* msg;

    std::unordered_set<std::string> ids;
    
    if ((fd = shm_open("/server", O_RDWR|O_CREAT|O_EXCL, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd, sizeof(myshm)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	if ((msg = (myshm*) mmap(NULL, sizeof(myshm), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

    msg->nb = 0;
    msg->read = 0;
    msg->write = 0;
    sem_init(&msg->sem, 1, 1);


    while (!quit) {

        if (msg->write > 0) {
            sem_wait(&msg->sem);
            message m = msg->messages[msg->read%MAX_MESS];
            msg->write--;
            msg->read++;
            if (m.type == 0) { // Connexion
                
                if (ids.find(m.content) == ids.end()) {
                    ids.insert(m.content);
                    cout << "New connexion " << m.content << endl;
                }

            } else if (m.type == 1) { // broadcast

                for (string s : ids) {
                    send(s, m);
                    msg->nb++;
                }

            } else if (m.type == 2) { // deconnexion

                if (ids.find(m.content) != ids.end()) {
                    ids.erase(m.content);
                    cout << "Client disconnected " << m.content << endl;
                }

            }
            sem_post(&msg->sem);

        }

    }

    sem_destroy(&msg->sem);
    
    close(fd);
	munmap(msg, sizeof(myshm));
    shm_unlink("/server");

    return 0;
}
