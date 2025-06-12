//
// Created by sigris on 11.06.2025.
//

#pragma once

#include "string"

class Metric{
public:
    Metric()= default;
    virtual std::string getName(){};
    virtual std::string toString(){};
    virtual void run(){};
    virtual void clearValues(){};
};