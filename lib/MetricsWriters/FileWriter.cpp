//
// Created by sigris on 10.06.2025.
//

#include "FileWriter.h"
#include "future"
#include "map"
#include "string"

FileWriter::FileWriter(std::string filepath)
        :filepath_(std::move(filepath))
        {}


void FileWriter::printAllMetrics(const std::unordered_map<std::string, std::shared_ptr<Metric>>& metrics){
    std::vector<std::future<std::string>> futures;

    for (const auto& i : metrics) {
        auto metric = i.second;
        futures.push_back(std::async(std::launch::async, [metric]() {
            return metric->toString();
        }));
    }

    std::lock_guard<std::mutex> lock(file_mutex_);
    std::ofstream file(filepath_, std::ios::app);
    if (!file) {
        std::cerr << "No such file: " << filepath_;
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    file << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    for (auto& fut : futures) {
        file << " " << fut.get();
    }

    file << "\n";
}

std::string FileWriter::getPrintedPlace() const{
    return filepath_;
}
