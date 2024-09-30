#ifndef PARSER_HPP
#define PARSER_HPP
#include <string_view>

namespace playground::parser {
    [[nodiscard]] auto is_header(std::string_view line) -> bool;
}// namespace playground::parser

#endif//PARSER_HPP
