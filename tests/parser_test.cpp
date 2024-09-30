#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <parser.hpp>

using namespace playground::parser;
using testing::Eq;

TEST(IsHeader, ReturnsTrueIfLineIsHeader) {
    const auto header_line = std::string{"****** reading METIS data form time= 30 mins *********"};
    EXPECT_TRUE(playground::parser::is_header(header_line));
}

TEST(IsHeader, ReturnsFalseIfLineIsNotHeader) {
    const auto data_line = std::string{"timeMpiSend=[0,]"};
    EXPECT_FALSE(is_header(data_line));
}

TEST(GetSimulationTime, ReturnsTheSimulationTimeFromHeader) {
    const auto header_line = std::string{"****** reading METIS data form time= 30 mins *********"};
    EXPECT_THAT(get_simulation_time(header_line), Eq(30));
}

TEST(ExtractSubstr, ReturnsStringBetweenDelimiters) {
    const auto left_delimiter = std::string{"["};
    const auto right_delimiter = std::string{"]"};
    const auto data = std::string{"data"};
    const auto garbage = std::string{"12345"};
    const auto str = garbage + left_delimiter + data + right_delimiter + garbage;

    EXPECT_THAT(extract_substr(str, left_delimiter, right_delimiter), Eq(data));
}

TEST(AsVector, GetsAStringWithCommaSeparatedValuesAndReturnsAVector) {
    const auto str = std::string{"[1,2,]"};

    EXPECT_THAT(as_vector<int>(str), Eq(std::vector{1, 2}));
}

TEST(AsVector, WorksWithDoubles) {
    const auto str = std::string{"[16.9165,16.7611,18.7212,]"};

    EXPECT_THAT(as_vector<double>(str), Eq(std::vector{16.9165, 16.7611, 18.7212}));
}