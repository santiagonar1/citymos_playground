#include "metric_type.hpp"

#include <stdexcept>

namespace playground {
    auto is_integer_metric(const MetricType &metric_type) -> bool {
        switch (metric_type) {
            case MetricType::NumAgents:
                return true;
            case MetricType::TimeMPISend:
            case MetricType::TimeMPIRecv:
            case MetricType::TimeToCompletion:
            case MetricType::Speedups:
            case MetricType::TotalUpdateTime:
            case MetricType::NoBarrierUpdateTime:
                return false;
            default:
                throw std::invalid_argument("Unhandled case in is_integer_metric");
        }
    }
}// namespace playground