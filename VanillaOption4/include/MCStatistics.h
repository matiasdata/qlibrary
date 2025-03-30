#pragma once
#include <vector>

class MCStatistics {
public:
    MCStatistics(){};
    virtual void addSample(double sample) = 0;
    virtual std::vector<std::vector<double>> getResults() const = 0;
    virtual MCStatistics* clone() const = 0;
    virtual ~MCStatistics(){};
private:
};

class MCStatisticsMean : public MCStatistics {
public:
    MCStatisticsMean();
    virtual void addSample(double sample);
    virtual std::vector<std::vector<double>> getResults() const;
    virtual MCStatistics* clone() const;
private:
    double sum;
    unsigned long count;
};

#include <MCStatistics.tpp>