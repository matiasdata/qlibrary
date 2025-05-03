// TreeEuropean.h
#pragma once
#include <QLibrary/TreeProduct.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Cloneable.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary{

class TreeEuropean : public TreeProduct
{
public: 
    TreeEuropean(double FinalTime_,const Wrapper<Payoff>& ThePayoff_);
    virtual double FinalPayoff(double Spot) const override;
    virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const override;
    virtual TreeProduct* clone() const override;
    virtual ~TreeEuropean() override = default;

private:
    Wrapper<Payoff> ThePayoff;
};

} //namespace QLibrary