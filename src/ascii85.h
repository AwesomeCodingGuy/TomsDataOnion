#ifndef ASCII85_H
#define ASCII85_H

#include <vector>

std::vector<uint8_t> ascii85_decode(std::vector<uint8_t> &inVec);

std::vector<uint8_t> ascii85_encode(std::vector<uint8_t> &outVec);



#endif // ASCII85_H