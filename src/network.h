#ifndef TOMSDATAONION_NETWORK_H
#define TOMSDATAONION_NETWORK_H

#include <cstdint>
#include <vector>

uint16_t byteSwap16(uint16_t value);
uint32_t byteSwap32(uint32_t value);

struct IPv4Header
{
    uint32_t srcAddress;
    uint32_t dstAddress;
    uint16_t protocol;
};

struct UdpHeader
{
    uint16_t srcPort;
    uint16_t dstPort;
    uint16_t udpLength;
};

class Packet
{
public:

    IPv4Header ipHeader;
    UdpHeader udpHeader;
    std::vector<uint8_t> data;

    bool isValid() const;
    size_t readPacket(const std::vector<uint8_t> &data, size_t startIndex);

private:
    bool validateIpHeader() const;
    bool validateUdpHeader() const;
};

std::vector<uint8_t> network_decode(const std::vector<uint8_t> &inVec);

#endif // TOMSDATAONION_NETWORK_H