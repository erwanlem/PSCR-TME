#pragma once

#include <cstddef>



template <typename T>
class Vector {
    T* tab;
    size_t capacity;
    size_t sz;

    void ensure_capacity(size_t n) {
        if (capacity < n) {
            capacity *= 2;
            T* tmp = new T[capacity];
            for (size_t i = 0; i < sz; i++) {
                tmp[i] = tab[i];
            }
            delete[] tab;
            tab = tmp;
        }
    }

    public:
    typedef T* iterator;

    Vector(size_t cap = 10) : capacity(cap), sz(cap) {
        tab = new T[capacity];
    }
    T& operator[] (size_t index) {
        return tab[index];
    }
    const T& operator[](size_t index) const {
        return tab[index];
    }
    void push_back(const T& val) {
        ensure_capacity(sz+1);
        tab[sz++] = val;
    }

    size_t size() const {return sz;}

    iterator begin() const {return tab;}
    iterator end() const {return tab+sz;}

};