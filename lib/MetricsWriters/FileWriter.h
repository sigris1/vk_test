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
    explicit FileWriter(std::string file_path);

    void printAllMetrics(const std::unordered_map<std::string, std::shared_ptr<Metric>> metrics) override;

    std::string getPrintedPlace() override;

    ~FileWriter()=default;
private:
    std::string file_path_;
    std::mutex file_mutex_;
};


