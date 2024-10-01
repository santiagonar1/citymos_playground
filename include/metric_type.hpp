#ifndef METRIC_TYPE_HPP
#define METRIC_TYPE_HPP

namespace playground {
    enum class MetricType {
        TimeMPISend,
        TimeMPIRecv,
        TimeToCompletion,
        Speedups,
        NumAgents,
        TotalUpdateTime,
        NoBarrierUpdateTime,
    };
}// namespace playground

#endif//METRIC_TYPE_HPP
