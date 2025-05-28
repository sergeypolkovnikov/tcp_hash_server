#include <gtest/gtest.h>
#include "hasher.hpp"
#include <string_view>

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