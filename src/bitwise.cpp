#include "bitwise.h"

#include <algorithm>

// Based on the blog post
// https://blog.regehr.org/archives/1063

#ifdef _MSC_VER

#include <intrin.h>

uint8_t rotateLeft8(uint8_t value, uint8_t n)
{
    return _rotl8(value, n);
}

uint8_t rotateRight8(uint8_t value, uint8_t n)
{
    return _rotr8(value, n);
}

uint8_t bitCount8(uint8_t value)
{
    return static_cast<uint8_t>(__popcnt(value));
}

#else

uint8_t rotateLeft8(uint8_t value, uint8_t n)
{
    return (value << n) | (value >> (-n & 7));
}

uint8_t rotateRight8(uint8_t value, uint8_t n)
{
    return (value >> n) | (value << (-n & 7));
}

#endif // _MSC_VER

uint8_t flipEverySecondBit8(uint8_t val)
{
    return (val ^ 0b01010101);
}

std::vector<uint8_t> bitwise_decode(const std::vector<uint8_t> &inVec)
{
    // Copy input data.
    std::vector<uint8_t> data(inVec);

    // flip every second bit
    std::transform(data.begin(), data.end(), data.begin(), flipEverySecondBit8);

    // rotate bytes right
    std::transform(data.begin(), data.end(), data.begin(), [](uint8_t val) { return rotateRight8(val, 1); });

    return data;
}

std::vector<uint8_t> parity_decode(const std::vector<uint8_t> &inVec)
{
    // New vector for valid data.
    // Reserve space for maximum valid data.
    std::vector<uint8_t> data;
    data.reserve(inVec.size());

    // copy all bytes with valid parity
    for(auto val : inVec) {
        // if the bit count is even the byte should be valid
        if(bitCount8(val) % 2 == 0) {
            data.push_back(val);
        }
    }

    // Create new vector for the output data
    std::vector<uint8_t> outVec;
    outVec.reserve((data.size() / 8) * 7);

    // assure that the data length is a multiple of 8
    if(data.size() % 8 != 0) {
        return std::vector<uint8_t>();
    }

    // extract the data by skipping the parity bits
    for(size_t idx = 0; idx < data.size(); idx += 8) {
        uint64_t value = 0;
        // shift data to the right position
        for(int i = 0; i < 8; ++i) {
            value |= (static_cast<uint64_t>(data[idx + i] >> 1) << (49 - i * 7));
        }

        // copy data to new vector
        for(int i = 0; i < 7; ++i) {
            outVec.push_back(static_cast<uint8_t>(value >> (48 - i * 8)));
        }
    }

    return outVec;
}

uint64_t dataShift(const std::vector<uint8_t> &values) {
    uint64_t value = 0;
    for(int i = 0; i < 8; ++i) {
        value |= (static_cast<uint64_t>(values[0 + i] >> 1) << (49 - i * 7));
    }

    return value;
}