/**************************************************
 * @date    2024-11-24
 * @brief   Macro and global variable definitions
 **************************************************/

#pragma once
#ifndef CRYPTO_DEFS_H
#define CRYPTO_DEFS_H

#include <cstdint>
#include <iostream>
#include <unordered_map>

namespace Crypto {

//--------------------------------------------------
// Macro definitions
//--------------------------------------------------
// Terminal colors
#define COLOR_RED       "\x1B[91m"
#define COLOR_GREEN     "\x1B[92m"
#define COLOR_YELLOW    "\x1B[93m"
#define COLOR_DEFAULT   "\x1B[0m"

// Logger macros
#define LOCATION __FILE__ << ":" << \
    __LINE__ << " (" << __FUNCTION__ << ")\n"

#define ERROR_LOG(msg)                                          \
    do {                                                        \
        std::cout << LOCATION << COLOR_RED                      \
        "[-] Error: " << msg << COLOR_DEFAULT << std::endl;     \
    } while(0)

#define WARNING_LOG(msg)                                        \
    do {                                                        \
        std::cout << LOCATION << COLOR_YELLOW                   \
        "[*] Warning: " << msg << COLOR_DEFAULT << std::endl;   \
    } while(0)

#define INFO_LOG(msg)                                           \
    do {                                                        \
        std::cout << COLOR_GREEN                                \
        "[+] " << msg << COLOR_DEFAULT << std::endl;            \
    } while(0)

#define RED_INFO_LOG(msg)                                       \
    do {                                                        \
        std::cout << COLOR_RED                                  \
        "[-] " << msg << COLOR_DEFAULT << std::endl;            \
    } while(0)

// Branch prediction
#define LIKELY(x) __builtin_expect (x, 1)
#define UNLIKELY(x) __builtin_expect (x, 0)


//--------------------------------------------------
// constexpr & static consts
//--------------------------------------------------
// Base maximums
constexpr uint8_t MAX_HEX_DIGIT = 0xF;
constexpr uint8_t MAX_BASE64_DIGIT = 0b111111;

// Invalid digits
constexpr uint8_t INVALID_HEX_DIGIT = UINT8_MAX;
constexpr uint8_t INVALID_BASE64_DIGIT = UINT8_MAX;
constexpr uint8_t INVALID_DECIMAL_DIGIT = UINT8_MAX;


//--------------------------------------------------
// Enums
//--------------------------------------------------
enum ErrorCode : uint8_t {
    SUCCESS,
};


//--------------------------------------------------
// Maps
//--------------------------------------------------
const std::unordered_map<char, uint8_t> &GetHexToDecimalMap();
const std::unordered_map<uint8_t, char> &GetDecimalToHexMap();
const std::unordered_map<char, uint8_t> &GetBase64ToDecimalMap();
const std::unordered_map<uint8_t, char> &GetDecimalToBase64Map();

} // namespace Crypto

#endif // CRYPTO_DEFS_H