#include "vector.h"
#include <iostream>
#include "list.h"
#include "hashmap.h"
#include "algorithm.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{

    cout << "Vector" << endl;

    Vector<int> v = Vector<int>(10);
    for (int i = 0; i < 10; i++) {
        v[i] = i%2 == 0 ? 1 : 0;
    }

    for (int i : v) {
        cout << i << " ";
    }

    cout << endl << count(v.begin(), v.end()) << endl;
    cout << endl << count_if_equal(v.begin(), v.end(), 0) << endl;

    /*

    cout << "End list" << endl;

    cout << "List" << endl;

    List<int> l = List<int>();
    for (int i = 0; i < 10; i++) {
        l.push_front(i);
    }

    for (auto i : l) {
        cout << i << " ";
    }

    cout << "End list" << endl;

    HashMap<string, int> h = HashMap<string, int>();

    
    h.put("un", 1);
    h.put("deux", 2);
    h.put("trois", 3);


    for (auto p : h) {
        cout << "IT" << endl;
        cout << p.key << " -- " << p.value << endl;
    }

    */

    
    return 0;
}
