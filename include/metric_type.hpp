#ifndef METRIC_TYPE_HPP
#define METRIC_TYPE_HPP

#include <ostream>

namespace playground {
    enum class MetricType {
        TimeMPISend,
        TimeMPIRecv,
        TimeToCompletion,
        Speedups,
        NumAgents,
        TotalUpdateTime,
        NoBarrierUpdateTime,
    };

    [[nodiscard]] auto is_integer_metric(const MetricType &metric_type) -> bool;
    auto operator<<(std::ostream &os, const MetricType &metric_type) -> std::ostream &;
}// namespace playground

#endif//METRIC_TYPE_HPP
