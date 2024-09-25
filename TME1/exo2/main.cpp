#include "string.h"

int main(int argc, char const *argv[])
{

    std::cout << "Hello World !" << std::endl;

    pr::String s = pr::String("Hello");

    std::cout << s << std::endl;


    std::cout << pr::compare("", "") << std::endl;
    std::cout << std::strcmp("", "") << std::endl;

    return 0;
}
