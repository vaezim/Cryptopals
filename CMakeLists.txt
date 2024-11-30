cmake_minimum_required(VERSION 3.0)
project(cryptopals)

# Executables at ./output/exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/exe)

# Libraries at ./output/lib
set(CRYPTO_LIB crypto)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# GCC flags
set(CMAKE_CXX_FLAGS 
    "-Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic"
)

# Include directories
include_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/Crypto/include
)

# Link directories
link_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/output/lib
)

# Crypto library
add_subdirectory(Crypto)

# Challenges
add_subdirectory(Challenges)