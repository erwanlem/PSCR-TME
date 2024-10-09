#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::recursive_mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;
	void lock() const { m.lock(); };
	void unlock() const { m.unlock(); };
	bool try_lock() const { return m.try_lock(); };
};

}
