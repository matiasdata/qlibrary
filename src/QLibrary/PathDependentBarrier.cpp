// PathDependentBarrier.cpp
#include <QLibrary/PathDependentBarrier.h>

PathDependentBarrier::PathDependentBarrier(const MyArray& LookAtTimes_, 
                                                            const Wrapper<Payoff>& ThePayoff_,
                                                            double Barrier_,
                                                            double Rebate_) 
                                                            :
                                                            PathDependent(LookAtTimes_),
                                                            ThePayoff(ThePayoff_),
                                                            NumberOfTimes(LookAtTimes_.size()), 
                                                            Barrier(Barrier_),
                                                            Rebate(Rebate_) {}
                                                            
unsigned long PathDependentBarrier::MaxNumberOfCashFlows() const
{
    return NumberOfTimes;
}

MyArray PathDependentBarrier::PossibleCashFlowTimes() const
{
    MyArray tmp(this->GetLookAtTimes());
    return tmp;
}

 unsigned long PathDependentBarrier::CashFlows(const MyArray& SpotValues, std::vector<CashFlow>& GeneratedCashFlows) const
 {

 }

                                                                                                                    