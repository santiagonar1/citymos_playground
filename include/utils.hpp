#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace playground::utils {
    auto split_by(const std::string &str, char delimiter) -> std::pair<std::string, std::string>;
}

#endif //UTILS_HPP
