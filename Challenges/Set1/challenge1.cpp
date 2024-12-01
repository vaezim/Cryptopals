#include "crypto.h"


int main()
{
    // Hex string
    const std::string hexStr{
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    };

    // Expected Base64 string
    const std::string expectedBase64Str{
        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
    };

    // Convert Hex string to bytes
    const Crypto::Bytes &bytes = Crypto::Base::HexStrToBytes(hexStr);

    // Convert bytes to Base64 string
    const std::string &base64Str = Crypto::Base::BytesToBase64Str(bytes);

    // Validate answer
    std::cout << "Base64 string by Crypto lib:\n\t" << base64Str << std::endl;
    std::cout << "Expected Base64 string:\n\t" << expectedBase64Str << std::endl;
    if (Crypto::Utils::CompareString(expectedBase64Str, base64Str)) {
        INFO_LOG("Answer is correct.");
    } else {
        RED_INFO_LOG("Answer is incorrect!");
    }

    return 0;
}