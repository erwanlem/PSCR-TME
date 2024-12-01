#include "chat_common.h"
#include <thread>
#include <string>
#include <iostream>

using namespace std;


bool quit = false;

void handler(int sig) {
    quit = true;
}


void reader(const char* name) {
    int fd;
    message* msg;

    if ((fd = shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd, sizeof(message)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	if ((msg = (message*) mmap(NULL, sizeof(message), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

    msg->type = 0;

    while (!quit) {
        if (msg->type == 1) {
            cout << ">> " << msg->content << endl;
            msg->type = 0;
        }
    }

	munmap(msg, sizeof(message));
    close(fd);
    shm_unlink(name);

}


void writer(const char* server_name, const char* my_name) {
    char to_send[TAILLE_MESS];
    int fd;
    myshm* mem_server;

    if ((fd = shm_open(server_name, O_RDWR, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

    mem_server = (myshm*) mmap(NULL, sizeof(myshm), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    message m;
    strcpy(m.content, my_name);
    m.type = 0;

    sem_wait(&mem_server->sem);
    mem_server->write++;
    mem_server->messages[mem_server->read%MAX_MESS] = m;
    sem_post(&mem_server->sem);

    while (!quit) {
        cin >> to_send;
        if (quit) break;
        strcpy(m.content, to_send);
        m.type = 1;

        sem_wait(&mem_server->sem);
        mem_server->write++;
        mem_server->messages[mem_server->read%MAX_MESS] = m;
        sem_post(&mem_server->sem);
    }

    strcpy(m.content, my_name);
    m.type = 2;

    sem_wait(&mem_server->sem);
    mem_server->write++;
    mem_server->messages[mem_server->read%MAX_MESS] = m;
    sem_post(&mem_server->sem);

}


int main(int argc, char const *argv[])
{
    signal(SIGINT, handler);
    shm_unlink(argv[1]);

    const char* name = argv[1];
    const char* server = "/server";

    thread th_read(reader, name);
    thread th_write(writer, server, name);
    
    th_read.join();
    th_write.join();

    return 0;
}
