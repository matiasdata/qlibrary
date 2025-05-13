// TreeBarrier.h
#pragma once
#include <QLibrary/TreeProduct.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>
#include <QLibrary/BinomialTree.h>

namespace QLibrary{

enum class BarrierType {Up, Down};

class TreeOutBarrier : public TreeProduct
{
public: 
    TreeOutBarrier(double FinalTime_,const Wrapper<Payoff>& ThePayoff_, double BarrierLevel_,
        BarrierType TheBarrierType_ = BarrierType::Up);
    virtual double FinalPayoff(double Spot) const override;
    virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const override;
    virtual TreeProduct* clone() const override;
    virtual ~TreeOutBarrier() override = default;
    double PriceInBarrier(SimpleBinomialTree& tree); // calculate the price of the barrier In option, not part of the TreeProduct interface.

private:
    Wrapper<Payoff> ThePayoff;
    const double BarrierLevel;
    BarrierType TheBarrierType;
};

} //namespace QLibrary
