#ifndef POLICY_HPP
#define POLICY_HPP

#include "measurement.hpp"

namespace playground {
    class Policy {
    public:
        explicit Policy(const std::vector<int> &available_ranks);

        [[nodiscard]] auto get_num_ranks(const std::vector<Measurement> &measurements) const -> int;

    private:
        const std::vector<int> _available_ranks;
    };
}// namespace playground

#endif//POLICY_HPP
