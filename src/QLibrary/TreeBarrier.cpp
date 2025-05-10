// TreeBarrier.cpp

#include <QLibrary/TreeBarrier.h>
#include <algorithm>

namespace QLibrary{

TreeBarrier::TreeBarrier(double FinalTime_,
                        const Wrapper<Payoff>& ThePayoff_) :
                         TreeProduct(FinalTime_), 
                         ThePayoff(ThePayoff_),
                         {};

double TreeBarrier::FinalPayoff(double Spot) const
{
    return (*ThePayoff)(Spot);
}

double TreeBarrier::PreFinalValue(double Spot, 
                                    double //Time
                                    , double DiscountedFutureValue) const
{
    return std::max((*ThePayoff)(Spot), DiscountedFutureValue);
}

TreeProduct* TreeBarrier::clone() const
{
    return new TreeBarrier(*this);
}

} // namespace QLibrary