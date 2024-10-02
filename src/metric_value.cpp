#include "metric_value.hpp"

namespace playground {
    namespace internal {
        struct MetricValuePrinter {
            std::ostream &os;

            void operator()(const std::vector<int> &values) const {
                os << "[";
                for (size_t i = 0; i < values.size(); ++i) {
                    if (i > 0) os << ", ";
                    os << values[i];
                }
                os << "]";
            }

            void operator()(const std::vector<double> &values) const {
                os << "[";
                for (size_t i = 0; i < values.size(); ++i) {
                    if (i > 0) os << ", ";
                    os << values[i];
                }
                os << "]";
            }
        };
    }// namespace internal

    std::ostream &operator<<(std::ostream &os, const MetricValue &metric_value) {
        std::visit(internal::MetricValuePrinter{os}, metric_value);
        return os;
    }
}// namespace playground