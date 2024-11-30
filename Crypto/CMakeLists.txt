
# Add source files
file(
    GLOB CRYPTO_SRC
    "./src/*.cpp"
)

# Crypto static library (../output/lib/libcrypto.a)
add_library(${CRYPTO_LIB} ${CRYPTO_SRC})