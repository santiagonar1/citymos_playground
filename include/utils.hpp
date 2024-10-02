#ifndef UTILS_HPP
#define UTILS_HPP

#include <metric_entry.hpp>
#include <string>

namespace playground::utils {
    auto split_by(const std::string &str, char delimiter) -> std::pair<std::string, std::string>;

    [[nodiscard]] auto extract_substr(const std::string &str, const std::string &from,
                                      const std::string &to) -> std::string;

    [[nodiscard]] auto get_metric_values(const std::vector<MetricEntry> &metrics,
                                         const MetricType &metric_type) -> MetricValue;
}// namespace playground::utils

#endif//UTILS_HPP
