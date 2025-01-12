/**************************************************
 * @date    2024-11-30
 * @brief   XOR utilities
 **************************************************/

#pragma once
#ifndef XOR_H
#define XOR_H

#include <set>
#include <queue>
#include "defs.h"

namespace Crypto {
namespace Xor {

// XOR Bytes
Bytes XORBytesWithBytes(const Bytes &bytes, const Bytes &key);

//--------------------------------------------------
// BruteForce XOR-encrypted messages
//--------------------------------------------------
class XORBruteForce {
public:
    XORBruteForce(const Bytes &cipherBytes) : m_cipherBytes(cipherBytes) {}
    ~XORBruteForce() = default;

    // Add the list of possible keys
    void AddKeys(const std::vector<Bytes> &keys);

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

//--------------------------------------------------
// Break XOR-encrypted messages (Vigenere)
//--------------------------------------------------
class XORBreaker {
public:
    XORBreaker(const Bytes &cipherBytes) : m_cipherBytes(cipherBytes) {}
    ~XORBreaker() = default;

    // Find encryption key by brute-forcing each byte of the key
    Bytes GetEncryptionKey() const;

private:
    const Bytes &m_cipherBytes;

    // Find edit distances of blocks of <Keysize> bytes
    // and return the keysize with smallest edit distance
    size_t GetKeysizeWithSmallestEditDistance(size_t min, size_t max) const;

    // Transpose the blocks of size <keysize>
    // Output will have <keysize> number of <Bytes> blocks
    std::vector<Bytes> GetTransposedBlocks() const;
};

} // namespace Xor
} // namespace Crypto

#endif // XOR_H