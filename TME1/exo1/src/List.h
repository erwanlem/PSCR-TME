#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <cstddef>
#include <string>
#include <ostream>

namespace pr {

class Chainon {
public :
	std::string data;
	Chainon * next;
	Chainon (const std::string & data, Chainon * next=nullptr);

	// FAUTE size_t dans std::
	std::size_t length() ;

	void print (std::ostream & os) const;
};

class List {
public:

	Chainon * tete;

	List(): tete(nullptr)  {}

	~List() {
		for (Chainon * c = tete ; c ; ) {
			Chainon * tmp = c->next;
			delete c;
			c = tmp;
		}
	}

	// FAUTE size_t dans std::
	const std::string & operator[] (std::size_t index) const ;

	void push_back (const std::string& val) ;

	// FAUTE push_front définit dans List.cpp
	void push_front (const std::string& val); /*{
		tete = new Chainon(val,tete);
	}*/

	bool empty() ;

	// FAUTE size_t dans std::
	std::size_t size() const ;
};




} /* namespace pr */

// FAUTE sortir du namespace
std::ostream & operator<< (std::ostream & os, const pr::List & vec) ;

#endif /* SRC_LIST_H_ */
