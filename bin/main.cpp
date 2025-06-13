//
// Created by sigris on 11.06.2025.
//

#include "lib/Metrics/DefaultMetric.h"
#include "lib/MetricsManager/MetricsManager.h"
#include "lib/MetricsWriters/FileWriter.h"
#include "iostream"
#include "vector"
#include "random"

int myRandom() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 10000);
    return dist(rng);
}

double mean(const std::vector<double>& nums) {
    double sum = 0.0;
    for (auto i : nums){
        sum += i;
    }
    return sum / nums.size();
}

std::pair<double, double> leastSquaresFit(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("The x and y dimensions must match and be > 0");
    }

    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
    size_t n = x.size();

    for (size_t i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double denominator = n * sumX2 - sumX * sumX;

    double k = (n * sumXY - sumX * sumY) / denominator;
    double b = (sumY - k * sumX) / n;

    return {k, b};
}

double secondsUntil2026() {
    using namespace std::chrono;

    auto now = system_clock::now();

    auto target_time = system_clock::from_time_t(std::mktime(new std::tm{
            .tm_year = 2026 - 1900,
            .tm_mon = 0,
            .tm_mday = 1,
            .tm_hour = 0,
            .tm_min = 0,
            .tm_sec = 0
    }));

    return duration<double>(target_time - now).count();
}


int main(int argc, char* argv[]){
    std::string file_path = argv[1];
    auto ptrWriter = std::make_shared<FileWriter>(file_path);
    MetricsManager metricsManager(ptrWriter);

    DefaultMetric<decltype(&myRandom)> metric1("myRandom", &myRandom);
    auto base_ptr = std::make_shared<decltype(metric1)>(metric1);
    metricsManager.addMetric(base_ptr);

    std::vector<double> for_mean = {1, 2, 3, 4, 5};
    DefaultMetric<decltype(&mean), const std::vector<double>&> metric2("mean", &mean, for_mean);
    auto mean_ptr = std::make_shared<decltype(metric2)>(metric2);
    metricsManager.addMetric(mean_ptr);

    std::vector<double> x = {2, 3, 5, 6, 11};
    std::vector<double> y = {32, 4, 12, 5, 8};
    DefaultMetric<decltype(&leastSquaresFit), const std::vector<double>&, const std::vector<double>&> metric3("lsf", &leastSquaresFit, x, y);
    auto lst_ptr = std::make_shared<decltype(metric3)>(metric3);
    metricsManager.addMetric(lst_ptr);

    DefaultMetric<decltype(&secondsUntil2026)> metric4("seconds_until_2026", &secondsUntil2026);
    auto sec_ptr = std::make_shared<decltype(metric4)>(metric4);
    metricsManager.addMetric(sec_ptr);

    metricsManager.runAllMetrics();
    metricsManager.writeAllMetric();
}