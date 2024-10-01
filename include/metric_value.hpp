#ifndef METRIC_VALUE_HPP
#define METRIC_VALUE_HPP

#include <vector>
#include <variant>

namespace playground {
    using MetricValue = std::variant<std::vector<int>, std::vector<double>>;
}// namespace playground

#endif //METRIC_VALUE_HPP
