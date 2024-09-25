#include "string.h"

namespace pr {

    String::String(const char* ori) : str(newcopy(ori)) {}

    String::String(const String& ori) : str(newcopy(ori.str)) {}

    String::~String() {
        delete []str;
    }

    std::size_t String::length() const {
        return pr::length(str);
    }

    String& String::operator=(const String& s) {
        if (this != &s) {
            delete[] str;
            str = newcopy(s.str);
        }
        return *this;
    }
}