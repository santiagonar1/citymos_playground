#ifndef METRIC_ENTRY_HPP
#define METRIC_ENTRY_HPP

#include "metric_type.hpp"
#include "metric_value.hpp"

namespace playground {
    using MetricEntry = std::pair<MetricType, MetricValue>;
}// namespace playground

#endif//METRIC_ENTRY_HPP
