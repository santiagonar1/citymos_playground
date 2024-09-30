#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <parser.hpp>

TEST(IsHeader, ReturnsTrueIfLineIsHeader) {
    const auto header_line = std::string{"****** reading METIS data form time= 30 mins *********"};
    EXPECT_TRUE(playground::parser::is_header(header_line));
}

TEST(IsHeader, ReturnsFalseIfLineIsNotHeader) {
    const auto data_line = std::string{"timeMpiSend=[0,]"};
    EXPECT_FALSE(playground::parser::is_header(data_line));
}