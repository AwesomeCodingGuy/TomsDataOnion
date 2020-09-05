#include "gtest/gtest.h"

#include "../src/bitwise.h"

TEST(BITWISE, flipEverySecondBit8)
{
    EXPECT_EQ(flipEverySecondBit8(0b00000000), 0b01010101);
    EXPECT_EQ(flipEverySecondBit8(0b11111111), 0b10101010);
    EXPECT_EQ(flipEverySecondBit8(0b00000001), 0b01010100);
    EXPECT_EQ(flipEverySecondBit8(0b11110000), 0b10100101);
}

TEST(BITWISE, flipEverySecondBitInPlace)
{
    std::vector<uint8_t> source{0b00000000, 0b11111111, 0b00000001, 0b11110000};
    std::vector<uint8_t> test_result{0b01010101, 0b10101010, 0b01010100, 0b10100101};

    std::vector<uint8_t> result = flipEverySecondBitInPlace(source);

    EXPECT_EQ(result[0], test_result[0]);
    EXPECT_EQ(result[1], test_result[1]);
    EXPECT_EQ(result[2], test_result[2]);
    EXPECT_EQ(result[3], test_result[3]);
    EXPECT_EQ(result[0], source[0]);
    EXPECT_EQ(result[1], source[1]);
    EXPECT_EQ(result[2], source[2]);
    EXPECT_EQ(result[3], source[3]);
}