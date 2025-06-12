//
// Created by sigris on 10.06.2025.
//

#pragma once

#include "../Metrics/DefaultMetric.h"
#include "map"
#include "string"

class Writer{
public:
    Writer()= default;
    virtual void printAllMetrics(const std::unordered_map<std::string, std::shared_ptr<Metric>> metrics){};
    virtual std::string getPrintedPlace(){};
    virtual ~Writer()= default;
};
