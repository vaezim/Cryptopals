/**************************************************
 * @date    2024-11-24
 * @brief   Conversion between numerical bases
 **************************************************/

#include <bitset>
#include <sstream>
#include "base.h"
#include "defs.h"

namespace Crypto {
namespace Base {

uint8_t HexToDecimal(const char &c)
{
    const auto &_map = GetHexToDecimalMap();
    auto itr = _map.find(c);
    if (UNLIKELY(itr == _map.end())) {
        ERROR_LOG("Character " << c << " is not a base 16 (hex) symbol.");
        return INVALID_DECIMAL_DIGIT;
    }
    return itr->second;
}

char DecimalToHex(const uint8_t &d)
{
    if (UNLIKELY(d > MAX_HEX_DIGIT)) {
        ERROR_LOG("Decimal number " << d << " cannot be larger than " << MAX_HEX_DIGIT);
        return INVALID_HEX_DIGIT;
    }
    const auto &_map = GetDecimalToHexMap();
    return _map.find(d)->second;
}

std::vector<uint8_t> HexStrToBytes(const std::string &str)
{
    // Str size must be a multiple of 2
    if (UNLIKELY(str.size() % 2 != 0)) {
        ERROR_LOG("Hex str size must be a multiple of 2.");
        return {};
    }
    // Output
    std::vector<uint8_t> bytes(str.size()/2);
    // Hex to Decimal mapping
    for (size_t i{ 0 }; i < bytes.size(); i++) {
        const char &c1 = std::tolower(str[2*i]);
        const char &c2 = std::tolower(str[2*i+1]);
        uint8_t b1 = HexToDecimal(c1);
        uint8_t b2 = HexToDecimal(c2);
        if (UNLIKELY(b1 == INVALID_DECIMAL_DIGIT || b2 == INVALID_DECIMAL_DIGIT)) {
            ERROR_LOG("HexStrToBytes() reached an invalid hex char. Exiting...");
            return {};
        }
        uint8_t byte = (b1 << 4) + b2;
        bytes[i] = byte;
    }
    return bytes;
}

std::string BytesToHexStr(const std::vector<uint8_t> &bytes)
{
    std::stringstream ss;
    for (const auto &byte : bytes) {
        uint8_t b1 = byte >> 4;
        uint8_t b2 = byte & 0b1111;
        char c1 = DecimalToHex(b1);
        char c2 = DecimalToHex(b2);
        ss << c1 << c2;
    }
    return ss.str();
}

uint8_t Base64ToDecimal(const char &c)
{
    const auto &_map = GetBase64ToDecimalMap();
    auto itr = _map.find(c);
    if (UNLIKELY(itr == _map.end())) {
        ERROR_LOG("Character " << c << " is not a Base64 symbol.");
        return INVALID_DECIMAL_DIGIT;
    }
    return itr->second;
}

char DecimalToBase64(const uint8_t &d)
{
    if (UNLIKELY(d > MAX_BASE64_DIGIT)) {
        ERROR_LOG("Decimal number " << d << " cannot be larger than " << MAX_BASE64_DIGIT);
        return INVALID_BASE64_DIGIT;
    }
    const auto &_map = GetDecimalToBase64Map();
    return _map.find(d)->second;
}

std::vector<uint8_t> Base64StrToBytes(const std::string &str)
{
    // Output
    size_t str_size = str.size();
    std::vector<uint8_t> bytes(str_size/4 * 3);
    // Parse base64 digits in chunks of 4
    for (size_t i{ 0 }; i < str_size/4; i++) {
        uint8_t d1 = Base64ToDecimal(str[4*i]);
        uint8_t d2 = Base64ToDecimal(str[4*i+1]);
        uint8_t d3= Base64ToDecimal(str[4*i+2]);
        uint8_t d4 = Base64ToDecimal(str[4*i+3]);
        if (UNLIKELY((d1 | d2 | d3 | d4) == INVALID_DECIMAL_DIGIT)) {
            ERROR_LOG("Base64StrToBytes() reached an invalid Base64 symbol. Exiting...");
            return {};
        }
        bytes[3*i] = (d1 << 2) + (d2 >> 4);
        bytes[3*i+1] = ((d2 & 0b1111) << 4) + (d3 >> 2);
        bytes[3*i+2] = ((d3 & 0b11) << 6) + d4;
    }
    // Parse the remaining 0-3 symbols
    size_t remaining = str_size - str_size/4*4;
    if (remaining == 1) {
        uint8_t d1 = Base64ToDecimal(str[str_size-1]);
        bytes.push_back(d1 << 2);
    } else if (remaining == 2) {
        uint8_t d1 = Base64ToDecimal(str[str_size-2]);
        uint8_t d2 = Base64ToDecimal(str[str_size-1]);
        bytes.push_back((d1 << 2) + (d2 >> 4));
        bytes.push_back((d2 & 0b1111) << 4);
    } else if (remaining == 3) {
        uint8_t d1 = Base64ToDecimal(str[str_size-3]);
        uint8_t d2 = Base64ToDecimal(str[str_size-2]);
        uint8_t d3 = Base64ToDecimal(str[str_size-1]);
        bytes.push_back((d1 << 2) + (d2 >> 4));
        bytes.push_back(((d2 & 0b1111) << 4) + (d3 >> 2));
        bytes.push_back((d3 & 0b11) << 6);
    }
    return bytes;
}

std::string BytesToBase64Str(const std::vector<uint8_t> &bytes)
{
    std::stringstream ss;
    size_t bytes_size = bytes.size();
    for (size_t i{ 0 }; i < bytes_size/3; i++) {
        const uint8_t &b1 = bytes[3*i];
        const uint8_t &b2 = bytes[3*i+1];
        const uint8_t &b3 = bytes[3*i+2];
        char c1 = DecimalToBase64(b1 >> 2);
        char c2 = DecimalToBase64(((b1 & 0b11) << 4) + (b2 >> 4));
        char c3 = DecimalToBase64(((b2 & 0b1111) << 2) + (b3 >> 6));
        char c4 = DecimalToBase64(b3 & 0b111111);
        ss << c1 << c2 << c3 << c4;
    }
    size_t remaining = bytes_size - bytes_size/3*3;
    if (remaining == 1) {
        const uint8_t &b1 = bytes[bytes_size-1];
        char c1 = DecimalToBase64(b1 >> 2);
        char c2 = DecimalToBase64((b1 & 0b11) << 4);
        ss << c1 << c2 << "==";
    } else if (remaining == 2) {
        const uint8_t &b1 = bytes[bytes_size-2];
        const uint8_t &b2 = bytes[bytes_size-1];
        char c1 = DecimalToBase64(b1 >> 2);
        char c2 = DecimalToBase64(((b1 & 0b11) << 4) + (b2 >> 4));
        char c3 = DecimalToBase64((b2 & 0b1111) << 2);
        ss << c1 << c2 << c3 << "=";
    }
    return ss.str();
}

} // namespace Base
} // namespace Crypto