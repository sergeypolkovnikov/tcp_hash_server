#include <gtest/gtest.h>
#include "hasher.hpp"
#include <string_view>

TEST(HasherTest, EmptyInput) {
    Hasher h;
    auto hash = h.finilize();
    EXPECT_EQ(hash_to_str(hash),
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n");
}

TEST(HasherTest, SingleChunk) {
    Hasher h;
    std::string data = "hello";
    h.add_chunk(std::span(data.begin(), data.end()));
    auto hash = h.finilize();
    EXPECT_EQ(hash_to_str(hash),
        "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824\n");
}

TEST(HasherTest, MultipleChunks) {
    const std::string_view data = "hello";
    const auto mid_it = data.begin() + 2;
    Hasher h;
    h.add_chunk(std::span{ data.begin(), mid_it });
    h.add_chunk(std::span{ mid_it, data.end() });
    const auto hash = h.finilize();
    h.add_chunk(std::span{ data.begin(), data.end() });
    const auto expected_hash = h.finilize();
    EXPECT_EQ(expected_hash, hash);
}

TEST(HasherTest, ReuseHasher) {
    Hasher h;
    const std::string_view data = "hello";
    h.add_chunk(std::span{ data.begin(), data.end() });
    const auto hash1 = h.finilize();

    h.add_chunk(std::span{ data.begin(), data.end() });
    const auto hash2 = h.finilize();

    EXPECT_EQ(hash1, hash2);
}