// PayoffForward.h
#pragma once

#include <QLibrary/Payoff.h>

namespace QLibrary
{

class PayoffForward : public Payoff
{
public:
    PayoffForward(double Strike_);
    virtual double operator()(double Spot) const;
    virtual Payoff* clone() const;
    virtual ~PayoffForward(){};
private:
    double Strike;
};

} // namespace QLibrary