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
    };

    typedef vector<forward_list<Entry>> buckets_t;
    buckets_t buckets;

    public:
    HashMap() : buckets(vector<forward_list<Entry>>(2048)) {};

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

};