#include "logger.hpp"

#include <ranges>

#include "utils.hpp"

namespace playground {
    Logger::Logger(const std::string &file_path, SimulationTime elastic_interval)
        : _log_file(file_path), _elastic_interval(elastic_interval) {
        if (not _log_file.is_open()) { throw std::runtime_error("Could not open log file"); }

        const auto header = std::string{"simulation_time, rank_id, speedup, wall-clock time"};
        _log_file << header << std::endl;
    }

    auto Logger::log(const Measurement &measurement) -> void {
        const auto [time, num_ranks, metrics] = measurement;

        const auto speedups = std::get<std::vector<double>>(
                utils::get_metric_values(metrics, MetricType::Speedups));

        for (int i = 0; i < num_ranks; i++) {
            const double wall_clock = _elastic_interval * 60 / speedups[i];
            _log_file << time << ", " << i << ", " << speedups[i] << ", " << wall_clock
                      << std::endl;
        }
    }

}// namespace playground