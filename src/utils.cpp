#include "utils.hpp"

namespace playground::utils {
    auto split_by(const std::string &str, char delimiter) -> std::pair<std::string, std::string> {
        const auto delimiter_pos = str.find_first_of(delimiter);
        return {str.substr(0, delimiter_pos), str.substr(delimiter_pos + 1)};
    }

    auto extract_substr(const std::string &str, const std::string &from, const std::string &to)
            -> std::string {
        const auto starting_pos = str.find(from);
        const auto ending_pos = str.find(to, starting_pos + from.length());
        const auto substr_length = ending_pos - starting_pos;

        return str.substr(starting_pos + from.length(), substr_length - 1);
    }
}// namespace playground::utils