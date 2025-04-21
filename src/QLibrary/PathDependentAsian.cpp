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

/* 
PathDependentAsian(const MyArray& LookAtTimes_, double DeliveryTime_, const Wrapper<Payoff>& ThePayoff_):
        1) Calls the PathDependent constructor with the LookAtTimes (times at where the spot is sampled).
        2) Initialises the DeliveryTime, time at which the payoff is delivered, usually (but not always) the last time of sampling.
        3) Stores NumberOfTimes which is just the size of LookAtTimes for efficiency as it will be used several times for averaging.

virtual unsigned long MaxNumberOfCashFlows() const override: return just 1 (1UL), because only cashflow is at delivery time.

virtual MyArray PossibleCashFlowTimes() const override: returns an array of size one, with the time of the one cashflow (DeliveryTime).
 
virtual unsigned long CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const override:
Computes the cashflow of an Asian Option:
        1) Computes the sum of the spot values using the .sum() method from MyArray (uses std::accumulate).
        2) Computes the mean by dividing by the NumberOfTimes (length of the SpotValues array).
        3) Computes the CashFlow and stores it in the GeneratedCashFlows array. (SpotValues and CashFlows are owned by the ExoticEngine).
        
*/