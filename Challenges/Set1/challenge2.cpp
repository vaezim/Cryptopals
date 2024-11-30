#include "crypto.h"

int main()
{
    // Hex strings
    const std::string hexStr1{
        "1c0111001f010100061a024b53535009181c"
    };
    const std::string hexStr2{
        "686974207468652062756c6c277320657965"
    };
    const std::string expectedHexStr{
        "746865206b696420646f6e277420706c6179"
    };

    // Hex decode
    const auto &bytes1 = Crypto::Base::HexStrToBytes(hexStr1);
    const auto &bytes2 = Crypto::Base::HexStrToBytes(hexStr2);

    // XOR bytes
    const auto &xorBytes = Crypto::Utils::XORBytes(bytes1, bytes2);

    // Hex encode
    const std::string &xorHexStr = Crypto::Base::BytesToHexStr(xorBytes);

    // Validate answer
    std::cout << "XOR hex string by Crypto lib:\n\t" << xorHexStr << std::endl;
    std::cout << "Expected XOR hex string:\n\t" << expectedHexStr << std::endl;
    if (Crypto::Utils::CompareString(expectedHexStr, xorHexStr)) {
        INFO_LOG("Answer is correct.");
    } else {
        RED_INFO_LOG("Answer is incorrect!");
    }

    return 0;
}