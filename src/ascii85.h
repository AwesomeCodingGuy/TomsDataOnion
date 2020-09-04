#ifndef ASCII85_H
#define ASCII85_H

#include <vector>

std::vector<uint8_t> preprocessInput(const std::vector<uint8_t> &inVec);

std::vector<uint8_t> ascii85_decode(const std::vector<uint8_t> &inVec);

std::vector<uint8_t> ascii85_encode(const std::vector<uint8_t> &outVec);



#endif // ASCII85_H