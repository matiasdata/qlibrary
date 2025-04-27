#pragma once
#include <Payoff.h>


class PayoffBridge
{
public:
    PayoffBridge(const Payoff& ThePayoff_);
    PayoffBridge(const PayoffBridge& other);
    PayoffBridge& operator=(const PayoffBridge& other);
    ~PayoffBridge();
    inline double operator()(double Spot) const;

private:
    Payoff* ThePayoffPtr;
};


#include "PayoffBridge.tpp"

/* A bridge class pattern is sort of a wrapper that has a pointer to a Payoff object, and takes care of 
all the memory handling of the Payoff, allowing the VanillaOption class to be much simpler.
Recall that in VanillaOption1, this class had to take care of all the memory handling of the Payoff it had as a member.
We had to add a non-default assignment, copy and destructor. 
*/

