#include "gtest/gtest.h"

#include "../src/bitwise.h"

TEST(BITWISE, rotateLeft8)
{
    EXPECT_EQ(rotateLeft8(0b00000000, 1), 0b00000000);
    EXPECT_EQ(rotateLeft8(0b00000001, 1), 0b00000010);
    EXPECT_EQ(rotateLeft8(0b10000000, 1), 0b00000001);
    EXPECT_EQ(rotateLeft8(0b11110000, 4), 0b00001111);
}

TEST(BITWISE, rotateRight8)
{
    EXPECT_EQ(rotateRight8(0b00000000, 1), 0b00000000);
    EXPECT_EQ(rotateRight8(0b00000001, 1), 0b10000000);
    EXPECT_EQ(rotateRight8(0b10000000, 1), 0b01000000);
    EXPECT_EQ(rotateRight8(0b11110000, 4), 0b00001111);
}

TEST(BITWISE, flipEverySecondBit8)
{
    EXPECT_EQ(flipEverySecondBit8(0b00000000), 0b01010101);
    EXPECT_EQ(flipEverySecondBit8(0b11111111), 0b10101010);
    EXPECT_EQ(flipEverySecondBit8(0b00000001), 0b01010100);
    EXPECT_EQ(flipEverySecondBit8(0b11110000), 0b10100101);
}

TEST(BITWISE, bitwise_decode)
{
    std::vector<uint8_t> source{0b11110000, 0b10101010};
    std::vector<uint8_t> test_result{0b11010010, 0b11111111};

    auto result = bitwise_decode(source);

    EXPECT_EQ(result[0], test_result[0]);
    EXPECT_EQ(result[1], test_result[1]);
}

TEST(BITWISE, bitCount8)
{
    EXPECT_EQ(bitCount8(0b11111111), 8);
    EXPECT_EQ(bitCount8(0b11111110), 7);
    EXPECT_EQ(bitCount8(0b11111100), 6);
    EXPECT_EQ(bitCount8(0b11111000), 5);
    EXPECT_EQ(bitCount8(0b11110000), 4);
    EXPECT_EQ(bitCount8(0b11100000), 3);
    EXPECT_EQ(bitCount8(0b11000000), 2);
    EXPECT_EQ(bitCount8(0b10000000), 1);
    EXPECT_EQ(bitCount8(0b00000000), 0);
}



TEST(ASCII85, dataShift)
{
    std::vector<uint8_t> values{0b10000010, 0b10000010, 0b10000010, 0b10000010,
                                0b10000010, 0b10000010, 0b10000010, 0b10000010};

    uint64_t val = dataShift(values);

    uint64_t test_val = 0b00000000'10000011'00000110'00001100'00011000'00110000'01100000'11000001;

    EXPECT_EQ(val, test_val);
}