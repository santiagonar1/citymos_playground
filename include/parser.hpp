#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <string_view>

namespace playground::parser {
    [[nodiscard]] auto is_header(std::string_view line) -> bool;
    [[nodiscard]] auto get_simulation_time(const std::string &header_line) -> int;
}// namespace playground::parser

#endif//PARSER_HPP
