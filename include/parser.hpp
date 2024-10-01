#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "metric_type.hpp"

namespace playground::parser {
    [[nodiscard]] auto is_header(std::string_view line) -> bool;
    [[nodiscard]] auto get_simulation_time(const std::string &header_line) -> int;
    [[nodiscard]] auto extract_substr(const std::string &str, const std::string &from,
                                      const std::string &to) -> std::string;
    [[nodiscard]] auto as_metric_type(const std::string &key) -> std::optional<MetricType>;

    template<typename T>
    [[nodiscard]] auto as_vector(const std::string &str) -> std::vector<T> {
        std::vector<T> results{};
        T value{};
        char not_number{};

        std::istringstream stream{str};
        stream >> not_number;
        while (stream >> value) {
            results.push_back(value);
            stream >> not_number;
        }

        return results;
    }
}// namespace playground::parser

#endif//PARSER_HPP
