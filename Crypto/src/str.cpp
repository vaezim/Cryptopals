/**************************************************
 * @date    2024-11-29
 * @brief   String utilities
 **************************************************/

#include <sstream>
#include "str.h"
#include "bit.h"

namespace Crypto {
namespace Str {

std::string BytesToStr(const Bytes &bytes)
{
    return std::string(bytes.begin(), bytes.end());
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

double GetTextScore(const std::string &str)
{
    double count{ 0 };
    for (const auto &c : str) {
        if (!std::isprint(c) && c != '\n') {
            return 0.0;
        }
        if (std::isalnum(c)) {
            count += 1.0;
        }
    }
    return count / static_cast<double>(str.size());
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

} // namespace Str
} // namespace Crypto