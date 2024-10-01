#include "parser.hpp"

#include <optional>
#include <string>

#include "utils.hpp"

#include <map>

namespace playground::parser {
    namespace internal {
        auto is_time_mpi_send_key(const std::string &key) -> bool { return key == "timeMpiSend"; }

        auto is_time_mpi_recv_key(const std::string &key) -> bool { return key == "timeMpiRecv"; }

        auto is_time_to_completion_key(const std::string &key) -> bool {
            return key == "timeToCompletion";
        }

        auto is_speedups_key(const std::string &key) -> bool { return key == "speedups"; }

        auto is_num_agents_key(const std::string &key) -> bool { return key == "numAgents"; }

        auto is_total_update_time_key(const std::string &key) -> bool {
            return key == "totalUpdateTime";
        }

        auto is_no_barrier_update_time_key(const std::string &key) -> bool {
            return key == "noBarrierUpdateTime";
        }

        auto get_values(const std::string &values_list, const MetricType &metric_type)
                -> MetricValue {
            if (is_integer_metric(metric_type)) { return as_vector<int>(values_list); }

            return as_vector<double>(values_list);
        }


        auto is_header(const std::string_view line) -> bool { return line[0] == '*'; }

        auto get_simulation_time(const std::string &header_line) -> int {
            const auto time_keyword = std::string{"time="};
            const auto mins_keyword = std::string{"mins"};
            const auto number_str = utils::extract_substr(header_line, time_keyword, mins_keyword);
            return std::stoi(number_str);
        }

        auto as_metric_type(const std::string &key) -> std::optional<MetricType> {
            if (is_time_mpi_send_key(key)) { return MetricType::TimeMPISend; }

            if (is_time_mpi_recv_key(key)) { return MetricType::TimeMPIRecv; }

            if (is_time_to_completion_key(key)) { return MetricType::TimeToCompletion; }

            if (is_speedups_key(key)) { return MetricType::Speedups; }

            if (is_num_agents_key(key)) { return MetricType::NumAgents; }

            if (is_total_update_time_key(key)) { return MetricType::TotalUpdateTime; }

            if (is_no_barrier_update_time_key(key)) { return MetricType::NoBarrierUpdateTime; }

            return {};
        }

        auto parse_metric_line(const std::string &metric_line) -> MetricEntry {
            const auto [metric_key, values_list] = utils::split_by(metric_line, '=');
            const auto metric_type = as_metric_type(metric_key).value();
            const auto values = get_values(values_list, metric_type);
            return {metric_type, values};
        }

    }// namespace internal

    auto parse_document(std::istream &input) -> std::map<SimulationTime, std::vector<MetricEntry>> {
        auto result = std::map<SimulationTime, std::vector<MetricEntry>>{};

        SimulationTime time{};
        auto line = std::string{};
        while (std::getline(input, line)) {
            if (internal::is_header(line)) {
                time = internal::get_simulation_time(line);
                result.emplace(time, std::vector<MetricEntry>{});
            } else {
                const auto [metric_type, values] = internal::parse_metric_line(line);
                result.at(time).emplace_back(metric_type, values);
            }
        }

        return result;
    }
}// namespace playground::parser