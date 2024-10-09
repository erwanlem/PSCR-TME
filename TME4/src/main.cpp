#include "Banque.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

#define SOLDEINITIAL 100

using namespace std;
using namespace pr;

const int NB_ACCOUNT = 2;
const int NB_THREAD = 10;


void transaction(Banque &b, int id) {
	for (int i = 0 ; i < 1000; ++i) {
		//printf("Thread %d realise transfert\n", id);
		//cout << "Thread " << id << " realise transfert" << endl;
		b.transfert((int)(rand()%NB_ACCOUNT), (int)(rand()%NB_ACCOUNT), (int)(rand()%100+1));
		this_thread::sleep_for(chrono::milliseconds((int)rand()%2));
	}
}

void comptabilise(Banque &b) {
	for (int i = 0; i < 1000; ++i)
		b.comptabiliser(NB_ACCOUNT * SOLDEINITIAL);
}

int main () {


	srand(time(nullptr));

	Banque b(NB_ACCOUNT, SOLDEINITIAL);

	vector<thread> threads;

	threads.reserve(NB_THREAD);
	for (int i = 0; i < NB_THREAD; ++i) {
		threads.emplace_back(transaction, std::ref(b), i);
	}

	thread comptable (comptabilise, std::ref(b));
	

	for (auto & t : threads) {
		t.join();
	}
	comptable.join();

	// TODO : tester solde = NB_THREAD * JP
	cout << b.comptabiliser(NB_ACCOUNT * SOLDEINITIAL) << endl;
	return 0;
}
