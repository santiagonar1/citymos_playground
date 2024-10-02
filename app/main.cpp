#include <iostream>

#include <data_provider.hpp>
#include <measurement.hpp>
#include <policy.hpp>

auto operator<<(std::ostream &os, const std::vector<playground::MetricEntry> &metrics)
        -> std::ostream &;

int main() {
    const auto input_data = std::vector<playground::DataInput>{
            {1, "/home/santiago/git/citymos_playground/data/1_rank.txt"},
            {2, "/home/santiago/git/citymos_playground/data/2_ranks.txt"},
            {3, "/home/santiago/git/citymos_playground/data/3_ranks.txt"}};

    const auto data_provider = playground::DataProvider{input_data};
    const auto simulation_times = data_provider.simulation_times_available();
    const auto available_ranks = data_provider.num_ranks_available();
    auto num_ranks = available_ranks[0];

    const auto policy = playground::Policy{available_ranks};

    auto measurements = std::vector<playground::Measurement>{};
    for (const auto &simulation_time: simulation_times) {
        const auto metrics = data_provider.get_metrics_for(num_ranks, simulation_time);
        std::cout << "Simulation time: " << simulation_time << "\n";
        std::cout << "Running with: " << num_ranks << " ranks\n";
        std::cout << metrics << "\n\n";

        measurements.emplace_back(simulation_time, num_ranks, metrics);
        num_ranks = policy.get_num_ranks(measurements);
    }
    return 0;
}

auto operator<<(std::ostream &os, const std::vector<playground::MetricEntry> &metrics)
        -> std::ostream & {
    os << "[";
    for (size_t i = 0; i < metrics.size(); ++i) {
        if (i > 0) os << ", ";
        os << metrics[i];
    }
    os << "]";
    return os;
}
