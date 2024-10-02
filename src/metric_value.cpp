#include "metric_value.hpp"

#include <utility>

namespace playground {
    namespace internal {
        struct MetricValuePrinter {
            std::ostream &os;

            template<typename T>
            void operator()(const std::vector<T> &values) const {
                auto delimiter = std::string{};
                os << "[";
                for (const auto value: values) { os << std::exchange(delimiter, ", ") << value; }
                os << "]";
            }
        };
    }// namespace internal

    std::ostream &operator<<(std::ostream &os, const MetricValue &metric_value) {
        std::visit(internal::MetricValuePrinter{os}, metric_value);
        return os;
    }
}// namespace playground