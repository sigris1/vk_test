//
// Created by sigris on 11.06.2025.
//

#include "MetricsManager.h"
#include "iostream"
#include "future"

MetricsManager::MetricsManager(std::shared_ptr<Writer> writer)
    :writer_(std::move(writer))
    {}

void MetricsManager::addMetric(const std::shared_ptr<Metric>& metric) {
    metrics_[metric->getName()] = metric;
}

void MetricsManager::runMetric(const std::string& name) {
    if (!metrics_.contains(name)){
        std::cerr << "There's no metric with that name";
    } else {
        auto now = metrics_[name];
        std::async(std::launch::async, [now]() {
            now->run();
        });
    }
}

std::string MetricsManager::getMetricResults(const std::string& name){
    if (!metrics_.contains(name)){
        std::cerr << "There's no metric with that name";
        return "";
    }
    return metrics_[name]->toString();
}

void MetricsManager::writeAllMetric() {
    writer_->printAllMetrics(metrics_);

    for (const auto& i : metrics_) {
        i.second->clearValues();
    }
}

void MetricsManager::runAllMetrics(){
    for (auto& i : metrics_){
        i.second->run();
    }
}
