#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include <map>
#include <string>
#include <vector>

#include "metric_entry.hpp"
#include "simulation_time.hpp"

namespace playground {
    struct DataInput {
        const int num_ranks{};
        const std::string input_file{};
    };

    class DataProvider {
    public:
        DataProvider(int num_ranks, std::istream &input);

        explicit DataProvider(const std::vector<DataInput> &inputs);

        [[nodiscard]] auto get_metrics_for(int num_ranks, SimulationTime time) const
                -> std::vector<MetricEntry>;

        [[nodiscard]] auto num_ranks_available() const -> std::vector<int>;

        [[nodiscard]] auto simulation_times_available() const -> std::vector<SimulationTime>;


    private:
        std::map<int, std::map<SimulationTime, std::vector<MetricEntry>>> _metrics;
    };
}// namespace playground

#endif//DATA_PROVIDER_HPP
