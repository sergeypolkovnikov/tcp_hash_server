#pragma once

#include <array>
#include <span>
#include <openssl/sha.h>
#include <iomanip>

struct Hasher {
    using HashT = std::array<unsigned char, SHA256_DIGEST_LENGTH>;

    Hasher();
    void add_chunk(std::span<const char> chunk);
    HashT finilize();

private:
    SHA256_CTX ctx;
};

std::string hash_to_str(const Hasher::HashT& hash);