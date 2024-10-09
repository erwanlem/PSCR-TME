#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	/*if (debiteur.try_lock()) {
		if (crediteur.try_lock()) {
			if (debiteur.debiter(val)) {
				crediteur.crediter(val);
			}
			crediteur.unlock();
		}
	debiteur.unlock();
	}*/

	//m.lock();

	if (deb < cred) {
		debiteur.lock();
		crediteur.lock();
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
		crediteur.unlock();
		debiteur.unlock();
	} else {
		crediteur.lock();
		debiteur.lock();
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
		debiteur.unlock();
		crediteur.unlock();
	}

	//m.unlock();

}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	//m.lock();
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		compte.lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	
	for (const auto & compte : comptes)
		compte.unlock();

	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}

	//m.unlock();
	return bilan == attendu;
}
}
