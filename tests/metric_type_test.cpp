#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <metric_type.hpp>

using namespace playground;

TEST(IsIntegerMetric, OnlyNumAgentsIsIntegerMetric) {
    EXPECT_TRUE(is_integer_metric(MetricType::NumAgents));

    EXPECT_FALSE(is_integer_metric(MetricType::TimeMPISend));
    EXPECT_FALSE(is_integer_metric(MetricType::TimeMPIRecv));
    EXPECT_FALSE(is_integer_metric(MetricType::TimeToCompletion));
    EXPECT_FALSE(is_integer_metric(MetricType::Speedups));
    EXPECT_FALSE(is_integer_metric(MetricType::TotalUpdateTime));
    EXPECT_FALSE(is_integer_metric(MetricType::NoBarrierUpdateTime));
}