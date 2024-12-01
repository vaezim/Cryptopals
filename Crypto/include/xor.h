/**************************************************
 * @date    2024-11-30
 * @brief   XOR utilities
 **************************************************/

#pragma once
#ifndef XOR_H
#define XOR_H

#include <queue>
#include "defs.h"

namespace Crypto {
namespace Xor {

// XOR Bytes
Bytes XORBytesWithBytes(const Bytes &bytes, const Bytes &key);

// Decryptor for XOR-encrypted messages
class XORDecryptor {
public:
    XORDecryptor(const Bytes &cipherBytes) : m_cipherBytes(cipherBytes) {}
    ~XORDecryptor() = default;

    // Add the list of possible keys
    void AddKeys(std::vector<Bytes> &&keys);

    // Decrypt the cipher-text with all of the keys
    void BruteForce();

    // Get the message with the highest score
    // and remove it from the priority queue
    TextScore_t Top();

    // Priority queue size
    bool Empty();

private:
    std::vector<Bytes> m_keys;
    const Bytes &m_cipherBytes;
    std::priority_queue<TextScore_t, std::vector<TextScore_t>, TextFreqComparator> m_msgPQ;
};

} // namespace Xor
} // namespace Crypto

#endif // XOR_H