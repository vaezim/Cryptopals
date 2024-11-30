/**************************************************
 * @date    2024-11-24
 * @brief   Conversion between numerical bases
 **************************************************/

#pragma once
#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>

namespace Crypto {
namespace Base {

// Base 16
uint8_t HexToDecimal(const char &c);
char DecimalToHex(const uint8_t &d);
std::vector<uint8_t> HexStrToBytes(const std::string &str);
std::string BytesToHexStr(const std::vector<uint8_t> &bytes);

// Base 64
uint8_t Base64ToDecimal(const char &c);
char DecimalToBase64(const uint8_t &d);
std::vector<uint8_t> Base64StrToBytes(const std::string &str);
std::string BytesToBase64Str(const std::vector<uint8_t> &bytes);

} // namespace Base
} // namespace Crypto

#endif // BASE_H