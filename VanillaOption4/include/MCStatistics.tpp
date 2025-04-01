#include <MCStatistics.h>

MCStatisticsMean::MCStatisticsMean() : sum(0.0), count(0) {}

void MCStatisticsMean::addSample(double sample) 
{
    sum += sample;
    count++;
}

std::map<std::string,std::vector<double>> MCStatisticsMean::getResults() const 
{
    std::map<std::string,std::vector<double>> results; // create a dictionary to store results
    results["mean"]; // create a key "mean" in the dictionary
    results["mean"].resize(1); // create a 1D vector with 1 column
    results["mean"][0] = (count > 0) ? sum / count : 0.0; // calculate mean
    return results;
}

MCStatistics* MCStatisticsMean::clone() const 
{
    return new MCStatisticsMean(*this);
}

/* MCStatisticsVariance Implementation */

MCStatisticsVariance::MCStatisticsVariance() : sum(0.0), count(0), sum2(0.0) {}

void MCStatisticsVariance::addSample(double sample) {
    sum += sample;
    sum2 += sample * sample;
    count++;
}

std::map<std::string,std::vector<double>> MCStatisticsVariance::getResults() const 
{
    std::map<std::string,std::vector<double>> results; // create a dictionary to store results
    results["mean"]; // create a key "mean" in the dictionary
    results["mean"].resize(1); // create a 1D vector with 1 column
    results["mean"][0] = (count > 0) ? sum / count : 0.0; // calculate mean
    results["variance"]; // create a key "variance" in the dictionary
    results["variance"].resize(1); // create a 1D vector with 1 column
    results["variance"][0] = (count > 1) ? (sum2 - sum * sum / count) / (count - 1) : 0.0; // calculate variance
    return results;
}

MCStatistics* MCStatisticsVariance::clone() const 
{
    return new MCStatisticsVariance(*this);
}

/* Convergence Table Implementation */

ConvergenceTable::ConvergenceTable(const Wrapper<MCStatistics>& inner_) 
    : inner(inner_), count{0}, stoppingPoint{1} // Start at 1 for powers of 2
{
}

void ConvergenceTable::addSample(double sample) 
{
    inner->addSample(sample);
    count++;

    // Check if count has reached a power of 2
    if (count == stoppingPoint) 
    {
        stoppingPoint *= 2; // Move to next power of 2
        std::map<std::string, std::vector<double>> thisResult = inner->getResults();

        for (const auto& data : thisResult) 
        {
            results[data.first].push_back(data.second[0]); // Store first statistic value
        }
    }
}

std::map<std::string, std::vector<double>> ConvergenceTable::getResults() const 
{
    return results;
}

MCStatistics* ConvergenceTable::clone() const 
{
    return new ConvergenceTable(*this);
}