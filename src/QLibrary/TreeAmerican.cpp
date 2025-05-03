// TreeAmerican.cpp

#include <QLibrary/TreeAmerican.h>

namespace QLibrary{

TreeAmerican::TreeAmerican(double FinalTime_,const Wrapper<Payoff>& ThePayoff_) : TreeProduct(FinalTime_), ThePayoff(ThePayoff_) {};

double TreeAmerican::FinalPayoff(double Spot) const
{
    return (*ThePayoff)(Spot);
}

double TreeAmerican::PreFinalValue(double Spot, 
                                    double //Time,
                                    double DiscountedFutureValue) const
{
    return std::max((*ThePayoff)(Spot), DiscountedFutureValue);
}

} // namespace QLibrary