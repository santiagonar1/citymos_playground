#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace playground::utils {
    auto split_by(const std::string &str, char delimiter) -> std::pair<std::string, std::string>;

    [[nodiscard]] auto extract_substr(const std::string &str, const std::string &from,
                                      const std::string &to) -> std::string;
}// namespace playground::utils

#endif//UTILS_HPP
