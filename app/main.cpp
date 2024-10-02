#include <iostream>
#include <random>

#include <data_provider.hpp>

auto select_random(const std::vector<int> &options) -> int;
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

    for (const auto &simulation_time: simulation_times) {
        const auto num_ranks = select_random(available_ranks);
        const auto metrics = data_provider.get_metrics_for(num_ranks, simulation_time);
        std::cout << "Simulation time: " << simulation_time << "\n";
        std::cout << "Running with: " << num_ranks << " ranks\n";
        std::cout << metrics << "\n\n";
    }
    return 0;
}

auto select_random(const std::vector<int> &options) -> int {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distr(0, static_cast<int>(options.size()) - 1);

    int random_index = distr(gen);

    return options[random_index];
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
