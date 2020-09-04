#include "ascii85.h"

#include <iostream>

std::vector<uint8_t> ascii85_decode(std::vector<uint8_t> &inVec)
{
    std::vector<uint8_t> outVec;



    return outVec;
}

std::vector<uint8_t> ascii85_encode(std::vector<uint8_t> &inVec)
{
    // Check for at least one byte to encode, else return empty vector
    if(inVec.size() < 1)
        return std::vector<uint8_t>();

    // Length of input vector
    size_t dataLength = inVec.size();

    // Calculate macimum length of output vector.
    // Add 4 due to delimiters at the beginning '<~' and the end '~>'.
    size_t maxOutputLength = ((dataLength + 3) / 4) * 5 + 4;

    // Reserve space in the output vector so that we can simply add all values.
    std::vector<uint8_t> outVec;
    outVec.reserve(maxOutputLength);

    // Add start delimiter
    outVec.push_back('<');
    outVec.push_back('~');

    // Process input vector in chunks of 4 bytes
    size_t chunkIdx = 0;
    size_t dataIdx = 0;
    for(; chunkIdx < ((dataLength + 3) / 4 - 1); ++chunkIdx, dataIdx += 4){
        // Calculate value
        uint32_t value;
        value = (static_cast<uint32_t>(inVec[dataIdx]) << 24);
        value |= (static_cast<uint32_t>(inVec[dataIdx + 1]) << 16);
        value |= (static_cast<uint32_t>(inVec[dataIdx + 2]) << 8);
        value |= (static_cast<uint32_t>(inVec[dataIdx + 3]));

        // If value is 0 then use special encoding character 'z'
        // Use normal encoding else
        if(value == 0) {
            outVec.push_back('z');
        } else {
            outVec.push_back(static_cast<uint8_t>((value / 52200625) % 85 + 33));
            outVec.push_back(static_cast<uint8_t>((value / 614125) % 85 + 33));
            outVec.push_back(static_cast<uint8_t>((value / 7225) % 85 + 33));
            outVec.push_back(static_cast<uint8_t>((value / 85) % 85 + 33));
            outVec.push_back(static_cast<uint8_t>(value % 85 + 33));
        }
    }

    // Special attention for the last chunk.
    // Zero pad last chunk
    uint32_t value;
    size_t paddedBytes = 4 - (inVec.size() - dataIdx);
    value = (static_cast<uint32_t>(inVec[dataIdx]) << 24);
    value |= (dataIdx + 1 < inVec.size() ? (static_cast<uint32_t>(inVec[dataIdx + 1]) << 16) : 0);
    value |= (dataIdx + 2 < inVec.size() ? (static_cast<uint32_t>(inVec[dataIdx + 2]) << 8) : 0);
    value |= (dataIdx + 3 < inVec.size() ? (static_cast<uint32_t>(inVec[dataIdx + 3])) : 0);

    // Insert last chunks bytes to output vector.
    outVec.push_back(static_cast<uint8_t>((value / 52200625) % 85 + 33));
    outVec.push_back(static_cast<uint8_t>((value / 614125) % 85 + 33));
    if(paddedBytes < 3) {
        outVec.push_back(static_cast<uint8_t>((value / 7225) % 85 + 33));
        if(paddedBytes < 2) {
            outVec.push_back(static_cast<uint8_t>((value / 85) % 85 + 33));
            if(paddedBytes < 1) {
                outVec.push_back(static_cast<uint8_t>(value % 85 + 33));
            }
        }
    }

    // Add end delimiter
    outVec.push_back('~');
    outVec.push_back('>');

    return outVec;
}