/**************************************************
 * @date    2024-11-29
 * @brief   Crypto utility functions
 **************************************************/

#include <sstream>
#include "utils.h"

namespace Crypto {
namespace Utils {

std::string BytesToStr(const Bytes &bytes)
{
    std::stringstream ss;
    for (const auto &byte : bytes) {
        ss << byte;
    }
    return ss.str();
}

Bytes StrToBytes(const std::string &str)
{
    Bytes output(str.size());
    for (size_t i{ 0 }; i < str.size(); i++) {
        output[i] = static_cast<uint8_t>(str[i]);
    }
    return output;
}

//--------------------------------------------------
// Returns #c / str.size()
//--------------------------------------------------
double GetCharFrqeuencyInStr(const std::string &str, char c)
{
    size_t count{ 0 };
    for (const auto &_c : str) {
        if (_c == c) count++;
    }
    return static_cast<double>(count) / static_cast<double>(str.size());
}

double GetAlNumPercentageInStr(const std::string &str)
{
    size_t count{ 0 };
    for (const auto &c : str) {
        if (std::isalnum(c)) {
            count++;
        } else if (count > 0) {
            count--;
        }
    }
    return static_cast<double>(count) / static_cast<double>(str.size());
}

//--------------------------------------------------
// true: strings match
// false: strings do not match
//--------------------------------------------------
bool CompareString(const std::string &s1, const std::string &s2)
{
    if (s1.size() != s2.size()) {
        return false;
    }
    for (size_t i{ 0 }; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

} // namespace Utils
} // namespace Crypto