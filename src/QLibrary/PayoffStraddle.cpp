// PayoffStraddle.cpp
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffStraddle.h>

namespace QLibrary{

PayoffStraddle::PayoffStraddle(double Strike_) : theCall(new PayoffCall(Strike_)), thePut(new PayoffPut(Strike_)){}

double PayoffStraddle::operator()(double Spot) const
{
    return theCall->operator()(Spot) + thePut->operator()(Spot);
}

Payoff* PayoffStraddle::clone() const { return new PayoffStraddle(*this);}


} // namespace QLibrary    