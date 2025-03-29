#pragma once
#include <Payoff.h>


class VanillaOption
{
public:
    VanillaOption(const Payoff& ThePayoff_, double Expiry_);
    VanillaOption(const VanillaOption& other);
    VanillaOption& operator=(const VanillaOption& other);
    ~VanillaOption();
    double GetExpiry() const;
    double OptionPayoff(double Spot) const;

private:
    Payoff* ThePayoffPtr;
    double Expiry;
};


#include "Vanilla.tpp"


/*
Rule of Three: Notice that the class VanillaOption includes an assignment operator (operator=) and a copy constructor 
whereas Payoff classes did not. This is because while the compiler generates these methods, they are inappropriate. 
The compiler default methods will generate shallow copies as opposed to a deep copy. When there is no memory allocation (pointers)
this is ok, but when there is memory allocation then a shallow copy simply copies the addresses to new pointers to the same address. 
If we copy in this way, a copy of an object will point to the same adress and thus any modification done on the copy will affect the
original object, which is certainly not what we want. We want a new object pointing to a copy of the payoff, with the same information but
stored elsewhere so that if it is modified then the original object is not affected. 
Another problem if that if any of the two objects gets out of scope, the others pointed payoff will be deleted, and this will lead
to a fatal error. A non-default destructor is also needed to guarantee that we delete the memory allocated appropriately and do not 
incur into memory leaks. 
The "Rule of Three" says that whenever we write a class that involves any one of (non-default) assigment operator, a copy constructor or 
a destructor, then all three are needed. 
*/