/**************************************************
 * @date    2025-01-10
 * @brief   Array utilities
 **************************************************/

#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include "defs.h"

namespace Crypto {
namespace Array {

// Get subarray of length <size> starting from index <start>
template <typename T>
std::vector<T> GetSubArray(const std::vector<T> &array, size_t start, size_t size)
{
    if (UNLIKELY(start + size >= array.size())) {
        ERROR_LOG("End=" << start + size << " cannot be greater than array size=" << array.size());
        return {};
    }
    std::vector<T> subarray(size);
    for (size_t i{ start }; i < start+size; i++) {
        subarray[i-start] = array[i];
    }
    return subarray;
}

} // namespace Array
} // namespace Crypto

#endif // ARRAY_H