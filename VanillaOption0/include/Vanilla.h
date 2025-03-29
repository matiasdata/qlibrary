#pragma once
#include <Payoff.h>


class VanillaOption
{
public:
    VanillaOption(Payoff& ThePayoff_, double Expiry_);
    double GetExpiry() const;
    double OptionPayoff(double Spot) const;

private:
    Payoff& ThePayoff;
    double Expiry;
};


#include "Vanilla.tpp"


/*
 The VanillaOption class stores a reference to a PayOff object which was defined
outside the class. This means that if we change that object then the pay-off of
the vanilla option will change. The vanilla option will not exist as independent
object in its own right but will instead always be dependent on the PayOff ob-
ject constructed outside the class. This is a recipe for trouble. 
*/