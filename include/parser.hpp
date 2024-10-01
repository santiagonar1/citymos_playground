#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "metric_entry.hpp"
#include "simulation_time.hpp"

namespace playground::parser {
    namespace internal {
        [[nodiscard]] auto is_header(std::string_view line) -> bool;
        [[nodiscard]] auto get_simulation_time(const std::string &header_line) -> int;
        [[nodiscard]] auto as_metric_type(const std::string &key) -> std::optional<MetricType>;

        [[nodiscard]] auto parse_metric_line(const std::string &metric_line) -> MetricEntry;

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
    }// namespace internal


    [[nodiscard]] auto parse_document(std::istream &input)
            -> std::map<SimulationTime, std::vector<MetricEntry>>;

}// namespace playground::parser

#endif//PARSER_HPP
