#ifndef TOMSDATAONION_BITWISE_H
#define TOMSDATAONION_BITWISE_H

#include <cstdint>
#include <vector>

uint8_t rotateLeft8(uint8_t value, uint8_t n);
uint8_t rotateRight8(uint8_t value, uint8_t n);

uint8_t flipEverySecondBit8(uint8_t val);
std::vector<uint8_t> flipEverySecondBitInPlace(std::vector<uint8_t> &data);
std::vector<uint8_t> bitwise_decode(std::vector<uint8_t> inVec);


#endif // TOMSDATAONION_BITWISE_H