#include "policy.hpp"

#include <random>

namespace playground {
    auto select_random(const std::vector<int> &options) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution distr(0, static_cast<int>(options.size()) - 1);

        int random_index = distr(gen);

        return options[random_index];
    }

    Policy::Policy(const std::vector<int> &available_ranks) : _available_ranks(available_ranks) {}

    auto Policy::get_num_ranks(const std::vector<Measurement> &measurements) const -> int {
        return select_random(_available_ranks);
    }
}// namespace playground