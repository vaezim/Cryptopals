/**************************************************
 * @date    2025-01-10
 * @brief   Bitwise utilities
 **************************************************/

#pragma once
#ifndef BIT_H
#define BIT_H

#include "defs.h"

namespace Crypto {
namespace Bit {

// Number of '1's in a byte
size_t GetNumSetBitsInByte(uint8_t byte);

// Hamming distance between two bytes
size_t GetHammingDistance(const uint8_t &byte1, const uint8_t &byte2);

// Hamming distance between two array of bytes
size_t GetHammingDistance(const Bytes &bytes1, const Bytes &bytes2);

} // namespace Bit
} // namespace Crypto

#endif // BIT_H