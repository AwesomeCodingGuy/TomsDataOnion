#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "ascii85.h"

int main(int argc, char **argv)
{
    // Read file into filestream
    std::stringstream fileStream;
    std::ifstream fileLayer1("data/layer1.txt");
    fileStream << fileLayer1.rdbuf();
    fileLayer1.close();

    // Convert filestream to string
    std::string encoded_layer1 = fileStream.str();

    // decode layer 1 string
    std::vector<uint8_t> decoded_layer1 = ascii85_decode(std::vector<uint8_t>(encoded_layer1.begin(),
                                                                              encoded_layer1.end()));

    // print decoded layer 1
    std::cout << std::string(decoded_layer1.begin(), decoded_layer1.end()) << std::endl;

    return 0;
}