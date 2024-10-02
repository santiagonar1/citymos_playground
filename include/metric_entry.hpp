#ifndef METRIC_ENTRY_HPP
#define METRIC_ENTRY_HPP

#include "metric_type.hpp"
#include "metric_value.hpp"

namespace playground {
    using MetricEntry = std::pair<MetricType, MetricValue>;

    auto operator<<(std::ostream &os, const MetricEntry &metric_entry) -> std::ostream &;
}// namespace playground

#endif//METRIC_ENTRY_HPP
