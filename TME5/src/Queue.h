#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <cstring>
#include <mutex>
#include <condition_variable>

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	mutable std::mutex m;
	std::condition_variable cond;
	
	std::condition_variable emptyCond, fullCond;

	bool isBlocking;
	

	// fonctions private, sans protection mutex
	bool empty() const {
		return sz == 0;
	}
	bool full() const {
		return sz == allocsize;
	}
public:
	Queue(size_t size) :allocsize(size), begin(0), sz(0), isBlocking(true) {
		tab = new T*[size];
		memset(tab, 0, size * sizeof(T*));
	}
	
	size_t size() const {
		std::unique_lock<std::mutex> lg(m);
		return sz;
	}

	T* pop() {
		std::unique_lock<std::mutex> lg(m);
		while (empty() && isBlocking) {
			//cond.wait(lg);
			emptyCond.wait(lg);
		}
		if (empty()) return nullptr;
		auto ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsize;


		fullCond.notify_one();
		return ret;
	}

	bool push(T* elt) {
		std::unique_lock<std::mutex> lg(m);
		while (full() && isBlocking) {
			fullCond.wait(lg);
		}
		if (full()) return false;
		tab[(begin + sz) % allocsize] = elt;
		sz++;

		emptyCond.notify_one();
		return true;
	}

	void setBlocking (bool block) {
		std::unique_lock<std::mutex> l(m);
		isBlocking = block;
		fullCond.notify_all();
		emptyCond.notify_all();
	}

	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			if (tab[ind] == nullptr) delete tab[ind];
		}
		delete[] tab;
	}
};

}

#endif /* SRC_QUEUE_H_ */
