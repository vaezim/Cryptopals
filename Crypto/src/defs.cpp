/**************************************************
 * @date    2024-11-24
 * @brief   Macro and global variable definitions
 **************************************************/

#include "defs.h"

namespace Crypto {

bool TextFreqComparator::operator() (const TextScore_t &t1, const TextScore_t &t2)
{
    return t1.score < t2.score;
}

const std::unordered_map<char, uint8_t> &GetHexToDecimalMap()
{
    static const std::unordered_map<char, uint8_t> _map {
        { '0', 0 }, { '1', 1 }, { '2', 2 }, { '3', 3 },
        { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 },
        { '8', 8 }, { '9', 9 }, { 'a', 10}, { 'b', 11},
        { 'c', 12}, { 'd', 13}, { 'e', 14}, { 'f', 15}
    };
    return _map;
}

const std::unordered_map<uint8_t, char> &GetDecimalToHexMap()
{
    static const std::unordered_map<uint8_t, char> _map {
        { 0, '0' }, { 1, '1' }, { 2, '2' }, { 3, '3' },
        { 4, '4' }, { 5, '5' }, { 6, '6' }, { 7, '7' },
        { 8, '8' }, { 9, '9' }, {10, 'a' }, {11, 'b' },
        {12, 'c' }, {13, 'd' }, {14, 'e' }, {15, 'f' }
    };
    return _map;
}

const std::unordered_map<char, uint8_t> &GetBase64ToDecimalMap()
{
    static const std::unordered_map<char, uint8_t> _map {
        { 'A', 0 }, { 'Q', 16 }, { 'g', 32 }, { 'w', 48 },
        { 'B', 1 }, { 'R', 17 }, { 'h', 33 }, { 'x', 49 },
        { 'C', 2 }, { 'S', 18 }, { 'i', 34 }, { 'y', 50 },
        { 'D', 3 }, { 'T', 19 }, { 'j', 35 }, { 'z', 51 },
        { 'E', 4 }, { 'U', 20 }, { 'k', 36 }, { '0', 52 },
        { 'F', 5 }, { 'V', 21 }, { 'l', 37 }, { '1', 53 },
        { 'G', 6 }, { 'W', 22 }, { 'm', 38 }, { '2', 54 },
        { 'H', 7 }, { 'X', 23 }, { 'n', 39 }, { '3', 55 },
        { 'I', 8 }, { 'Y', 24 }, { 'o', 40 }, { '4', 56 },
        { 'J', 9 }, { 'Z', 25 }, { 'p', 41 }, { '5', 57 },
        { 'K', 10}, { 'a', 26 }, { 'q', 42 }, { '6', 58 },
        { 'L', 11}, { 'b', 27 }, { 'r', 43 }, { '7', 59 },
        { 'M', 12}, { 'c', 28 }, { 's', 44 }, { '8', 60 },
        { 'N', 13}, { 'd', 29 }, { 't', 45 }, { '9', 61 },
        { 'O', 14}, { 'e', 30 }, { 'u', 46 }, { '+', 62 },
        { 'P', 15}, { 'f', 31 }, { 'v', 47 }, { '/', 63 },
        { '=', 0 }
    };
    return _map;
}

const std::unordered_map<uint8_t, char> &GetDecimalToBase64Map()
{
    static const std::unordered_map<uint8_t, char> _map {
        { 0, 'A' }, { 16, 'Q' }, { 32, 'g' }, { 48, 'w' },
        { 1, 'B' }, { 17, 'R' }, { 33, 'h' }, { 49, 'x' },
        { 2, 'C' }, { 18, 'S' }, { 34, 'i' }, { 50, 'y' },
        { 3, 'D' }, { 19, 'T' }, { 35, 'j' }, { 51, 'z' },
        { 4, 'E' }, { 20, 'U' }, { 36, 'k' }, { 52, '0' },
        { 5, 'F' }, { 21, 'V' }, { 37, 'l' }, { 53, '1' },
        { 6, 'G' }, { 22, 'W' }, { 38, 'm' }, { 54, '2' },
        { 7, 'H' }, { 23, 'X' }, { 39, 'n' }, { 55, '3' },
        { 8, 'I' }, { 24, 'Y' }, { 40, 'o' }, { 56, '4' },
        { 9, 'J' }, { 25, 'Z' }, { 41, 'p' }, { 57, '5' },
        {10, 'K' }, { 26, 'a' }, { 42, 'q' }, { 58, '6' },
        {11, 'L' }, { 27, 'b' }, { 43, 'r' }, { 59, '7' },
        {12, 'M' }, { 28, 'c' }, { 44, 's' }, { 60, '8' },
        {13, 'N' }, { 29, 'd' }, { 45, 't' }, { 61, '9' },
        {14, 'O' }, { 30, 'e' }, { 46, 'u' }, { 62, '+' },
        {15, 'P' }, { 31, 'f' }, { 47, 'v' }, { 63, '/' },
    };
    return _map;
}

const std::unordered_map<char, double> &GetCommonAlphabetsScoreMap()
{
    static const std::unordered_map<char, double> _map {
        { ' ', 18.0 }, { 'e', 12.7 }, { 't', 9.06 }, { 'a', 8.17 },
        { 'o', 7.51 }, { 'i', 6.97 }, { 'n', 6.75 }, { 's', 6.33 },
        { 'h', 6.09 }, { 'r', 5.99 }, { 'd', 4.25 }, { 'l', 4.03 }, { 'u', 2.76 }
    };
    return _map;
}

} // namespace Crypto