#include "metric_entry.hpp"

namespace playground {
    auto operator<<(std::ostream &os, const MetricEntry &metric_entry) -> std::ostream & {
        os << "Type: " << metric_entry.first << "Values: " << metric_entry.second;
        return os;
    }
}// namespace playground