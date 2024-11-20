#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <iostream>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t sem_pop, sem_push, sem;
	
public :
	Stack () : sz(0) {
		memset(tab,0,sizeof tab) ;
		sem_init(&sem_pop, 1, 0);
		sem_init(&sem, 1, 1);
		sem_init(&sem_push, 1, STACKSIZE);
	}

	T pop () {
		// bloquer si vide

		sem_wait(&sem_pop);
		sem_wait(&sem);
		T toret = tab[--sz];
		sem_post(&sem);
		sem_post(&sem_push);
		return toret;
	}

	void push(T elt) {
		sem_wait(&sem_push);
		sem_wait(&sem);
		tab[sz++] = elt;
		sem_post(&sem);
		sem_post(&sem_pop);
	}
};

}
