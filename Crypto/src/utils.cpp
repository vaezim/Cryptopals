/**************************************************
 * @date    2024-11-29
 * @brief   Crypto utility functions
 **************************************************/

#include "utils.h"

namespace Crypto {
namespace Utils {

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