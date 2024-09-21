// FAUTE pas de include "List.h"
#include "List.h"


namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

// FAUTE size_t dans std::
std::size_t Chainon::length() {
	std::size_t len = 1;
	if (next != nullptr) {
		len += next->length();
	}
	return len; // FAUTE récursion infinie length();
}


// FAUTE de correspond pas à la définition de print dans List.h
void Chainon::print (std::ostream & os) const {
	os << data ;
	if (next != nullptr) {
		os << ", ";
	} else {
		return ;
	}
	next->print(os);
}

// ******************  List
const std::string & List::operator[] (std::size_t index) const  {
	Chainon * it = tete;
	for (std::size_t i=0; i < index ; i++) {
		it = it->next;
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}

void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}

// FAUTE manque List::
bool List::empty() {
	return tete == nullptr;
}

std::size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}

} // namespace pr

std::ostream & operator<< (std::ostream & os, const pr::List & vec)
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]";
	return os;
}
