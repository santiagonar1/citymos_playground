#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utils.hpp>

using namespace playground::utils;
using testing::Eq;

TEST(SplitBy, SplitsAStringInTwoBasedOnDelimiter) {
    constexpr char delimiter = ',';
    const auto first_part = std::string{"first_part"};
    const auto second_part = std::string{"second_part"};
    const auto str = first_part + delimiter + second_part;

    EXPECT_THAT(split_by(str, delimiter), Eq(std::pair{first_part, second_part}));
}