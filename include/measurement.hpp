#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

#include "metric_entry.hpp"
#include "simulation_time.hpp"

namespace playground {
    struct Measurement {
        SimulationTime time{};
        int num_ranks{};
        std::vector<MetricEntry> metrics{};
    };
}// namespace playground

#endif//MEASUREMENT_HPP
