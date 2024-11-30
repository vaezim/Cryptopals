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

// XOR Bytes
Bytes XORBytes(const Bytes &bytes1, const Bytes &bytes2); 

// Strings
bool CompareString(const std::string &s1, const std::string &s2);

} // namespace Utils
} // namespace Crypto

#endif // UTILS_H