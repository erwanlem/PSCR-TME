#include <iostream>
#include <unistd.h>
#include <wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int children = 0;

	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if (fork() == 0) {
			std::cout << "my pid : " << getpid() << " , my father : " << getppid() << std::endl;
			std::cout << " i:j " << i << ":" << j << std::endl;
			children = 0;

			for (int k=1; k<=i && j==N ; k++) {
				if ( fork() == 0) {
					children = 0;
					//std::cout << "my pid : " << getpid() << " , my father : " << getppid() << std::endl;
					j=0;
					std::cout << " k:j " << k << ":" << j << std::endl;
				} else {
					children++;
				}
			}
		} else {
			children++;
			break;
		}
	}

	for (int i = 0; i < children; i++) {
		pid_t pid = wait(NULL);
		std::cout << pid << " end" << std::endl;
	}

	return 0;
} // 9 processus créés (10 avec le main)
