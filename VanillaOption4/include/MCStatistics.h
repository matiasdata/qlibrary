#pragma once
#include <vector>
#include <map>
#include <string>
#include <Wrapper.h>

template <typename T>
class MCStatistics {
public:
    MCStatistics(){};
    virtual void addSample(T sample) = 0;
    virtual std::map<std::string,T> getResults() const = 0;
    virtual MCStatistics<T>* clone() const = 0;
    virtual ~MCStatistics(){};
private:
};

template <typename T>
class MCStatisticsMean : public MCStatistics<T> {
public:
    MCStatisticsMean();
    virtual void addSample(T sample);
    virtual std::map<std::string,T> getResults() const;
    virtual MCStatistics<T>* clone() const;
private:
    double sum;
    unsigned long count;
};

template<typename T>
class MCStatisticsVariance : public MCStatistics<T> {
public:
    MCStatisticsVariance();
    virtual void addSample(T sample);
    virtual std::map<std::string,T> getResults() const;
    virtual MCStatistics<T>* clone() const;
private:
    double sum;
    unsigned long count;
    double sum2;
};

template <typename T>
class ConvergenceTable : public MCStatistics<T> {
public:
    ConvergenceTable(const Wrapper<MCStatistics<T>>& inner);
    virtual void addSample(T sample);
    virtual std::map<std::string, T> getResults() const;
    virtual std::map<std::string, std::vector<T>> getConvergenceTable() const;
    virtual MCStatistics<T>* clone() const;
private:
    Wrapper<MCStatistics<T>> inner;
    std::map<std::string, std::vector<T>> results;
    unsigned long count;
    unsigned long stoppingPoint;
};

#include <MCStatistics.tpp>