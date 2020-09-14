#include "gtest/gtest.h"

#include "../src/network.h"

TEST(NETWORK, byteSwap16)
{
    EXPECT_EQ(byteSwap16(0xFF00), 0x00FF);
    EXPECT_EQ(byteSwap16(0x1122), 0x2211);
    EXPECT_EQ(byteSwap16(0x0000), 0x0000);
    EXPECT_EQ(byteSwap16(0xEFFE), 0xFEEF);
}

TEST(NETWORK, byteSwap32)
{
    EXPECT_EQ(byteSwap32(0xFF000000), 0x000000FF);
    EXPECT_EQ(byteSwap32(0x11223344), 0x44332211);
    EXPECT_EQ(byteSwap32(0x00000000), 0x00000000);
    EXPECT_EQ(byteSwap32(0xEFFE1234), 0x3412FEEF);
}

uint8_t datagram[49] = {
  0x45, 0x00,
  0x00, 0x31, 0x00, 0x00, 0x40, 0x00, 0x3b, 0x11,
  0xbb, 0xe6, 0xac, 0xd9, 0x16, 0x42, 0xc0, 0xa8,
  0x00, 0x12, 0x01, 0xbb, 0xc5, 0xd5, 0x00, 0x1d,
  0xe8, 0x2d, 0x41, 0x00, 0x55, 0x53, 0xfa, 0xbb,
  0x45, 0x91, 0x5d, 0xcd, 0xa9, 0xa6, 0x8a, 0x41,
  0x50, 0x4a, 0xf2, 0x87, 0x8b, 0xf6, 0x95
};

uint16_t srcPort = 443;
uint16_t dstPort = 50645;
uint16_t dataLength = 29;
uint16_t payloadLength = 21;
uint16_t protocol = 17;
std::string srcStr = "172.217.22.66";
uint32_t src = 2899908162;
std::string dstStr = "192.168.0.18";
uint32_t dst = 3232235538;


TEST(NETWORK_Packet, readPacket)
{
    std::vector<uint8_t> vec(datagram, datagram + 49);

    Packet p;
    size_t ret = p.readPacket(vec, 0);

    EXPECT_EQ(ret, 49);
    EXPECT_EQ(p.ipHeader.srcAddress, src);
    EXPECT_EQ(p.ipHeader.dstAddress, dst);
    EXPECT_EQ(p.ipHeader.protocol, protocol);
    EXPECT_EQ(p.udpHeader.srcPort, srcPort);
    EXPECT_EQ(p.udpHeader.dstPort, dstPort);
    EXPECT_EQ(p.udpHeader.udpLength, dataLength);
}

TEST(NETWORK_Packet, isValid)
{
    std::vector<uint8_t> vec(datagram, datagram + 49);

    Packet p;
    size_t ret = p.readPacket(vec, 0);

    EXPECT_EQ(ret, 49);
    EXPECT_EQ(p.ipHeader.srcAddress, src);
    EXPECT_EQ(p.ipHeader.dstAddress, dst);
    EXPECT_EQ(p.ipHeader.protocol, protocol);
    EXPECT_EQ(p.udpHeader.srcPort, srcPort);
    EXPECT_EQ(p.udpHeader.dstPort, dstPort);
    EXPECT_EQ(p.udpHeader.udpLength, dataLength);

    EXPECT_TRUE(p.isValid());
}



