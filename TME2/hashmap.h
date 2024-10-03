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
    buckets_t _buckets;
    int entriesNumber;

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
            // Same function as operator++() but postfix
            iterator ret(it_vect, it_list);
            if (!(it_vect->empty()) && ++it_list != it_vect->end()) ;
            else {
                it_vect++;
                while (it_vect->empty()) it_vect++;
                it_list = (it_vect->begin());
            }
            return ret;
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

    HashMap(int initial_size = 16) 
    : _buckets(vector<forward_list<Entry>>(initial_size))
    , entriesNumber(0) {};



    /**
     * returns the value associated with the given key
     * if the key doesn't exist returns nullptr
     */
    V* get(const K& key) {
        size_t h = hash<K>()(key);
        size_t pos = h % _buckets.size();

        for (Entry& e : _buckets[pos]) {
            if (e.key == key) return &e.value;
        }
        return nullptr;
    }

    /**
     * adds an element in the hashmap
     */
    bool put(const K& key, const V& value) {
        size_t h = hash<K>()(key);
        size_t pos = h % _buckets.size();

        for (Entry& e : _buckets[pos]) {
            if (e.key == key) {
                e.value = value;
                return true;
            }
        }
        _buckets[pos].push_front(Entry(key, value));
        entriesNumber++;
        grow();
        return true;
    }

    /**
     * returns the size of the hashmap
     */
    size_t size() const {
        return entriesNumber;
    }


    /**
     * returns a vector containing every pair in the hashmap
     */
    vector<pair<K, V>> extract() {
        vector<pair<K, V>> vec = vector<pair<K, V>>();

        for (auto& lst : _buckets) {
            for (auto& p : lst) {
                vec.push_back(pair<string, int>(p.key, p.value));
            }
        }

        return vec;
    }


    iterator begin() {
        return iterator(_buckets.begin(), (*(_buckets.begin())).begin());
    }

    iterator end() {
        return iterator(_buckets.end(), (_buckets.back()).end());
    }

    private:

        void grow() {
            if ( entriesNumber > 10 * _buckets.size() ) {
                HashMap<K, V> tmp(this->_buckets.size()*2);
                for (Entry e : *this) {
                    tmp.put(e.key, e.value);
                }
                this->_buckets = tmp._buckets;
            }
        }

};