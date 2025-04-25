// PathDependentBarrier.cpp
#include <QLibrary/PathDependentBarrier.h>


PathDependentBarrier::PathDependentBarrier(const MyArray& LookAtTimes_,
                                            const Wrapper<Payoff>& ThePayoff_, 
                                            const Wrapper<Barrier>& TheBarrier_)
                                            :
                                            PathDependent(LookAtTimes_),
                                            ThePayoff(ThePayoff_), 
                                            TheBarrier(TheBarrier_), 
                                            NumberOfTimes(LookAtTimes_.size()) {}
                                                            
unsigned long PathDependentBarrier::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MyArray PathDependentBarrier::PossibleCashFlowTimes() const
{
    MyArray tmp(GetLookAtTimes());
    return tmp;
}


unsigned long PathDependentBarrier::CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const
{
    std::optional<CashFlow> cf = TheBarrier->evaluate(SpotValues, ThePayoff);
    if (cf.has_value())
    {
        GeneratedCashFlows[0] = cf.value();
        return 1UL;
    }
    return 0UL; // No cashflow (e.g. knock-in barrier never triggered)
}

PathDependent* PathDependentBarrier::clone() const 
{
    return new PathDependentBarrier(*this);
}
                                                                                                                   