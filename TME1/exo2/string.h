#pragma once
#include "strutil.h"
#include <iostream>

namespace pr {

    class String {
        private:
        const char* str;

        public:
        String(const char* ori="");
        String(const String& ori);
        ~String();
        std::size_t length() const;
        String& operator=(const String& s);
        friend std::ostream& operator<<(std::ostream& os, const pr::String s) {
            os << s.str << std::endl;
            return os;
        }
    };

}