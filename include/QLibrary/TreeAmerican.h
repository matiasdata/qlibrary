// TreeAmerican.h
#pragma once
#include <QLibrary/TreeProduct.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Cloneable.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary{

class TreeAmerican : public virtual TreeProduct, public Cloneable<TreeProduct,TreeAmerican>
{
public: 
    TreeAmerican(double FinalTime_,const Wrapper<Payoff>& ThePayoff_);
    virtual double FinalPayoff(double Spot) const override;
    virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const override;
    virtual ~TreeAmerican() override = default;

private:
    Wrapper<Payoff> ThePayoff;
};

} //namespace QLibrary

/* Unused variables are not named because some compilers issue a warning if a variable is named but left unused. */