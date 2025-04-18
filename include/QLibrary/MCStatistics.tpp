#include <QLibrary/MCStatistics.h>

template<typename T>
MCStatisticsMean<T>::MCStatisticsMean() : sum(0.0), count(0) {}

template<typename T>
void MCStatisticsMean<T>::addSample(T sample) 
{
    sum += sample;
    count++;
}

template<typename T>
std::map<std::string,T> MCStatisticsMean<T>::getResults() const 
{
    std::map<std::string,T> results; // create a dictionary to store results
    results["mean"]= (count > 0) ? sum / count : 0.0; // calculate mean
    return results;
}

template<typename T>
MCStatistics<T>* MCStatisticsMean<T>::clone() const 
{
    return new MCStatisticsMean(*this);
}

/* MCStatisticsVariance Implementation */
template<typename T>
MCStatisticsVariance<T>::MCStatisticsVariance() : sum(0.0), count(0), sum2(0.0) {}

template<typename T>
void MCStatisticsVariance<T>::addSample(T sample) {
    sum += sample;
    sum2 += sample * sample;
    count++;
}

template<typename T>
std::map<std::string,T> MCStatisticsVariance<T>::getResults() const 
{
    std::map<std::string,T> results; // create a dictionary to store results
    results["mean"] = (count > 0) ? sum / count : 0.0; // calculate mean
    results["variance"] = (count > 1) ? (sum2 - sum * sum / count) / (count - 1) : 0.0; // calculate variance
    return results;
}

template<typename T>
MCStatistics<T>* MCStatisticsVariance<T>::clone() const 
{
    return new MCStatisticsVariance(*this);
}

/* Convergence Table Implementation */

template<typename T>
ConvergenceTable<T>::ConvergenceTable(const Wrapper<MCStatistics<T>>& inner_) 
    : inner(inner_), count{0}, stoppingPoint{1} // Start at 1 for powers of 2
{
}

template<typename T>
void ConvergenceTable<T>::addSample(T sample) 
{
    inner->addSample(sample);
    count++;

    // Check if count has reached a power of 2
    if (count == stoppingPoint) 
    {
        stoppingPoint *= 2; // Move to next power of 2
        std::map<std::string,T> thisResult = inner->getResults();

        for (const auto& data : thisResult) 
        {
            results[data.first].push_back(data.second); // Store first statistic value
            results[data.first].push_back(count); // Store count
        }
    }
}

template<typename T>
std::map<std::string,T> ConvergenceTable<T>::getResults() const 
{
    return inner->getResults();
}


template<typename T>
std::map<std::string, std::vector<T>> ConvergenceTable<T>::getConvergenceTable() const 
{
    std::map<std::string, std::vector<T>> tmp = results; // Create a copy of the results
    std::map<std::string,T> thisResult = inner->getResults();
    for (const auto& data : thisResult) 
    {
        tmp[data.first].push_back(data.second); // Store first statistic value
        tmp[data.first].push_back(count); // Store count
    }
    return tmp; // Return the copy of the results with added latest results so far.
}

template<typename T>
MCStatistics<T>* ConvergenceTable<T>::clone() const 
{
    return new ConvergenceTable(*this);
}