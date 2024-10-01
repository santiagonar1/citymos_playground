#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <data_provider.hpp>

using namespace playground;
using testing::Eq;

TEST(DataProvider, GivesMetricsForACertainNumRanksAtACertainSimulationTime) {
    const std::string log_2_ranks = "****** reading METIS data form time= 30 mins *********\n"
                              "timeMpiSend=[0.1,0.2,]\n"
                              "numAgents=[1, 2,]\n"
                              "****** reading METIS data form time= 60 mins *********\n"
                              "timeMpiSend=[1.1,1.2,]\n"
                              "numAgents=[3, 4,]";

    auto stream_2_ranks = std::istringstream(log_2_ranks);

    const auto data_provider = DataProvider{2, stream_2_ranks};

    const auto reported_metrics = data_provider.get_metrics_for(2, 30);

    EXPECT_THAT(
            reported_metrics,
            Eq(std::vector{MetricEntry{MetricType::TimeMPISend, MetricValue{std::vector{
                                                                        0.1,
                                                                        0.2,
                                                                }}},
                           MetricEntry{MetricType::NumAgents, MetricValue{std::vector{1, 2}}}}));
}

TEST(DataProvider, GivesTheAvailableNumberOfRanks) {
    const std::string log_2_ranks = "****** reading METIS data form time= 30 mins *********\n"
                              "timeMpiSend=[0.1,0.2,]\n"
                              "numAgents=[1, 2,]\n"
                              "****** reading METIS data form time= 60 mins *********\n"
                              "timeMpiSend=[1.1,1.2,]\n"
                              "numAgents=[3, 4,]";

    auto stream_2_ranks = std::istringstream(log_2_ranks);

    const auto data_provider = DataProvider{2, stream_2_ranks};

    EXPECT_THAT(data_provider.num_ranks_available(), Eq(std::vector{2}));
}

TEST(DataProvider, GivesTheAvailableSimulationTimes) {
    const std::string log_2_ranks = "****** reading METIS data form time= 30 mins *********\n"
                              "timeMpiSend=[0.1,0.2,]\n"
                              "numAgents=[1, 2,]\n"
                              "****** reading METIS data form time= 60 mins *********\n"
                              "timeMpiSend=[1.1,1.2,]\n"
                              "numAgents=[3, 4,]";


    auto stream_2_ranks = std::istringstream(log_2_ranks);

    const auto data_provider = DataProvider{2, stream_2_ranks};

    EXPECT_THAT(data_provider.simulation_times_available(), Eq(std::vector{30, 60}));
}