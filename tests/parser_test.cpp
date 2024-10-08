#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <parser.hpp>

using namespace playground::parser::internal;
using namespace playground::parser;
using namespace playground;
using testing::Eq;

TEST(IsHeader, ReturnsTrueIfLineIsHeader) {
    const auto header_line = std::string{"****** reading METIS data form time= 30 mins *********"};
    EXPECT_TRUE(is_header(header_line));
}

TEST(IsHeader, ReturnsFalseIfLineIsNotHeader) {
    const auto data_line = std::string{"timeMpiSend=[0,]"};
    EXPECT_FALSE(is_header(data_line));
}

TEST(GetSimulationTime, ReturnsTheSimulationTimeFromHeader) {
    const auto header_line = std::string{"****** reading METIS data form time= 30 mins *********"};
    EXPECT_THAT(get_simulation_time(header_line), Eq(30));
}

TEST(AsVector, GetsAStringWithCommaSeparatedValuesAndReturnsAVector) {
    const auto str = std::string{"[1,2,]"};

    EXPECT_THAT(as_vector<int>(str), Eq(std::vector{1, 2}));
}

TEST(AsVector, WorksWithDoubles) {
    const auto str = std::string{"[16.9165,16.7611,18.7212,]"};

    EXPECT_THAT(as_vector<double>(str), Eq(std::vector{16.9165, 16.7611, 18.7212}));
}

TEST(GetMetricType, ReturnsTheMetricTypeGivenAKey) {
    const auto key = std::string{"timeMpiSend"};
    EXPECT_THAT(as_metric_type(key).value(), Eq(MetricType::TimeMPISend));
}

TEST(GetMetricType, ReturnsEmtpyOptionalIfKeyNotFound) {
    const auto not_a_key = std::string{"NotAKey"};
    EXPECT_FALSE(as_metric_type(not_a_key).has_value());
}

TEST(GetMetricType, WorksForTimeMPISend) {
    const auto time_mpi_send_key = std::string{"timeMpiSend"};
    EXPECT_THAT(as_metric_type(time_mpi_send_key).value(), Eq(MetricType::TimeMPISend));
}

TEST(GetMetricType, WorksForTimeMPIRecv) {
    const auto time_mpi_recv_key = std::string{"timeMpiRecv"};
    EXPECT_THAT(as_metric_type(time_mpi_recv_key).value(), Eq(MetricType::TimeMPIRecv));
}

TEST(GetMetricType, WorksForTimeToCompletion) {
    const auto time_to_completion = std::string{"timeToCompletion"};
    EXPECT_THAT(as_metric_type(time_to_completion).value(), Eq(MetricType::TimeToCompletion));
}

TEST(GetMetricType, WorksForSpeedups) {
    const auto speedups_key = std::string{"speedups"};
    EXPECT_THAT(as_metric_type(speedups_key).value(), Eq(MetricType::Speedups));
}

TEST(GetMetricType, WorksForNumAgents) {
    const auto num_agents_key = std::string{"numAgents"};
    EXPECT_THAT(as_metric_type(num_agents_key).value(), Eq(MetricType::NumAgents));
}

TEST(GetMetricType, WorksForTotalUpdateTime) {
    const auto total_update_time_key = std::string{"totalUpdateTime"};
    EXPECT_THAT(as_metric_type(total_update_time_key).value(), Eq(MetricType::TotalUpdateTime));
}

TEST(GetMetricType, WorksForNoBarrierUpdateTime) {
    const auto no_barrier_update_time_key = std::string{"noBarrierUpdateTime"};
    EXPECT_THAT(as_metric_type(no_barrier_update_time_key).value(),
                Eq(MetricType::NoBarrierUpdateTime));
}

TEST(ParseMetricLine, ReturnsMetricTypeAndValues) {
    const auto metric_line = std::string{"timeMpiSend=[0.414859,0.577273,0.866705,]"};
    const auto [metric_type, values] = parse_metric_line(metric_line);

    EXPECT_THAT(metric_type, Eq(MetricType::TimeMPISend));
    EXPECT_THAT(std::get<std::vector<double>>(values),
                Eq(std::vector{0.414859, 0.577273, 0.866705}));
}

TEST(ParseMetricLine, WorksForIntegerMetrics) {
    const auto metric_line = std::string{"numAgents=[2985,3040,2960,]"};
    const auto [metric_type, values] = parse_metric_line(metric_line);

    EXPECT_THAT(metric_type, Eq(MetricType::NumAgents));
    EXPECT_THAT(std::get<std::vector<int>>(values), Eq(std::vector{2985, 3040, 2960}));
}

TEST(ParseDocument, ReturnsTheMetricsGroupedBySimulationTime) {
    const std::string log_data = "****** reading METIS data form time= 30 mins *********\n"
                                 "timeMpiSend=[0.1,0.2,0.3,]\n"
                                 "numAgents=[3,4,5,]\n"
                                 "****** reading METIS data form time= 60 mins *********\n"
                                 "totalUpdateTime=[1.1,1.2,1.3,]\n"
                                 "noBarrierUpdateTime=[1.4,1.5,1.6,]";

    auto stream = std::istringstream{log_data};

    const auto result = parse_document(stream);
    const auto metrics_at_30 = result.at(30);
    const auto metrics_at_60 = result.at(60);

    EXPECT_THAT(metrics_at_30, Eq(std::vector{MetricEntry{MetricType::TimeMPISend,
                                                          MetricValue{std::vector{0.1, 0.2, 0.3}}},
                                              MetricEntry{MetricType::NumAgents,
                                                          MetricValue{std::vector{3, 4, 5}}}}));
    EXPECT_THAT(metrics_at_60,
                Eq(std::vector{MetricEntry{MetricType::TotalUpdateTime,
                                           MetricValue{std::vector{1.1, 1.2, 1.3}}},
                               MetricEntry{MetricType::NoBarrierUpdateTime,
                                           MetricValue{std::vector{1.4, 1.5, 1.6}}}}));
}