#include "utils.hpp"

namespace playground::utils {
    auto split_by(const std::string &str, char delimiter) -> std::pair<std::string, std::string> {
        const auto delimiter_pos = str.find_first_of(delimiter);
        return {str.substr(0, delimiter_pos), str.substr(delimiter_pos + 1)};
    }
}// namespace playground::utils