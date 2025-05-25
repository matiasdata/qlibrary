// TreeBarrier.cpp

#include <QLibrary/TreeBarrier.h>
#include <QLibrary/TreeEuropean.h>
#include <stdexcept>
#include <algorithm>

namespace QLibrary{

TreeOutBarrier::TreeOutBarrier(double FinalTime_,
                        const Wrapper<Payoff>& ThePayoff_, double BarrierLevel_, BarrierType TheBarrierType_) :
                         TreeProduct(FinalTime_), 
                         ThePayoff(ThePayoff_),
                         BarrierLevel(BarrierLevel_),
                         TheBarrierType(TheBarrierType_)
                         {};

double TreeOutBarrier::FinalPayoff(double Spot) const
{
    switch(TheBarrierType)
    {
        case BarrierType::Up:
            return Spot <= BarrierLevel? (*ThePayoff)(Spot) : 0.0;
        case BarrierType::Down:
            return Spot >= BarrierLevel? (*ThePayoff)(Spot) : 0.0;
        default:
            throw std::invalid_argument("Invalid barrier type");
    }
}

double TreeOutBarrier::PreFinalValue(double Spot, 
                                    double //Time
                                    , double DiscountedFutureValue) const
{
    switch(TheBarrierType)
    {
        case BarrierType::Up:
            return Spot <= BarrierLevel? DiscountedFutureValue : 0.0;
        case BarrierType::Down:
            return Spot >= BarrierLevel? DiscountedFutureValue : 0.0;
        default:
            throw std::invalid_argument("Invalid barrier type");
    }
}

TreeProduct* TreeOutBarrier::clone() const
{
    return new TreeOutBarrier(*this);
}

double TreeOutBarrier::PriceInBarrier(SimpleBinomialTree& tree) {
    TreeEuropean european(GetFinalTime(), ThePayoff);
    //TreeOutBarrier knockOut(GetFinalTime(), ThePayoff, BarrierLevel, TheBarrierType);
    
    double europeanPrice = tree.GetThePrice(european);
    double knockOutPrice = tree.GetThePrice(*this);
    
    return europeanPrice - knockOutPrice;
    }

} // namespace QLibrary