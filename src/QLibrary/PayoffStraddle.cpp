// PayoffStraddle.cpp
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffStraddle.h>

namespace QLibrary{

PayoffStraddle::PayoffStraddle(double Strike_) : theCall(new PayoffCall(Strike_)), thePut(new PayoffPut(Strike_)){}

PayoffStraddle::PayoffStraddle(const std::vector<double>& Parameters) : theCall(new PayoffCall(Parameters.at(0))), thePut(new PayoffPut(Parameters.at(0)))
{
    if (Parameters.size() != 1)
    {
        throw std::invalid_argument("PayoffStraddle requires only one parameter.");
    }
    
    if (Parameters[0] < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}

double PayoffStraddle::operator()(double Spot) const
{
    return theCall->operator()(Spot) + thePut->operator()(Spot);
}

Payoff* PayoffStraddle::clone() const { return new PayoffStraddle(*this);}


} // namespace QLibrary    