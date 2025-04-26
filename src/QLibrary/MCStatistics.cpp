// MCStatistics.cpp
#include <QLibrary/MCStatistics.h>

/* MCStatisticsMean Implementation */

MCStatisticsMean::MCStatisticsMean() : sum(0.0), count(0) {}


void MCStatisticsMean::addSample(double sample) 
{
    sum += sample;
    count++;
}


std::map<std::string,double> MCStatisticsMean::getResults() const 
{
    std::map<std::string,double> results; // create a dictionary to store results
    results["mean"]= (count > 0) ? sum / count : 0.0; // calculate mean
    return results;
}


MCStatistics* MCStatisticsMean::clone() const 
{
    return new MCStatisticsMean(*this);
}


void MCStatisticsMean::reset()
{
    sum = 0;
    count = 0;
}

/* MCStatisticsVariance Implementation */

MCStatisticsVariance::MCStatisticsVariance() : sum(0.0), count(0), sum2(0.0) {}


void MCStatisticsVariance::addSample(double sample) {
    sum += sample;
    sum2 += sample * sample;
    count++;
}


std::map<std::string,double> MCStatisticsVariance::getResults() const 
{
    std::map<std::string,double> results; // create a dictionary to store results
    results["mean"] = (count > 0) ? sum / count : 0.0; // calculate mean
    results["variance"] = (count > 1) ? (sum2 - sum * sum / count) / (count - 1) : 0.0; // calculate variance
    return results;
}


MCStatistics* MCStatisticsVariance::clone() const 
{
    return new MCStatisticsVariance(*this);
}


void MCStatisticsVariance::reset()
{
    sum = 0;
    sum2 = 0;
    count = 0;
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
        std::map<std::string,double> thisResult = inner->getResults();

        for (const auto& data : thisResult) 
        {
            results[data.first].push_back(data.second); // Store first statistic value
            results[data.first].push_back(count); // Store count
        }
    }
}


std::map<std::string,double> ConvergenceTable::getResults() const 
{
    return inner->getResults();
}



std::map<std::string,std::vector<double>> ConvergenceTable::getConvergenceTable() const 
{
    std::map<std::string, std::vector<double>> tmp = results; // Create a copy of the results
    std::map<std::string,double> thisResult = inner->getResults();
    for (const auto& data : thisResult) 
    {
        tmp[data.first].push_back(data.second); // Store first statistic value
        tmp[data.first].push_back(count); // Store count
    }
    return tmp; // Return the copy of the results with added latest results so far.
}


MCStatistics* ConvergenceTable::clone() const 
{
    return new ConvergenceTable(*this);
}


void ConvergenceTable::reset()
{
    inner->reset();
    results.clear();
}