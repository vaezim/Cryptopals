#include <fstream>
#include <sstream>
#include "crypto.h"

/**************************************************
 * Challenge 6
 * https://cryptopals.com/sets/1/challenges/6
 **************************************************/

int main()
{
    // Check Hamming Distance
    const std::string text1{ "this is a test" };
    const std::string text2{ "wokka wokka!!!" };
    constexpr size_t expectedHammingDistance{ 37 };
    size_t hammingDistance = Crypto::Bit::GetHammingDistance(
        Crypto::Str::StrToBytes(text1), Crypto::Str::StrToBytes(text2));
    if (hammingDistance == expectedHammingDistance) {
        INFO_LOG("Hamming Distance is correct.");
    } else {
        RED_INFO_LOG("Hamming Distance is incorrect!");
        return 1;
    }

    // Read the cipher text
    std::string filename{ "text/6.txt" };
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        ERROR_LOG("Failed to open " << filename);
        return 1;
    }
    std::string line;
    std::stringstream ss;
    while (std::getline(ifs, line)) {
        ss << line;
    }
    std::string cipherText = ss.str();
    const auto &cipherBytes = Crypto::Base::Base64StrToBytes(cipherText);

    // Break the cipher
    Crypto::Xor::XORBreaker xorBreaker(cipherBytes);
    const auto &key = xorBreaker.GetEncryptionKey();
    const auto &plainBytes = Crypto::Xor::XORBytesWithBytes(cipherBytes, key);
    const auto &plainText = Crypto::Str::BytesToStr(plainBytes);

    // Output file
    const std::string outputFile{ "./text/6.out" };
    std::ofstream ofs(outputFile);
    ofs << plainText << "\n";
    ofs.close();
    INFO_LOG("Possible plain-text message dumped to " << outputFile);

    return 0;
}