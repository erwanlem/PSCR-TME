#pragma once
#include <cstddef>
#include <cstring>

namespace pr {
    std::size_t length(const char*);
    char* newcopy(const char*);
    int compare(const char* a, const char* b);
}