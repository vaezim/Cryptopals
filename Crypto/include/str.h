/**************************************************
 * @date    2024-11-29
 * @brief   String utilities
 **************************************************/

#pragma once
#ifndef STR_H
#define STR_H

#include "defs.h"

namespace Crypto {
namespace Str {

// Bytes to string
std::string BytesToStr(const Bytes &bytes);

// String to bytes
Bytes StrToBytes(const std::string &string);

// Get percentage of alpha-numeric characters
double GetTextScore(const std::string &str);

// Get character usage% in a string
double GetCharFrqeuencyInStr(const std::string &str, char c);

// Strings
bool CompareString(const std::string &s1, const std::string &s2);

} // namespace Str
} // namespace Crypto

#endif // STR_H