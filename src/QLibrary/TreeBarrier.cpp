// TreeBarrier.cpp

#include <QLibrary/TreeBarrier.h>
#include <algorithm>

namespace QLibrary{

TreeBarrier::TreeBarrier(double FinalTime_,
                        const Wrapper<Payoff>& ThePayoff_, double Level_) :
                         TreeProduct(FinalTime_), 
                         ThePayoff(ThePayoff_),
                         Level(Level_)
                         {};

double TreeBarrier::FinalPayoff(double Spot) const
{
    return Spot < Level? (*ThePayoff)(Spot) : 0.0;
}

double TreeBarrier::PreFinalValue(double Spot, 
                                    double //Time
                                    , double DiscountedFutureValue) const
{
    return Spot < Level? DiscountedFutureValue : 0.0;
}

TreeProduct* TreeBarrier::clone() const
{
    return new TreeBarrier(*this);
}

} // namespace QLibrary