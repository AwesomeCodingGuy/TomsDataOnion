#include "network.h"

uint16_t byteSwap16(uint16_t value)
{
    return ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
}

uint32_t byteSwap32(uint32_t value)
{
    return ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8) | ((value & 0x000000FF) << 24);
}

bool Packet::isValid() const
{
    return (validateIpHeader() && validateUdpHeader());
}

size_t Packet::readPacket(const std::vector<uint8_t> &data, size_t startIndex)
{
    // check the remaining size.
    // if there less than a packet header to read then return
    if(startIndex + 28 > data.size())
        return data.size();

    // get pointer to current packet data block
    const uint8_t *ptr = &data.data()[startIndex];

    // Read essential IP Header data
    ipHeader.protocol = (*(uint16_t *)&ptr[8] >> 8);
    ipHeader.srcAddress = byteSwap32(*(uint32_t *)&ptr[12]);
    ipHeader.dstAddress = byteSwap32(*(uint32_t *)&ptr[16]);

    // Read essential UDP Header data
    udpHeader.srcPort = byteSwap16(*(uint16_t *)&ptr[20]);
    udpHeader.dstPort = byteSwap16(*(uint32_t *)&ptr[22]);
    udpHeader.udpLength = byteSwap16(*(uint32_t *)&ptr[24]);

    // Copy packet header data and payload
    this->data.clear();
    this->data.insert(this->data.end(),
                      data.begin() + startIndex, 
                      data.begin() + startIndex + 20 + udpHeader.udpLength);

    return 20 + (size_t)udpHeader.udpLength;
}

bool Packet::validateIpHeader() const
{
    // get a raw pointer to packet data
    // and cast it to 16bit since we add 2-byte values.
    uint16_t *ptr = (uint16_t *)this->data.data();

    uint32_t checksum = 0;
    for(int idx = 0; idx < 10; ++idx) {
        checksum += *(ptr++);
    }

    checksum = (0xFFFF & checksum) + (checksum >> 16);
    // the addition might add another carry bit, so we do this twice
    checksum = (0xFFFF & checksum) + (checksum >> 16);

    // flipping the bits should result in 0
    uint16_t checksum16 = ~checksum;

    return checksum16 == 0;
}

bool Packet::validateUdpHeader() const
{
    // get a raw pointer to packet data
    // and cast it to 16bit since we add 2-byte values.
    uint16_t *ptr = (uint16_t *)this->data.data();

    // first calculate the checksum over the payload
    uint32_t checksum = 0;
    // move pointer to payload
    ptr += 14;
    // calculate payload length in steps of 2 byte
    uint16_t payloadLength = udpHeader.udpLength - 8;
    uint16_t len = payloadLength / 2;
    for(int idx = 0; idx < len; ++idx) {
        checksum += *(ptr++);
    }

    // if the payload length is odd, zero pad and add to checksum
    if(payloadLength % 2 > 0) {
        checksum += ((*ptr) & 0x00FF);
    }

    // Add the pseudo header
    uint32_t src = byteSwap32(ipHeader.srcAddress);
    checksum += (src & 0xFFFF) + (src >> 16 & 0xFFFF);
    uint32_t dst = byteSwap32(ipHeader.dstAddress);
    checksum += (dst & 0xFFFF) + (dst >> 16 & 0xFFFF);
    checksum += byteSwap16(ipHeader.protocol);
    checksum += byteSwap16(udpHeader.udpLength);

    // Add udp Header
    checksum += *(uint16_t *)&this->data[20];
    checksum += *(uint16_t *)&this->data[22];
    checksum += *(uint16_t *)&this->data[24];
    checksum += *(uint16_t *)&this->data[26];

    checksum = (0xFFFF & checksum) + (checksum >> 16);
    // the addition might add another carry bit, so we do this twice
    checksum = (0xFFFF & checksum) + (checksum >> 16);

    // flipping the bits should result in 0
    uint16_t checksum16 = ~checksum;

    return checksum16 == 0;
}

std::vector<uint8_t> network_decode(const std::vector<uint8_t> &inVec)
{
    // first we collect all packets from the input stream
    // no matter the data it contains
    std::vector<Packet> packets;
    size_t packetIndex = 0;
    while(packetIndex < inVec.size()) {
        Packet p;
        packetIndex += p.readPacket(inVec, packetIndex);
        packets.emplace_back(p);
    }

    // init vector for decoded data
    std::vector<uint8_t> data;

    // we discard all packets that do not match the requirements
    // all other packets' payloads will be added to the data vector
    constexpr uint32_t srcAddress = 167837962; // 10.1.1.10
    constexpr uint32_t dstAddress = 167838152; // 10.1.1.200
    constexpr uint16_t dstPort = 42069;

    // iterate over packets
    for(const Packet &p : packets) {
        if(p.ipHeader.srcAddress == srcAddress
           && p.ipHeader.dstAddress == dstAddress
           && p.udpHeader.dstPort == dstPort
           && p.isValid()) {
            data.insert(data.end(),
                        p.data.begin() + 28,
                        p.data.end());
        }
    }

    return data;
}