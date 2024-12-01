/**************************************************
 * @date    2024-11-29
 * @brief   Crypto utility functions
 **************************************************/

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "defs.h"

namespace Crypto {
namespace Utils {

// Bytes to string
std::string BytesToStr(const Bytes &bytes);

// String to bytes
Bytes StrToBytes(const std::string &string);

// Get character usage% in a string
double GetCharFrqeuencyInStr(const std::string &str, char c);

// Get percentage of alpha-numeric characters
double GetAlNumPercentageInStr(const std::string &str);

// Strings
bool CompareString(const std::string &s1, const std::string &s2);

} // namespace Utils
} // namespace Crypto

#endif // UTILS_H