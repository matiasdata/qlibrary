// PathDependentAsian.cpp
#include <QLibrary/PathDependentAsian.h>

PathDependentAsian::PathDependentAsian(const MyArray& LookAtTimes_,
                                        double DeliveryTime_,
                                        const Wrapper<Payoff>& ThePayoff_) 
                                        : 
                                        PathDependent(LookAtTimes_),
                                         DeliveryTime(DeliveryTime_),
                                         ThePayoff(ThePayoff_),
                                         NumberOfTimes(LookAtTimes_.size()) {}

unsigned long PathDependentAsian::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MyArray PathDependentAsian::PossibleCashFlowTimes() const
{
    MyArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentAsian::CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const
{
    double sum = SpotValues.sum();
    double mean = sum/NumberOfTimes;
    GeneratedCashFlows[0].TimeIndex = 0UL;
    GeneratedCashFlows[0].Amount = (*ThePayoff)(mean);
    return 1UL;
}

PathDependent* PathDependentAsian::clone() const
{
    return new PathDependentAsian(*this);
}