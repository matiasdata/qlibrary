// ExoticEngine.h
#pragma once

#include <QLibrary/Wrapper.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/PathDependent.h>
#include <QLibrary/MCStatistics.h>
#include <vector>

class ExoticEngine
{
public:
    ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Wrapper<Parameters>& r_);
    virtual void GetOnePath(MyArray& SpotValues) = 0;
    void DoSimulation(MCStatistics<double>& TheGatherer, unsigned long NumberOfPaths);
    virtual ~ExoticEngine(){};
    double DoOnePath(const MyArray& SpotValues) const;
private:
    Wrapper<PathDependent> TheProduct;
    Wrapper<Parameters> r;
    MyArray Discounts;
    mutable std::vector<CashFlow> TheseCashFlows;
};
