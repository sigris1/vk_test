//
// Created by sigris on 10.06.2025.
//

#pragma once

#include "Writer.h"

#include <utility>
#include "string"
#include "fstream"
#include "iostream"
#include "map"

class FileWriter : public Writer {
public:
    explicit FileWriter(std::string filepath);

    void printAllMetrics(const std::unordered_map<std::string, std::shared_ptr<Metric>>& metrics) override;

    std::string getPrintedPlace() const override;

    ~FileWriter()=default;
private:
    std::string filepath_;
    std::mutex file_mutex_;
};


