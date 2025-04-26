// ExoticEngine.cpp
#include <QLibrary/ExoticEngine.h>
#include <cmath>

ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Wrapper<Parameters>& r_) : TheProduct{TheProduct_}, r{r_}
{
    Discounts = TheProduct->PossibleCashFlowTimes();
    for(unsigned long i = 0; i < Discounts.size(); i++)
    {
        Discounts[i] = exp(-r->Integral(0.0,Discounts[i]));
    }
    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
}

void ExoticEngine::DoSimulation(MCStatistics& TheGatherer, unsigned long NumberOfPaths)
{
    MyArray SpotValues(TheProduct->GetLookAtTimes().size());
    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
    double ThisValue;
    for (unsigned long i =0; i < NumberOfPaths; ++i)
    {
        GetOnePath(SpotValues);
        ThisValue = DoOnePath(SpotValues);
        TheGatherer.addSample(ThisValue);
    }

}

double ExoticEngine::DoOnePath(const MyArray& SpotValues) const
{
    unsigned long NumberFlows = TheProduct->CashFlows(SpotValues,TheseCashFlows);
    double Value = 0.0;
    for(unsigned long i = 0; i < NumberFlows; ++i)
    {
        Value += TheseCashFlows[i].Amount * Discounts[TheseCashFlows[i].TimeIndex];
    }
    return Value;
}

/* 
ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Wrapper<Parameters>& r_): Constructor computes the discount factors at all possible times and resizes TheseCashFlows.

virtual void GetOnePath(MyArray& SpotValues) = 0: (pure virtual) computes one path of spot values (array passed by reference so no memory allocation inside). 

double DoOnePath(const MyArray& SpotValues) const: (not virtual) computes the discounted value of the option for one path of spot values.
For that:
        1) it uses the SpotValues (S_{t_1},...,S_{t_n}) (given as input, 
        previously computed) to update TheseCashFlows (passed by reference),
        using CashFlows from the PathDependent option.
        2) it uses the discounts (which were pre-computed in the constructor),
        to compute the discounted CashFlow of the option for one path.
        It does a for loop over the number of cashflows.
        3) returns the Value (discounted CashFlow of one path).

void DoSimulation(MCStatistics<double>& TheGatherer, unsigned long NumberOfPaths):  performs a simulation of a number of paths.
For that:
        does NumberOfPath simulations, 
        using GetOnePath followed by DoOnePath, 
        and gives the result (addSample) to the statistics gatherer.
*/