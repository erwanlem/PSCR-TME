#include <vector>
#include <forward_list>

using namespace std;

template <typename K, typename V>
class HashMap {
    class Entry {
        public:
        const K key;
        V value;
        Entry(K k, V v) : key(k), value(v) {};

        bool operator==(const Entry& o) { return o.key == key && o.value == value; }
    };

    typedef vector<forward_list<Entry>> buckets_t;
    buckets_t buckets;

    public:
    class iterator {
        typedef typename vector<forward_list<Entry>>::iterator vec_iterator;
        typedef typename forward_list<Entry>::iterator list_iterator;

        vec_iterator it_vect;
        list_iterator it_list;

        public:
        iterator(vec_iterator vec, list_iterator lst) 
        : it_vect(vec)
        , it_list(lst)
        {
            while ((*it_vect).empty()) it_vect++;
            it_list = it_vect->begin();
        }

        iterator operator++() {
            if (!(it_vect->empty()) && ++it_list != it_vect->end()) {
                return *this;
            } else {
                it_vect++;
                while (it_vect->empty()) it_vect++;
                it_list = (it_vect->begin());
                return *this;
            }
        }

        iterator operator++(int) {
            iterator ret(it_vect, it_list);
            if (!(it_vect->empty()) && ++it_list != it_vect->end()) {
                return ret;
            } else {
                it_vect++;
                while (it_vect->empty()) it_vect++;
                it_list = (it_vect->begin());
                return ret;
            }
            //return ret;
        }

        Entry operator*() {
            Entry p = *it_list;
            return p;
        }

        bool operator!=(const iterator& o) {
            return it_vect != o.it_vect || it_list != o.it_list;
        }

        bool operator==(const iterator& o) {
            return !(*this != o);
        }

    };

    HashMap() : buckets(vector<forward_list<Entry>>(4096)) {
        
    };

    V* get(const K& key) {
        size_t h = hash<K>()(key);
        size_t pos = h % buckets.size();

        for (Entry& e : buckets[pos]) {
            if (e.key == key) return &e.value;
        }
        return nullptr;
    }

    bool put(const K& key, const V& value) {
        size_t h = hash<K>()(key);
        size_t pos = h % buckets.size();

        for (Entry& e : buckets[pos]) {
            if (e.key == key) {
                e.value = value;
                return true;
            }
        }
        buckets[pos].push_front(Entry(key, value));
        return true;
    }

    size_t size() const {
        return buckets.size();
    }

    vector<pair<K, V>> extract() {
        vector<pair<K, V>> vec = vector<pair<K, V>>();

        for (auto& lst : buckets) {
            for (auto& p : lst) {
                vec.push_back(pair<string, int>(p.key, p.value));
            }
        }

        return vec;
    }


    iterator begin() {
        return iterator(buckets.begin(), (*(buckets.begin())).begin());
    }

    iterator end() {
        return iterator(buckets.end(), (buckets.back()).end());
    }

};