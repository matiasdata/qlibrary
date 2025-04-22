// PathDependentDiscreteKnockout.cpp
#include <QLibrary/PathDependentDiscreteKnockout.h>

PathDependentDiscreteKnockout::PathDependentDiscreteKnockout(const MyArray& LookAtTimes_, 
                                                            const Wrapper<Payoff>& ThePayoff_) 
                                                            :
                                                            PathDependent(LookAtTimes_),
                                                            ThePayoff(ThePayoff_),
                                                            NumberOfTimes(LookAtTimes_.size()) {}
                                                            
unsigned long PathDependentDiscreteKnockout::MaxNumberOfCashFlows() const
{
    return NumberOfTimes;
}

MyArray PathDependentDiscreteKnockout::PossibleCashFlowTimes() const
{
    MyArray tmp(this->GetLookAtTimes());
    return tmp;
}

                                                                                                                    