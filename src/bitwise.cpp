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