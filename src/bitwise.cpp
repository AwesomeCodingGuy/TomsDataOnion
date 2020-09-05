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
    return (x << n) | (x >> (-n & 7));
}

uint8_t rotateRight8(uint8_t value, uint8_t n)
{
    return (x >> n) | (x << (-n & 7));
}

#endif // _MSC_VER

uint8_t flipEverySecondBit8(uint8_t val)
{
    return (val ^ 0b01010101);
}

std::vector<uint8_t> flipEverySecondBitInPlace(std::vector<uint8_t> &inVec)
{
    // flip every second bit in every byte
    std::transform(inVec.begin(), inVec.end(), inVec.begin(), flipEverySecondBit8);

    return inVec;
}

std::vector<uint8_t> rotateRightEveryByteInPlace(std::vector<uint8_t> &inVec)
{
    // flip every second bit in every byte
    std::transform(inVec.begin(), inVec.end(), inVec.begin(), [](uint8_t val) { return rotateRight8(val, 1); });

    return inVec;
}

std::vector<uint8_t> bitwise_decode(std::vector<uint8_t> inVec)
{
    flipEverySecondBitInPlace(inVec);
    rotateRightEveryByteInPlace(inVec);

    return inVec;
}