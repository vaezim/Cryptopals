/**************************************************
 * @date    2024-11-29
 * @brief   XOR utilities
 **************************************************/

#include <cstdint>
#include "xor.h"
#include "str.h"
#include "bit.h"
#include "array.h"

namespace Crypto {
namespace Xor {

Bytes XORBytesWithBytes(const Bytes &bytes, const Bytes &key)
{
    Bytes output(bytes.size());
    for (size_t i{ 0 }; i < bytes.size(); i++) {
        output[i] = bytes[i] ^ key[i % key.size()];
    }
    return output;
}

void XORBruteForce::AddKeys(const std::vector<Bytes> &keys)
{
    m_keys = keys;
}

//--------------------------------------------------
// Score decrypted messaged according to a scoring metric
//--------------------------------------------------
void XORBruteForce::BruteForce()
{
    for (const auto &key : m_keys) {
        const auto &msgBytes = XORBytesWithBytes(m_cipherBytes, key);
        TextScore_t textFreq;
        textFreq.message = Str::BytesToStr(msgBytes);
        textFreq.key = Str::BytesToStr(key);
        textFreq.score = Str::GetTextScore(textFreq.message);
        m_msgPQ.emplace(textFreq);
    }
}

TextScore_t XORBruteForce::Top()
{
    if (UNLIKELY(m_msgPQ.empty())) {
        return {};
    }
    auto topMsg = m_msgPQ.top();
    m_msgPQ.pop();
    return topMsg;
}

bool XORBruteForce::Empty()
{
    return m_msgPQ.empty();
}

size_t XORBreaker::GetKeysizeWithSmallestEditDistance(size_t min, size_t max) const
{
    size_t minKeySize{ min };
    double minEditDistance{ 1e9 };
    for (size_t keysize{ min }; keysize <= max; keysize++) {
        if (UNLIKELY(m_cipherBytes.size() < 4*keysize)) {
            break;
        }
        size_t h1 = Bit::GetHammingDistance(
            Array::GetSubArray(m_cipherBytes, 0, keysize),
            Array::GetSubArray(m_cipherBytes, keysize, keysize));
        size_t h2 = Bit::GetHammingDistance(
            Array::GetSubArray(m_cipherBytes, 2*keysize, keysize),
            Array::GetSubArray(m_cipherBytes, 3*keysize, keysize));
        double editDistance{ static_cast<double>(h1 + h2) / 2 / static_cast<double>(keysize) };
        if (editDistance < minEditDistance) {
            minEditDistance = editDistance;
            minKeySize = keysize;
        }
    }
    return minKeySize;
}

std::vector<Bytes> XORBreaker::GetTransposedBlocks() const
{
    size_t keysize = GetKeysizeWithSmallestEditDistance(6, 40);
    size_t numBlocks = m_cipherBytes.size() / keysize;
    std::vector<Bytes> output(keysize, Bytes(numBlocks));
    for (size_t i{ 0 }; i < numBlocks * keysize; i++) {
        output[i % keysize][i / keysize] = m_cipherBytes[i];
    }
    return output;
}

Bytes XORBreaker::GetEncryptionKey() const
{
    // Single byte XOR key: Bytes 0 to 255
    std::vector<Bytes> singleByteKeys;
    singleByteKeys.reserve(UINT8_MAX);
    for (uint8_t key{ 0 }; key < UINT8_MAX; key++) {
        singleByteKeys.push_back({ key });
    }

    // Find single-byte key for each block
    const std::vector<Bytes> &blocks = GetTransposedBlocks();
    Bytes key(blocks.size());
    for (size_t i{ 0 }; i < blocks.size(); i++) {
        XORBruteForce bruteforce(blocks[i]);
        bruteforce.AddKeys(singleByteKeys);
        bruteforce.BruteForce();
        key[i] = Str::StrToBytes(bruteforce.Top().key)[0];
    }

    return key;
}

} // namespace Xor
} // namespace Crypto