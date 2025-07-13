// Vanilla.h
#pragma once
#include <QLibrary/Wrapper.h>
#include <QLibrary/Payoff.h>

namespace QLibrary{

class VanillaOption
{
public:
    VanillaOption(const Wrapper<Payoff>& ThePayoff_, double Expiry_);
    double GetExpiry() const;
    double OptionPayoff(double Spot) const;

private:
    double Expiry;
    Wrapper<Payoff> ThePayoff;
};

}

/* Super simple VanillaOption class, no need to write copy constructors, assigment operators or destructors
as these are taken care by the Wrapper<Payoff>. 
*/