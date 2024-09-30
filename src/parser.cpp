#include "parser.hpp"

#include <string>

namespace playground::parser {
    auto is_header(const std::string_view line) -> bool { return line[0] == '*'; }


    auto extract_substr(const std::string &str, const std::string &from, const std::string &to)
            -> std::string {
        const auto starting_pos = str.find(from);
        const auto ending_pos = str.find(to, starting_pos + from.length());
        const auto substr_length = ending_pos - starting_pos;

        return str.substr(starting_pos + from.length(), substr_length - 1);
    }

    auto get_simulation_time(const std::string &header_line) -> int {
        const auto time_keyword = std::string{"time="};
        const auto mins_keyword = std::string{"mins"};
        const auto number_str = extract_substr(header_line, time_keyword, mins_keyword);
        return std::stoi(number_str);
    }
}// namespace playground::parser