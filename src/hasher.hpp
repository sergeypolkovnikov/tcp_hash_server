#pragma once

#include <array>
#include <span>
#include <openssl/sha.h>

struct Hasher {
    using HashT = std::array<unsigned char, SHA256_DIGEST_LENGTH>;

    Hasher() {
        SHA256_Init(&ctx);
    }

    void add_chunk(std::span<const char> chunk) {
        SHA256_Update(&ctx, chunk.data(), chunk.size());
    }

    HashT finilize() {
        HashT res;
        SHA256_Final(res.data(), &ctx);
        SHA256_Init(&ctx);
        return res;
    }

private:
    SHA256_CTX ctx;
};

std::string hash_to_str(const Hasher::HashT& hash) {
    std::ostringstream oss;
    for (const auto sym : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(sym);
    }
    oss << "\n";
    return oss.str();
}