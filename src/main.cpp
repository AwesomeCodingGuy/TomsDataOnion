#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "ascii85.h"
#include "bitwise.h"
#include "network.h"

std::string readPayloadFromFile(std::string fileName)
{
    // Read file into filestream
    std::stringstream strm;
    std::ifstream file(fileName);
    strm << file.rdbuf();
    file.close();

    return strm.str();
}

int main(int argc, char **argv)
{
    int layer = 4;

    if(layer == 0) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer0_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // print decoded layer 0
        std::cout << std::string(decoded_layer0.begin(), decoded_layer0.end()) << std::endl;
    } else if(layer == 1) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer1_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // decode layer 1
        std::vector<uint8_t> decoded_layer1 = bitwise_decode(decoded_layer0);

        // print decoded layer 2
        std::cout << std::string(decoded_layer1.begin(), decoded_layer1.end()) << std::endl;
    } else if(layer == 2) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer2_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));

        // decode layer 2
        std::vector<uint8_t> decoded_layer2 = parity_decode(decoded_layer0);

        // print decoded layer 3
        std::cout << std::string(decoded_layer2.begin(), decoded_layer2.end()) << std::endl;
    } else if(layer == 3) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer3_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));
        // decode layer 3
        std::vector<uint8_t> decoded_laye3 = xor_decode(decoded_layer0);

        // print decoded layer 3
        std::cout << std::string(decoded_laye3.begin(), decoded_laye3.end()) << std::endl;
    } else if(layer == 4) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer4_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));
        // decode layer 3
        std::vector<uint8_t> decoded_laye3 = network_decode(decoded_layer0);

        // print decoded layer 3
        std::cout << std::string(decoded_laye3.begin(), decoded_laye3.end()) << std::endl;
    } else if(layer == 5) {
        // Get encoded payload from file
        std::string encoded_layer0 = readPayloadFromFile("data/layer4_payload.txt");

        // decode layer 0 string
        std::vector<uint8_t> decoded_layer0 = ascii85_decode(std::vector<uint8_t>(encoded_layer0.begin(),
                                                                                  encoded_layer0.end()));
        // decode layer 3
        std::vector<uint8_t> decoded_laye3 = network_decode(decoded_layer0);

        // print decoded layer 3
        std::cout << std::string(decoded_laye3.begin(), decoded_laye3.end()) << std::endl;
    }

    return 0;
}


