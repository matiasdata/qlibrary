// TreeKnockIn.h
#pragma once
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary{



class TreeKnockIn
{
public: 
    enum class BarrierType {Up, Down};
    TreeKnockIn(double FinalTime_,const Wrapper<Payoff>& ThePayoff_, double BarrierLevel_,
        BarrierType TheBarrierType_ = BarrierType::Up);
    double FinalPayoff(double Spot, bool KnockedIn) const;
    double PreFinalValue(double Spot, double Time, double DiscountedFutureValue, bool KnockedIn) const;
    bool isKnockedIn(double Spot, bool previouslyKnockedIn) const;
    ~TreeKnockIn(){};
    double GetFinalTime() const {return FinalTime;};

private:
    double FinalTime;
    Wrapper<Payoff> ThePayoff;
    const double BarrierLevel;
    BarrierType TheBarrierType;
    
};

} //namespace QLibrary
