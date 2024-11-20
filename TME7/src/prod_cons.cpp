#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



using namespace std;
using namespace pr;

void* sp;
int fd;

void handler_father(int sig) {
	close(fd);
	munmap(sp, sizeof(Stack<char>));
	shm_unlink("/stackshm");
	exit(0);
}

void handler_children(int sig) {
	close(fd);
	munmap(sp, sizeof(Stack<char>));
	exit(0);
}




void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}




int main () {
	signal(SIGINT, handler_father);

	if ((fd = shm_open("/stackshm", O_RDWR|O_CREAT|O_EXCL, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	if ((sp = (Stack<char>*) mmap(NULL, sizeof(Stack<char>), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	Stack<char> * s = new (sp) Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		signal(SIGINT, handler_children);

		producteur(s);

		close(fd);
		munmap(sp, sizeof(Stack<char>));
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		signal(SIGINT, handler_children);

		consomateur(s);
		
		close(fd);
		munmap(sp, sizeof(Stack<char>));
		return 0;
	}

	wait(0);
	wait(0);

	close(fd);
	munmap(sp, sizeof(Stack<char>));

	shm_unlink("/stackshm");

	delete s;
	return 0;
}

