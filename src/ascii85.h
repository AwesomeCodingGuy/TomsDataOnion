#ifndef TOMSDATAONION_ASCII85_H
#define TOMSDATAONION_ASCII85_H

#include <cstdint>
#include <vector>

std::vector<uint8_t> preprocessInput(const std::vector<uint8_t> &inVec);

std::vector<uint8_t> ascii85_decode(const std::vector<uint8_t> &inVec);

std::vector<uint8_t> ascii85_encode(const std::vector<uint8_t> &outVec);



#endif // TOMSDATAONION_ASCII85_H