#ifndef TOMSDATAONION_BITWISE_H
#define TOMSDATAONION_BITWISE_H

#include <cstdint>
#include <vector>

uint8_t rotateLeft8(uint8_t value, uint8_t n);
uint8_t rotateRight8(uint8_t value, uint8_t n);
uint8_t bitCount8(uint8_t value);

uint8_t flipEverySecondBit8(uint8_t val);
std::vector<uint8_t> bitwise_decode(const std::vector<uint8_t> &inVec);

std::vector<uint8_t> parity_decode(const std::vector<uint8_t> &inVec);

uint64_t dataShift(const std::vector<uint8_t> &values);


#endif // TOMSDATAONION_BITWISE_H