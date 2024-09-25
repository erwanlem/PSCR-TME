#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

#include "hashmap.h"
#include "vector.h"
#include "list.h"


void add_in_pair(std::vector<std::pair<std::string, int>>& v, std::string w) {
	using namespace std;

	int found = false;
	for (pair<string, int>& p : v) {
		if (p.first == w) {
			p.second++;
			return ;
		}
	}
	v.push_back(pair<string, int>(w, 1));
}



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

	HashMap<string, int> hm = HashMap<string, int>();

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

		/*
		// Question 1
		bool find = false;
		for (string s : words) {
			if (s == word) {
				find = true;
				break;
			}
		}
		if (!find) words.push_back(word); 
		*/

		// Question 2 - 4
		//add_in_pair(words_pair, word);
		
		int* val = hm.get(word);
		if (val)
			hm.put(word, (*val)+1);
		else
			hm.put(word, 1);
			

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

	// Question 1
	// cout << "Found " << words.size() << " different words." << endl;

	// Question 4
	/*for (pair<string, int> p : words_pair) {
		if (p.first == "toto" || p.first == "war" || p.first == "peace") {
			cout << p.first << " : " << p.second << endl;
		}
	}*/

	//cout << "toto : " << (hm.get("toto") == nullptr ? "0" : "not null") << endl;
	//cout << "war : " << *(hm.get("war")) << endl;
	//cout << "peace : " << *(hm.get("peace")) << endl;

	vector<pair<string, int>> cpy = hm.extract();

	sort(cpy.begin(), cpy.end(), [] (pair<string, int>& e1, pair<string, int>& e2) {return e1.second > e2.second;});

	for (int i = 0; i < 10; i++) {
		cout << cpy[i].first << " : " << cpy[i].second << endl;
	}

    return 0;
}


