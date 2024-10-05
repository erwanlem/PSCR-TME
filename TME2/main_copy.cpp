#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>

#include "hashmap.h"
#include "algorithm.h"
#include "vector.h"
#include "list.h"


/***********************************/
/************** TME3 ***************/
/***********************************/


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	// Question 1
	vector<string> words = vector<string>();

	// Question 2 - 4
	vector<pair<string, int>> words_pair = vector<pair<string, int>>();

    unordered_map<string, int> hm = unordered_map<string, int>();

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		
        auto r = hm.insert(pair<string, int>(word, 1));
		if (!r.second) (*r.first).second++;

		// word est maintenant "tout propre"
		//if (nombre_lu % 10000 == 0)
			// on affiche un mot "propre" sur 100
			//cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

    for (auto p : hm) {
        cout << p.first << ": " << p.second << endl;
    }

    ////////////////
    // Question 8 //
    ////////////////

    unordered_map<int, forward_list<string>> inv = unordered_map<int, forward_list<string>>();

    for (auto p : hm) {
        auto r = inv.insert(pair<int, forward_list<string>>(p.second, forward_list<string>({p.first})));
        if (!r.second) (*r.first).second.push_front(p.first);
    }

    for (auto p : inv) {
        cout << p.first << ": ";
        for (auto w : p.second) {
            cout << w << ", ";
        }
        cout << endl;
    }

    return 0;
}


