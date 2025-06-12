//
// Created by sigris on 10.06.2025.
//

#pragma once

#include <utility>
#include "tuple"
#include "string"
#include "sstream"
#include "../ResultsAnalyzer/ResultAnalyzer.h"
#include "Metric.h"
#include "optional"

template<typename result>
using safety_type = std::conditional_t<std::is_void_v<result>, std::monostate, std::optional<result>>;

template<typename Func, typename... Args>
class DefaultMetric : public Metric{
public:
    using ReturnedTypes = std::invoke_result_t<Func, Args...>;

    DefaultMetric(std::string  name, Func func, Args... args)
            :name_(std::move(name))
            ,function_(func)
            ,args_(std::forward<Args>(args)...)
    {}

    std::string getName() override{
        return name_;
    }

    std::string toString() override {
        std::stringstream s;
        s << name_;

        if constexpr (!std::is_void_v<ReturnedTypes>) {
            auto results = getMetricValues();
            s << " " << ResultAnalyzer<decltype(results)>::results_to_string(results);
        }
        return s.str();
    }

    void run() override{
        if constexpr (!std::is_void_v<ReturnedTypes>) {
            values_ = std::apply(function_, args_);
        } else {
            std::apply(function_, args_);
        }
    }

    void clearValues() override{
        if constexpr (!std::is_void_v<ReturnedTypes>) {
            values_.reset();
        }
    }

    ReturnedTypes getMetricValues(){
        if constexpr (!std::is_void_v<ReturnedTypes>) {
            return values_.value();
        }
    }

    ~DefaultMetric()= default;

private:
    std::tuple<Args...> args_;
    std::string name_;
    Func function_;
    safety_type<ReturnedTypes> values_;
};


