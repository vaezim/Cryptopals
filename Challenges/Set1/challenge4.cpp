#include <fstream>
#include "crypto.h"

/**************************************************
 * Challenge 4
 * https://cryptopals.com/sets/1/challenges/4
 **************************************************/

int main()
{
    // Possible keys: lower/upper case alphabets
    std::vector<Crypto::Bytes> keys;
    for (uint8_t key{ 0 }; key < UINT8_MAX; key++) {
        keys.push_back({ key });
    }

    // Open text file
    std::string filename{ "text/4.txt" };
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        ERROR_LOG("Failed to open " << filename);
        return 1;
    }

    // MessageScore priority_queue
    std::priority_queue<Crypto::TextScore_t,
        std::vector<Crypto::TextScore_t>,
        Crypto::TextFreqComparator> msgPQ;

    // Read line by line
    std::string cipherHex;
    while (std::getline(ifs, cipherHex)) {
        const auto &cipherBytes = Crypto::Base::HexStrToBytes(cipherHex);

        // XOR bruteForce
        Crypto::Xor::XORBruteForce bruteForce(cipherBytes);
        bruteForce.AddKeys(keys);

        // Generate all possible plain-text messages with brute force
        bruteForce.BruteForce();

        // Add plain-text messages to priority_queue
        while (!bruteForce.Empty()) {
            msgPQ.emplace(bruteForce.Top());
        }
    }

    // Output file
    const std::string outputFile{ "./text/4.out" };
    std::ofstream ofs(outputFile);

    // Get top score plain-text messages
    while (!msgPQ.empty()) {
        const auto &msg = msgPQ.top();
        if (msg.score > 0.0) { // Printables only
            ofs << msg.message << "\n";
        }
        msgPQ.pop();
    }
    ofs.close();
    INFO_LOG("Possible plain-text messages dumped to " << outputFile);

    return 0;
}