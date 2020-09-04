#include <iostream>
#include <string>

#include "ascii85.h"

int main(int argc, char **argv)
{
    std::string string1("abcde");
    std::string string2("abcdefghijkl");

    auto payload1 = std::vector<uint8_t>(string1.begin(), string1.end());
    auto payload2 = std::vector<uint8_t>(string2.begin(), string2.end());

    auto encoded1 = ascii85_encode(payload1);
    auto encoded2 = ascii85_encode(payload2);

    std::cout << std::string(encoded1.begin(), encoded1.end()) << std::endl;
    std::cout << std::string(encoded2.begin(), encoded2.end()) << std::endl;

    return 0;
}