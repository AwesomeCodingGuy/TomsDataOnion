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
        std::ifstream fileLayer0("data/layer0_payload.txt");
        fileStream << fileLayer0.rdbuf();
        fileLayer0.close();

        // Convert filestream to string
        std::string encoded_layer0 = fileStream.str();

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // print decoded layer 0
        std::cout << std::string(decoded_layer0.begin(), decoded_layer0.end()) << std::endl;
    } else if(layer == 1) {
        // Read file into filestream
        std::stringstream fileStream;
        std::ifstream fileLayer1("data/layer1_payload.txt");
        fileStream << fileLayer1.rdbuf();
        fileLayer1.close();

        // Convert filestream to string
        std::string encoded_layer0 = fileStream.str();

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // decode layer 1
        std::vector<uint8_t> decoded_layer1 = bitwise_decode(decoded_layer0);

        // print decoded layer 2
        std::cout << std::string(decoded_layer1.begin(), decoded_layer1.end()) << std::endl;
    } else if(layer == 2) {
        // Read file into filestream
        std::stringstream fileStream;
        std::ifstream fileLayer1("data/layer2_payload.txt");
        fileStream << fileLayer1.rdbuf();
        fileLayer1.close();

        // Convert filestream to string
        std::string encoded_layer0 = fileStream.str();

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // decode layer 2
        std::vector<uint8_t> decoded_layer2 = parity_decode(decoded_layer0);

        // print decoded layer 3
        std::cout << std::string(decoded_layer2.begin(), decoded_layer2.end()) << std::endl;
    }

    return 0;
}