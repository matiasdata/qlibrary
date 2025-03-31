#include <MCStatistics.h>

MCStatisticsMean::MCStatisticsMean() : sum(0.0), count(0) {}

void MCStatisticsMean::addSample(double sample) {
    sum += sample;
    count++;
}

std::map<std::string,std::vector<double>> MCStatisticsMean::getResults() const {
    std::map<std::string,std::vector<double>> results; // create a dictionary to store results
    results["mean"]; // create a key "mean" in the dictionary
    results["mean"].resize(1); // create a 1D vector with 1 column
    results["mean"][0] = (count > 0) ? sum / count : 0.0; // calculate mean
    return results;
}

MCStatistics* MCStatisticsMean::clone() const {
    return new MCStatisticsMean(*this);
}

