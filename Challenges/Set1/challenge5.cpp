#include "crypto.h"

/**************************************************
 * Challenge 5
 * https://cryptopals.com/sets/1/challenges/5
 **************************************************/

int main()
{
    // Plain-text message
    const std::string plainTextMessage{
        "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
    };

    // Cipher texts
    const std::string expectedCipherHexStr{
        "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
    };

    // Encryption key
    const std::string key{ "ICE" };

    // XOR encryption
    const Crypto::Bytes &cipherBytes =
        Crypto::Xor::XORBytesWithBytes(
            Crypto::Str::StrToBytes(plainTextMessage),
            Crypto::Str::StrToBytes(key));

    // Cipher text in hex
    const std::string &cipherHexStr = Crypto::Base::BytesToHexStr(cipherBytes);

    // Validate answer
    std::cout << "Plain text:\n\t" << plainTextMessage << std::endl;
    std::cout << "Cipher text (hex):\n\t" << cipherHexStr << std::endl;
    if (Crypto::Str::CompareString(expectedCipherHexStr, cipherHexStr)) {
        INFO_LOG("Answer is correct.");
    } else {
        RED_INFO_LOG("Answer is incorrect!");
    }

    return 0;
}