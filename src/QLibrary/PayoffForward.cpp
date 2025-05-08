// PayoffForward.cpp
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffForward.h>

namespace QLibrary{

PayoffForward::PayoffForward(double Strike_) : Strike{Strike_} {};

double PayoffForward::operator()(double Spot) const
{
    return Spot - Strike;
}

Payoff* PayoffForward::clone() const { return new PayoffForward(*this);}

} // namespace QLibrary    