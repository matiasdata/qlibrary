// PayoffForward.cpp
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffForward.h>

namespace QLibrary{

PayoffForward::PayoffForward(double Strike_) : Strike{Strike_} {};

PayoffForward::PayoffForward(const std::vector<double>& Parameters)
{
    if (Parameters.size() != 1)
    {
        throw std::invalid_argument("PayoffForward requires only one parameter.");
    }
    Strike = Parameters[0];
    
    if (Strike < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}

double PayoffForward::operator()(double Spot) const
{
    return Spot - Strike;
}

Payoff* PayoffForward::clone() const { return new PayoffForward(*this);}

} // namespace QLibrary    