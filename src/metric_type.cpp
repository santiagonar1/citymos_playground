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

    std::ostream &operator<<(std::ostream &os, const MetricType &metric_type) {
        switch (metric_type) {
            case MetricType::TimeMPISend:
                os << "TimeMPISend";
                break;
            case MetricType::TimeMPIRecv:
                os << "TimeMPIRecv";
                break;
            case MetricType::TimeToCompletion:
                os << "TimeToCompletion";
                break;
            case MetricType::Speedups:
                os << "Speedups";
                break;
            case MetricType::NumAgents:
                os << "NumAgents";
                break;
            case MetricType::TotalUpdateTime:
                os << "TotalUpdateTime";
                break;
            case MetricType::NoBarrierUpdateTime:
                os << "NoBarrierUpdateTime";
                break;
            default:
                os << "Unknown Metric";
                break;
        }
        return os;
    }
}// namespace playground