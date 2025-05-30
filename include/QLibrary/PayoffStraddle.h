// PayoffStraddle.h
#pragma once

#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>

namespace QLibrary
{

class PayoffStraddle : public Payoff
{
public:
    PayoffStraddle(double Strike_);
    virtual double operator()(double Spot) const;
    virtual Payoff* clone() const;
    virtual ~PayoffStraddle();
private:
    PayoffCall* theCall;
    PayoffPut* thePut;
};

} // namespace QLibrary