#include <cstddef>
#include <iterator>


template<typename iterator>
std::size_t count (iterator begin, iterator end) {
    std::size_t i = 0;
    while (begin != end) {
        i++;
        begin++;
    }
    return i;
}

template<typename iterator, typename T>
std::size_t count_if_equal(iterator begin, iterator end, const T& val) {
    std::size_t i = 0;
    while (begin != end)
        if (*(begin++) == val) i++;
    return i;
}