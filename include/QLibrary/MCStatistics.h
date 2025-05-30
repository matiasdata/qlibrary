#pragma once
#include <vector>
#include <map>
#include <string>
#include <QLibrary/Wrapper.h>

namespace QLibrary{

class MCStatistics {
public:
    MCStatistics(){};
    virtual void addSample(double sample) = 0;
    virtual std::map<std::string,double> getResults() const = 0;
    virtual MCStatistics* clone() const = 0;
    virtual void reset() = 0;
    virtual ~MCStatistics(){};
private:
};


class MCStatisticsMean : public MCStatistics {
public:
    MCStatisticsMean();
    virtual void addSample(double sample) override;
    virtual std::map<std::string,double> getResults() const override;
    virtual MCStatistics* clone() const override;
    virtual void reset() override;
    virtual ~MCStatisticsMean() override = default;
private:
    double sum;
    unsigned long count;
};


class MCStatisticsVariance : public MCStatistics {
public:
    MCStatisticsVariance();
    virtual void addSample(double sample) override;
    virtual std::map<std::string,double> getResults() const override;
    virtual MCStatistics* clone() const override;
    virtual void reset() override;
    virtual ~MCStatisticsVariance() override = default;
private:
    double sum;
    unsigned long count;
    double sum2;
};

class ConvergenceTable : public MCStatistics {
public:
    ConvergenceTable(const Wrapper<MCStatistics>& inner);
    virtual void addSample(double sample) override;
    virtual std::map<std::string, double> getResults() const override;
    virtual std::map<std::string, std::vector<double>> getConvergenceTable() const;
    virtual MCStatistics* clone() const override;
    virtual void reset() override;
    virtual ~ConvergenceTable() override = default;
private:
    Wrapper<MCStatistics> inner;
    std::map<std::string, std::vector<double>> results;
    unsigned long count;
    unsigned long stoppingPoint;
};

}