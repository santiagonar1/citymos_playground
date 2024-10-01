#include "data_provider.hpp"

#include <ranges>

#include "parser.hpp"

namespace playground {
    DataProvider::DataProvider(int num_ranks, std::istream &input) {
        const auto results = parser::parse_document(input);
        _metrics[num_ranks] = results;
    }

    DataProvider::DataProvider(const std::vector<DataInput> &inputs) {
        for (const auto &[num_ranks, input_file]: inputs) {
            const auto results = parser::parse_document(input_file);
            _metrics[num_ranks] = results;
        }
    }

    auto DataProvider::get_metrics_for(int num_ranks, SimulationTime time) const
            -> std::vector<MetricEntry> {
        return _metrics.at(num_ranks).at(time);
    }

    auto DataProvider::num_ranks_available() const -> std::vector<int> {
        auto keys_view = _metrics | std::views::keys;
        return {keys_view.begin(), keys_view.end()};
    }

    auto DataProvider::simulation_times_available() const -> std::vector<SimulationTime> {
        const auto num_ranks_available = DataProvider::num_ranks_available();
        auto simulation_times_view = _metrics.at(num_ranks_available[0]) | std::views::keys;
        return {simulation_times_view.begin(), simulation_times_view.end()};
    }

}// namespace playground