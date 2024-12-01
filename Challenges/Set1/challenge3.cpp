#include "crypto.h"

int main()
{
    // Cipher Text
    const std::string cipherHex{
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
    };
    const auto &cipherBytes = Crypto::Base::HexStrToBytes(cipherHex);

    // XOR decryptor
    Crypto::Xor::XORDecryptor decryptor(cipherBytes);

    // Possible keys: [0, UINT8_MAX]
    std::vector<Crypto::Bytes> keys(UINT8_MAX+1);
    for (int key{ 0 }; key <= UINT8_MAX; key++) {
        keys[key] = { static_cast<uint8_t>(key) };
    }
    decryptor.AddKeys(std::move(keys));

    // Generate all possible plain-text messages with brute force
    decryptor.BruteForce();

    // Print messages until queue is empty
    // Correct Answer: Cooking MC's like a pound of bacon (Key = 'X')
    while (!decryptor.Empty()) {
        const auto &plainTextMessage = decryptor.Top();
        std::cout << "Possible plain-text message:\n"
            << "\tKey: " << plainTextMessage.key << "\n"
            << "\tMessage: " << plainTextMessage.message << std::endl;
        std::getchar();
    }

    return 0;
}