#pragma once
#include <Wrapper.h>
#include <Payoff.h>


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


#include "Vanilla.tpp"

/* Super simple VanillaOption class, no need to write copy constructors, assigment operators or destructors
as these are taken care by the PayoffBridge. 
*/