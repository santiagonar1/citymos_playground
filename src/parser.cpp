#include "parser.hpp"

#include <string>

namespace playground::parser {
    auto is_header(const std::string_view line) -> bool { return line[0] == '*'; }

    auto get_simulation_time(const std::string &header_line) -> int {
        const auto time_keyword = std::string{"time="};
        const auto mins_keyword = std::string{"mins"};
        const auto starting_pos = header_line.find(time_keyword) + time_keyword.length();
        const auto ending_pos = header_line.find(mins_keyword, starting_pos);
        const auto number_str = header_line.substr(starting_pos, ending_pos);
        return std::stoi(number_str);
    }
}// namespace playground::parser