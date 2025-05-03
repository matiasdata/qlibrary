// TreeEuropean.cpp

#include <QLibrary/TreeEuropean.h>

namespace QLibrary{

TreeEuropean::TreeEuropean(double FinalTime_,const Wrapper<Payoff>& ThePayoff_) : TreeProduct(FinalTime_), ThePayoff(ThePayoff_) {};

double TreeEuropean::FinalPayoff(double Spot) const
{
    return (*ThePayoff)(Spot);
}

double TreeEuropean::PreFinalValue(double Spot,
                                     double //Time, 
                                     double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

} // namespace QLibrary