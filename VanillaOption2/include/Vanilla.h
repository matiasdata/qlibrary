#pragma once
#include <PayoffBridge.h>


class VanillaOption
{
public:
    VanillaOption(const PayoffBridge& ThePayoff_, double Expiry_);
    double GetExpiry() const;
    double OptionPayoff(double Spot) const;

private:
    PayoffBridge ThePayoff;
    double Expiry;
};


#include "Vanilla.tpp"

/* Super simple VanillaOption class, no need to write copy constructors, assigment operators or destructors
as these are taken care by the PayoffBridge. 
*/