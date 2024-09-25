#include "strutil.h"
#include <iostream>

namespace pr {

    std::size_t length(const char* str) {
        const char* cp = str;
        for ( ; *cp; ++cp);
        return cp-str;
    }

    char* newcopy(const char* str) {
        std::size_t len = length(str);
        char* res = new char[len+1];
        memcpy(res, str, len+1);
        return res;
    }

    int compare(const char* a, const char* b) {
        while (*a && *b && *a-*b == 0 ){ *a++; *b++;}
        return *a - *b > 0 ? 1 : (*a - *b < 0) ? -1 : 0;
    }
}