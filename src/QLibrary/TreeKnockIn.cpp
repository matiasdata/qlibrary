// TreeKnockIn.cpp

#include <QLibrary/TreeKnockIn.h>
#include <stdexcept>
#include <algorithm>

namespace QLibrary{

TreeKnockIn::TreeKnockIn(double FinalTime_,
                        const Wrapper<Payoff>& ThePayoff_, double BarrierLevel_, BarrierType TheBarrierType_) :
                         FinalTime(FinalTime_), 
                         ThePayoff(ThePayoff_),
                         BarrierLevel(BarrierLevel_),
                         TheBarrierType(TheBarrierType_)
                         {};

double TreeKnockIn::FinalPayoff(double Spot, bool KnockedIn) const
{
    return KnockedIn? (*ThePayoff)(Spot) : 0.0;
}

double TreeKnockIn::PreFinalValue(double Spot, 
                                    double //Time
                                    , double DiscountedFutureValue
                                    , bool KnockedIn) const
{
    return KnockedIn? std::max((*ThePayoff)(Spot),DiscountedFutureValue) : DiscountedFutureValue;
}

bool TreeKnockIn::isKnockedIn(double Spot, bool previouslyKnockedIn) const
{
    if (previouslyKnockedIn) {return true;}
    else
    {
        switch(TheBarrierType)
        {
            case BarrierType::Up:
                return Spot >= BarrierLevel;
            case BarrierType::Down:
                return Spot <= BarrierLevel;
            default:
                throw std::invalid_argument("Invalid barrier type");
        }
    }
}


} // namespace QLibrary