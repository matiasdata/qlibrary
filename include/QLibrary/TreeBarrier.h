// TreeBarrier.h
#pragma once
#include <QLibrary/TreeProduct.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary{

class TreeBarrier : public TreeProduct
{
public: 
    TreeBarrier(double FinalTime_,const Wrapper<Payoff>& ThePayoff_);
    virtual double FinalPayoff(double Spot) const override;
    virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const override;
    virtual TreeProduct* clone() const override;
    virtual ~TreeBarrier() override = default;

private:
    Wrapper<Payoff> ThePayoff;

};

} //namespace QLibrary