#include <MCStatistics.h>

MCStatisticsMean::MCStatisticsMean() : sum(0.0), count(0) {}

void MCStatisticsMean::addSample(double sample) {
    sum += sample;
    count++;
}

std::vector<std::vector<double>> MCStatisticsMean::getResults() const {
    std::vector<std::vector<double>> results(1); // create a 2D vector with 1 row
    results[0].resize(1); // create a 1D vector with 1 column
    results[0][0] = (count > 0) ? sum / count : 0.0; // calculate mean
    return results;
}

MCStatistics* MCStatisticsMean::clone() const {
    return new MCStatisticsMean(*this);
}

