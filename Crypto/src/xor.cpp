/**************************************************
 * @date    2024-11-29
 * @brief   XOR utilities
 **************************************************/

#include "xor.h"
#include "utils.h"

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

void XORDecryptor::AddKeys(std::vector<Bytes> &&keys)
{
    m_keys = keys;
}

//--------------------------------------------------
// Score decrypted messaged according to a scoring metric
//--------------------------------------------------
void XORDecryptor::BruteForce()
{
    for (const auto &key : m_keys) {
        const auto &msgBytes = XORBytesWithBytes(m_cipherBytes, key);
        TextScore_t textFreq;
        textFreq.message = Utils::BytesToStr(msgBytes);
        textFreq.key = Utils::BytesToStr(key);
        textFreq.score = Utils::GetAlNumPercentageInStr(textFreq.message);
        m_msgPQ.emplace(textFreq);
    }
}

TextScore_t XORDecryptor::Top()
{
    if (UNLIKELY(m_msgPQ.empty())) {
        return {};
    }
    auto &topMsg = m_msgPQ.top();
    m_msgPQ.pop();
    return topMsg;
}

bool XORDecryptor::Empty()
{
    return m_msgPQ.empty();
}

} // namespace Xor
} // namespace Crypto