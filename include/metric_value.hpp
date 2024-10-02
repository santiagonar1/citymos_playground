#ifndef METRIC_VALUE_HPP
#define METRIC_VALUE_HPP

#include <ostream>
#include <variant>
#include <vector>

namespace playground {
    using MetricValue = std::variant<std::vector<int>, std::vector<double>>;

    auto operator<<(std::ostream &os, const MetricValue &metric_value) -> std::ostream &;
}// namespace playground

#endif//METRIC_VALUE_HPP
