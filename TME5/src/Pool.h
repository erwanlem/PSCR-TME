#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <iostream>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) ;
	void start (int nbthread);
	void submit (Job * job) ;
	void stop() ;
	void work() ;
	~Pool() ;
};

 Pool::Pool(int qsize) : queue(qsize) {}

void Pool::submit(Job* j) {
	queue.push(j);
}

void Pool::start(int nbWorker) {
	for (int i = 0; i < nbWorker; ++i)
		threads.emplace_back( &Pool::work, this );
}

void Pool::stop() {
	queue.setBlocking(false);

	for (auto& t : threads)
		t.join();
	threads.clear();
}

void
Pool::work()
{
	while (true) {
		Job* j = queue.pop();
		if (j == nullptr) {
			return ;
		}
		j->run();
		delete j;
	}
}

Pool::~Pool() { stop(); }

}