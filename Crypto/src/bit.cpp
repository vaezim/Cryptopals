/**************************************************
 * @date    2025-01-10
 * @brief   Bitwise utilities
 **************************************************/

#include "bit.h"

namespace Crypto {
namespace Bit {

size_t GetNumSetBitsInByte(uint8_t byte)
{
    size_t count{ 0 };
    while (byte != 0) {
        count += static_cast<size_t>((byte & 1) != 0);
        byte >>= 1;
    }
    return count;
}

size_t GetHammingDistance(const uint8_t &byte1, const uint8_t &byte2)
{
    return GetNumSetBitsInByte(byte1 ^ byte2);
}

//--------------------------------------------------
// Hamming distance between two strings:
// The number of differing bits between the two strings
//--------------------------------------------------
size_t GetHammingDistance(const Bytes &bytes1, const Bytes &bytes2)
{
    size_t distance{ 0 };
    size_t shorter = std::min(bytes1.size(), bytes2.size());
    size_t longer = std::max(bytes1.size(), bytes2.size());
    for (size_t i{ 0 }; i < shorter; i++) {
        distance += GetHammingDistance(bytes1[i], bytes2[i]);
    }
    if (bytes1.size() > bytes2.size()) {
        for (size_t i{ shorter }; i < longer; i++) {
            distance += GetHammingDistance(bytes1[i], 0);
        }
    } else if (bytes2.size() > bytes1.size()) {
        for (size_t i{ shorter }; i < longer; i++) {
            distance += GetHammingDistance(bytes2[i], 0);
        }
    }
    return distance;
}

} // namespace Bit
} // namespace Crypto