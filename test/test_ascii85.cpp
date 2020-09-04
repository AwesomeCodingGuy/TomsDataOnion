#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "../src/ascii85.h"

// Encoding / Decoding
std::string complex_payload_1 = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
std::string complex_payload_1_encoded = R"delim(<~9jqo^BlbD-BleB1DJ+*+F(f,q/0JhKF<GL>Cj@.4Gp$d7F!,L7@<6@)/0JDEF<G%<+EV:2F!,O<DJ+*.@<*K0@<6L(Df-\0Ec5e;DffZ(EZee.Bl.9pF"AGXBPCsi+DGm>@3BB/F*&OCAfu2/AKYi(DIb:@FD,*)+C]U=@3BN#EcYf8ATD3s@q?d$AftVqCh[NqF<G:8+EV:.+Cf>-FD5W8ARlolDIal(DId<j@<?3r@:F%a+D58'ATD4$Bl@l3De:,-DJs`8ARoFb/0JMK@qB4^F!,R<AKZ&-DfTqBG%G>uD.RTpAKYo'+CT/5+Cei#DII?(E,9)oF*2M7/c~>)delim";

std::string test_string_padded_0 = "abcdefgh";
std::string test_string_padded_1 = "abcdefghi";
std::string test_string_padded_2 = "abcdefghij";
std::string test_string_padded_3 = "abcdefghijk";

std::string test_string_padded_0_encoded = "<~@:E_WAS,Rg~>";
std::string test_string_padded_1_encoded = "<~@:E_WAS,RgB`~>";
std::string test_string_padded_2_encoded = "<~@:E_WAS,RgBkd~>";
std::string test_string_padded_3_encoded = "<~@:E_WAS,RgBkhD~>";

// Preprocessing
std::string test_string = "abcdefghijkl";
std::string test_string_whitespace_1 = "abcdef ghijkl";
std::string test_string_whitespace_2 = "abcdef\fghijkl";
std::string test_string_whitespace_3 = "abcdef\nghijkl";
std::string test_string_whitespace_4 = "abcdef\rghijkl";
std::string test_string_whitespace_5 = "abcdef\tghijkl";
std::string test_string_whitespace_6 = "abcdef\vghijkl";
std::string test_string_whitespace_mixed = "a b c d e f g\v\r\n h i j k l \t    \n";
std::string test_string_delimiter = "<~abcdefghijkl~>";
std::string test_string_delimiter_front = "<~abcdefghijkl";
std::string test_string_delimiter_back = "abcdefghijkl~>";
std::string test_string_delimiter_whitespace = "<~ab cd \nefg \r    hijk \vl~>";


TEST(ASCII85, ascii85_preprocessInput)
{
    auto emptyVector = preprocessInput(std::vector<uint8_t>());
    ASSERT_EQ(emptyVector.size(), 0);

    auto test_vector_whitespace_1 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_1.begin(),
                                                                         test_string_whitespace_1.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_1.begin(),
                                                  test_vector_whitespace_1.end()).c_str());

    auto test_vector_whitespace_2 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_2.begin(),
                                                                         test_string_whitespace_2.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_2.begin(),
                                                  test_vector_whitespace_2.end()).c_str());

    auto test_vector_whitespace_3 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_3.begin(),
                                                                         test_string_whitespace_3.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_3.begin(),
                                                  test_vector_whitespace_3.end()).c_str());

    auto test_vector_whitespace_4 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_4.begin(),
                                                                         test_string_whitespace_4.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_4.begin(),
                                                  test_vector_whitespace_4.end()).c_str());

    auto test_vector_whitespace_5 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_5.begin(),
                                                                         test_string_whitespace_5.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_5.begin(),
                                                  test_vector_whitespace_5.end()).c_str());

    auto test_vector_whitespace_6 = preprocessInput(std::vector<uint8_t>(test_string_whitespace_6.begin(),
                                                                         test_string_whitespace_6.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_6.begin(),
                                                  test_vector_whitespace_6.end()).c_str());

    auto test_vector_whitespace_mixed = preprocessInput(std::vector<uint8_t>(test_string_whitespace_mixed.begin(),
                                                                         test_string_whitespace_mixed.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_whitespace_mixed.begin(),
                                                  test_vector_whitespace_mixed.end()).c_str());

    auto test_vector_delimiter = preprocessInput(std::vector<uint8_t>(test_string_delimiter.begin(),
                                                                      test_string_delimiter.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_delimiter.begin(),
                                                  test_vector_delimiter.end()).c_str());

    auto test_vector_delimiter_front = preprocessInput(std::vector<uint8_t>(test_string_delimiter_front.begin(),
                                                                            test_string_delimiter_front.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_delimiter_front.begin(),
                                                  test_vector_delimiter_front.end()).c_str());

    auto test_vector_delimiter_back = preprocessInput(std::vector<uint8_t>(test_string_delimiter_back.begin(),
                                                                           test_string_delimiter_back.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_delimiter_back.begin(),
                                                  test_vector_delimiter_back.end()).c_str());

    auto test_vector_delimiter_whitespace = preprocessInput(std::vector<uint8_t>(test_string_delimiter_whitespace.begin(),
                                                                                 test_string_delimiter_whitespace.end()));
    ASSERT_STREQ(test_string.c_str(), std::string(test_vector_delimiter_whitespace.begin(),
                                                  test_vector_delimiter_whitespace.end()).c_str());
}

TEST(ASCII85, ascii85_encode_zero_length)
{
    auto encodedPayload = ascii85_encode(std::vector<uint8_t>());
    ASSERT_EQ(encodedPayload.size(), 0);
}

TEST(ASCII85, ascii85_encode_padding_0)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_0.begin(), test_string_padded_0.end());
    ASSERT_EQ(payload.size(), test_string_padded_0.length());

    // encode the vector
    auto encodedPayload = ascii85_encode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(encodedPayload.size(), test_string_padded_0_encoded.length());

    // convert the vector to string and compare both strings
    std::string encodedString(encodedPayload.begin(), encodedPayload.end());
    ASSERT_STREQ(encodedString.c_str(), test_string_padded_0_encoded.c_str());
}

TEST(ASCII85, ascii85_encode_padding_1)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_1.begin(), test_string_padded_1.end());
    ASSERT_EQ(payload.size(), test_string_padded_1.length());

    // encode the vector
    auto encodedPayload = ascii85_encode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(encodedPayload.size(), test_string_padded_1_encoded.length());

    // convert the vector to string and compare both strings
    std::string encodedString(encodedPayload.begin(), encodedPayload.end());
    ASSERT_STREQ(encodedString.c_str(), test_string_padded_1_encoded.c_str());
}

TEST(ASCII85, ascii85_encode_padding_2)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_2.begin(), test_string_padded_2.end());
    ASSERT_EQ(payload.size(), test_string_padded_2.length());

    // encode the vector
    auto encodedPayload = ascii85_encode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(encodedPayload.size(), test_string_padded_2_encoded.length());

    // convert the vector to string and compare both strings
    std::string encodedString(encodedPayload.begin(), encodedPayload.end());
    ASSERT_STREQ(encodedString.c_str(), test_string_padded_2_encoded.c_str());
}

TEST(ASCII85, ascii85_encode_padding_3)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_3.begin(), test_string_padded_3.end());
    ASSERT_EQ(payload.size(), test_string_padded_3.length());

    // encode the vector
    auto encodedPayload = ascii85_encode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(encodedPayload.size(), test_string_padded_3_encoded.length());

    // convert the vector to string and compare both strings
    std::string encodedString(encodedPayload.begin(), encodedPayload.end());
    ASSERT_STREQ(encodedString.c_str(), test_string_padded_3_encoded.c_str());
}

TEST(ASCII85, ascii85_encode_complex)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(complex_payload_1.begin(), complex_payload_1.end());
    ASSERT_EQ(payload.size(), complex_payload_1.length());

    // encode the vector
    auto encodedPayload = ascii85_encode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(encodedPayload.size(), complex_payload_1_encoded.length());

    // convert the vector to string and compare both strings
    std::string encodedString(encodedPayload.begin(), encodedPayload.end());
    ASSERT_STREQ(encodedString.c_str(), complex_payload_1_encoded.c_str());
}

TEST(ASCII85, ascii85_decode_zero_length) 
{
    auto decodedPayload = ascii85_decode(std::vector<uint8_t>());
    ASSERT_EQ(decodedPayload.size(), 0);
}

TEST(ASCII85, ascii85_decode_padding_0)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_0_encoded.begin(),
                                 test_string_padded_0_encoded.end());
    ASSERT_EQ(payload.size(), test_string_padded_0_encoded.length());

    // decode the vector
    auto decodedPayload = ascii85_decode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(decodedPayload.size(), test_string_padded_0.length());

    // convert the vector to string and compare both strings
    std::string decodedString(decodedPayload.begin(), decodedPayload.end());
    ASSERT_STREQ(decodedString.c_str(), test_string_padded_0.c_str());
}

TEST(ASCII85, ascii85_decode_padding_1)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_1_encoded.begin(),
                                 test_string_padded_1_encoded.end());
    ASSERT_EQ(payload.size(), test_string_padded_1_encoded.length());

    // decode the vector
    auto decodedPayload = ascii85_decode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(decodedPayload.size(), test_string_padded_1.length());

    // convert the vector to string and compare both strings
    std::string decodedString(decodedPayload.begin(), decodedPayload.end());
    ASSERT_STREQ(decodedString.c_str(), test_string_padded_1.c_str());
}

TEST(ASCII85, ascii85_decode_padding_2)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_2_encoded.begin(),
                                 test_string_padded_2_encoded.end());
    ASSERT_EQ(payload.size(), test_string_padded_2_encoded.length());

    // decode the vector
    auto decodedPayload = ascii85_decode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(decodedPayload.size(), test_string_padded_2.length());

    // convert the vector to string and compare both strings
    std::string decodedString(decodedPayload.begin(), decodedPayload.end());
    ASSERT_STREQ(decodedString.c_str(), test_string_padded_2.c_str());
}

TEST(ASCII85, ascii85_decode_padding_3)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(test_string_padded_3_encoded.begin(),
                                 test_string_padded_3_encoded.end());
    ASSERT_EQ(payload.size(), test_string_padded_3_encoded.length());

    // decode the vector
    auto decodedPayload = ascii85_decode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(decodedPayload.size(), test_string_padded_3.length());

    // convert the vector to string and compare both strings
    std::string decodedString(decodedPayload.begin(), decodedPayload.end());
    ASSERT_STREQ(decodedString.c_str(), test_string_padded_3.c_str());
}

TEST(ASCII85, ascii85_decode_complex)
{
    // load string to vector and compare their lengths
    std::vector<uint8_t> payload(complex_payload_1_encoded.begin(),
                                 complex_payload_1_encoded.end());
    ASSERT_EQ(payload.size(), complex_payload_1_encoded.length());

    // decode the vector
    auto decodedPayload = ascii85_decode(payload);

    // compare the encoded vector size with the test string length
    ASSERT_EQ(decodedPayload.size(), complex_payload_1.length());

    // convert the vector to string and compare both strings
    std::string decodedString(decodedPayload.begin(), decodedPayload.end());
    ASSERT_STREQ(decodedString.c_str(), complex_payload_1.c_str());
}