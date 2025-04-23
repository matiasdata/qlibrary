// PathDependentBarrier.cpp
#include <QLibrary/PathDependentBarrier.h>


PathDependentBarrier::PathDependentBarrier(const MyArray& LookAtTimes_,
                                            const Wrapper<Payoff>& ThePayoff_, 
                                            const Wrapper<Barrier>& TheBarrier_,
                                            double Rebate_)
                                            :
                                            PathDependent(LookAtTimes_),
                                            ThePayoff(ThePayoff_),
                                            NumberOfTimes(LookAtTimes_.size()), 
                                            TheBarrier(TheBarrier_),
                                            Rebate(Rebate_) {}
                                                            
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
    std::optional<unsigned long> touch_barrier = (*TheBarrier)(SpotValues);
    if (touch_barrier.has_value())
    {
        unsigned long TouchIndex = touch_barrier.value();
        GeneratedCashFlows[0].TimeIndex = TouchIndex;
        GeneratedCashFlows[0].Amount = Rebate;
    } 
    else
    {
        unsigned long lastIndex = GetLookAtTimes().size()-1;
        GeneratedCashFlows[0].TimeIndex = lastIndex;
        GeneratedCashFlows[0].Amount = (*ThePayoff)(SpotValues[lastIndex]);
    }
    return 1UL;
}
                                                                                                                   