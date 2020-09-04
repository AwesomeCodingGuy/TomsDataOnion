#include "ascii85.h"

#include <cctype>
#include <iostream>

std::vector<uint8_t> preprocessInput(const std::vector<uint8_t> &inVec)
{
    // Ignore delimiters at start and end.
    size_t startIndex = 0;
    size_t inVecLength = inVec.size();
    size_t maxDataLength = inVecLength;
    if(inVecLength > 2 && inVec[0] == '<' && inVec[1] == '~') {
        startIndex = 2;
        maxDataLength -= 2;
    }
    if(maxDataLength > 2 && inVec[inVecLength - 1] == '>' && inVec[inVecLength - 2] == '~') {
        maxDataLength -= 2;
    }

    // Ignore all Whitspace
    std::vector<uint8_t> data(maxDataLength);
    size_t idxNew = 0;
    for(size_t idxOld = startIndex; idxOld < maxDataLength + startIndex; ++idxOld) {
        if(!std::isspace(inVec[idxOld])) {
            data[idxNew++] = inVec[idxOld];
        }
    }

    data.resize(idxNew);
    return data;
}

std::vector<uint8_t> ascii85_decode(const std::vector<uint8_t> &inVec)
{
    // Check for at least one byte to encode, else return empty vector
    if(inVec.size() < 1)
        return std::vector<uint8_t>();

    // Preprocess the input vector. 
    auto data = preprocessInput(inVec);

    // Reserve space in the output vector. 
    // => 4 times the input size due to the 'z' rule
    std::vector<uint8_t> outVec;
    outVec.reserve(data.size() * 4);

    // Iterate over input characters
    size_t dataIdx = 0;
    size_t outIdx = 0;
    size_t dataLength = data.size();
    while(dataIdx < dataLength) {
        uint32_t value;

        // Check remaining length - if we need padding later
        int32_t chunk_length = dataLength - dataIdx;

        // Check for 'z' rule first
        if(data[dataIdx] == static_cast<uint8_t>('z')) {
            dataIdx += 1;
            value = 0;
            chunk_length = 5;
        // Chunk is long enough, we do not need padding
        } else if(chunk_length >= 5) {
            value = data[dataIdx++] - 33;
            value *= 85;
            value += data[dataIdx++] - 33;
            value *= 85;
            value += data[dataIdx++] - 33;
            value *= 85;
            value += data[dataIdx++] - 33;
            value *= 85; // TODO: Evaluate Overflow ?!?
            value += data[dataIdx++] - 33;
        // Chunk is not long enough, we do need padding
        } else {
            value = data[dataIdx++] - 33;
            value *= 85;
            value += (dataIdx < dataLength ? data[dataIdx++] - 33 : 84);
            value *= 85;
            value += (dataIdx < dataLength ? data[dataIdx++] - 33 : 84);
            value *= 85;
            value += (dataIdx < dataLength ? data[dataIdx++] - 33 : 84);
            value *= 85; // TODO: Evaluate Overflow ?!?
            value += (dataIdx < dataLength ? data[dataIdx++] - 33 : 84);
        }

        // Calculate byte values
        uint8_t val_3 = value % 256;
        value /= 256;
        uint8_t val_2 = value % 256;
        value /= 256;
        uint8_t val_1 = value % 256;
        value /= 256;
        uint8_t val_0 = static_cast<uint8_t>(value);

        // Simply add all bytes to the output vector
        if(chunk_length >= 5) {
            outVec.insert(outVec.end(), {val_0, val_1, val_2, val_3});
        // If we padded the data exclude padded bytes
        } else {
            if(chunk_length > 1) {
                outVec.push_back(val_0);
                if(chunk_length > 2) {
                    outVec.push_back(val_1);
                    if(chunk_length > 3) {
                        outVec.push_back(val_2);
                    }
                }
            }
        }
    }

    return outVec;
}

std::vector<uint8_t> ascii85_encode(const std::vector<uint8_t> &inVec)
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
    size_t chunks = ((dataLength + 3) / 4 - 1);
    while(chunkIdx < chunks) {
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

        ++chunkIdx;
        dataIdx += 4;
    }

    // Special attention for the last chunk.
    // Zero pad last chunk
    uint32_t value;
    size_t paddedBytes = 4 - (dataLength - dataIdx);
    value = (static_cast<uint32_t>(inVec[dataIdx]) << 24);
    value |= (dataIdx + 1 < dataLength ? (static_cast<uint32_t>(inVec[dataIdx + 1]) << 16) : 0);
    value |= (dataIdx + 2 < dataLength ? (static_cast<uint32_t>(inVec[dataIdx + 2]) << 8) : 0);
    value |= (dataIdx + 3 < dataLength ? (static_cast<uint32_t>(inVec[dataIdx + 3])) : 0);

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