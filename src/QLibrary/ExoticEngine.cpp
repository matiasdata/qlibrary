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

void ExoticEngine::DoSimulation(MCStatistics<double>& TheGatherer, unsigned long NumberOfPaths)
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
}