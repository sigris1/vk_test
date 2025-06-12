//
// Created by sigris on 10.06.2025.
//

#include "gtest/gtest.h"
#include "Metrics/DefaultMetric.h"
#include "AuxiliaryFunctions.h"

TEST(metrics_controller, labmdaFunctionFirstTest){
    auto foo = [](){return 1;};
    DefaultMetric<decltype(foo)> metric("metric", foo);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 1");
}

TEST(metrics_controller, labmdaFunctionSecondTest){
    auto foo = [](int a, int b){return a * b;};
    DefaultMetric<decltype(foo), int, int> metric("metric", foo, 3, 5);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 15");
}

TEST(metrics_controller, BaseIntFuncion){
    DefaultMetric<decltype(&intFoo)> metric("metric", &intFoo);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 1");
}

TEST(metrics_controller, MultiplyIntFuncion){
    DefaultMetric<decltype(&multiply), int, int, int> metric("metric", &multiply, 2, 3, 5);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 30");
}

TEST(metrics_controller, StringReverseFunction){
    DefaultMetric<decltype(&myreverse), std::string> metric("metric", &myreverse, "reverse");
    metric.run();
    ASSERT_EQ(metric.toString(), "metric esrever");
}

TEST(metrics_controller, VectorMutableFunction){
    DefaultMetric<decltype(&mutableVector), std::vector<int>> metric("metric", &mutableVector, (std::vector<int>){1, 2, 3});
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 1 4 9");
}

TEST(metrics_controller, PairMutableFunction){
    DefaultMetric<decltype(&mutablePair), int, int> metric("metric", &mutablePair, 3, 4);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 9 16");
}

TEST(metrics_controller, TupleMutableFunction){
    DefaultMetric<decltype(&mutableTuple), std::tuple<int, std::string, std::vector<int>>> metric("metric", &mutableTuple, (std::tuple<int, std::string, std::vector<int>>){4, "reverse", (std::vector<int>){1, 2, 3}});
    metric.run();
    ASSERT_EQ(metric.toString(), "metric 16 esrever 1 4 9");
}

TEST(metrics_controller, VoidButMutableFunction){
    std::vector<int> tested = {1, 2, 3, 4, 5};
    DefaultMetric<decltype(&multiplyVector), std::vector<int>&> metric("metric", &multiplyVector, tested);
    metric.run();
    for (int i = 0; i < 5; ++i){
        ASSERT_EQ(tested[i], (i + 1) * (i + 1));
    }
    ASSERT_EQ(metric.toString(), "metric");
}

TEST(metrics_controller, CustomClassesWithOutPutOperatorFunction){
    DefaultMetric<decltype(&getTested), int, int> metric("metric", &getTested, 4, 5);
    metric.run();
    ASSERT_EQ(metric.toString(), "metric tested(4, 5)");
}