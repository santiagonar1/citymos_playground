#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

#include "measurement.hpp"

namespace playground {
    class Logger {
    public:
        Logger(const std::string &file_path, SimulationTime elastic_interval);

        auto log(const Measurement& measurement) -> void;

    private:
        std::ofstream _log_file{};
        const SimulationTime _elastic_interval{};
    };
}// namespace playground

#endif//LOGGER_HPP
