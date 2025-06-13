//
// Created by sigris on 11.06.2025.
//

#pragma once

#include "../MetricsWriters/Writer.h"
#include "map"

class MetricsManager {
public:
    explicit MetricsManager(std::shared_ptr<Writer> writer);
    void addMetric(const std::shared_ptr<Metric>& metric);
    void runMetric(const std::string& name);
    std::string getMetricResults(const std::string& name);
    void runAllMetrics();
    void writeAllMetric();
    ~MetricsManager()= default;
private:
    std::unordered_map<std::string, std::shared_ptr<Metric>> metrics_;
    std::shared_ptr<Writer> writer_;
};


