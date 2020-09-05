#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "ascii85.h"
#include "bitwise.h"

int main(int argc, char **argv)
{
    int layer = 2;

    if(layer == 0) {
        // Read file into filestream
        std::stringstream fileStream;
        std::ifstream fileLayer1("data/layer0_payload.txt");
        fileStream << fileLayer1.rdbuf();
        fileLayer1.close();

        // Convert filestream to string
        std::string encoded_layer1 = fileStream.str();

        // decode layer 1 string
        std::vector<uint8_t> decoded_layer1 = ascii85_decode(std::vector<uint8_t>(encoded_layer1.begin(),
                                                                                  encoded_layer1.end()));

        // print decoded layer 1
        std::cout << std::string(decoded_layer1.begin(), decoded_layer1.end()) << std::endl;
    } else if(layer == 1) {
        // Read file into filestream
        std::stringstream fileStream;
        std::ifstream fileLayer1("data/layer1_payload.txt");
        fileStream << fileLayer1.rdbuf();
        fileLayer1.close();

                // Convert filestream to string
        std::string encoded_layer1 = fileStream.str();

        // decode layer 1 string
        std::vector<uint8_t> decoded_layer1 = ascii85_decode(std::vector<uint8_t>(encoded_layer1.begin(),
                                                                                  encoded_layer1.end()));

        // decode layer 2
        std::vector<uint8_t> decoded_layer2 = bitwise_decode(decoded_layer1);

        // print decoded layer 1
        std::cout << std::string(decoded_layer2.begin(), decoded_layer2.end()) << std::endl;
    } else if(layer == 2) {

    }

    return 0;
}