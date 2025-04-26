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
    void DoSimulation(MCStatistics& TheGatherer, unsigned long NumberOfPaths);
    virtual ~ExoticEngine(){};
    double DoOnePath(const MyArray& SpotValues) const; 
private:
    Wrapper<PathDependent> TheProduct;
    Wrapper<Parameters> r;
    MyArray Discounts;
    mutable std::vector<CashFlow> TheseCashFlows;
};

/* 
ExoticEngine is an abstract simulation (MC) engine that can evaluate a PathDependent option (TheProduct).
It takes care of simulating the paths, performs the discounting, computes the DCF of each path. 

virtual void GetOnePath(MyArray& SpotValues) = 0: (pure virtual) computes one path of spot values. 

double DoOnePath(const MyArray& SpotValues) const: (not virtual) computes the discounted value of the option for one path of spot values.

void DoSimulation(MCStatistics<double>& TheGatherer, unsigned long NumberOfPaths):  performs a simulation of a number of paths.

Notice: mutable makes possible to modify TheseCashFlows even in const methods (like DoOnePath) while everything else has to remain the same.
*/