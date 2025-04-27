#include <Vanilla.h>

VanillaOption::VanillaOption(const Payoff& ThePayoff_, double Expiry_) : Expiry{Expiry_}
{
    ThePayoffPtr = ThePayoff_.clone();
}

VanillaOption::VanillaOption(const VanillaOption& other)
{
    Expiry = other.Expiry;
    ThePayoffPtr = other.ThePayoffPtr->clone();
}

VanillaOption& VanillaOption::operator=(const VanillaOption& other)
{
    // if statement to prevent self-assignment crashes.
    if(this != &other){
        // Copy the Expiry.
        Expiry = other.Expiry;
        // Delete the existing Payoff, to prevent memory leaks.
        delete ThePayoffPtr;
        // Clone the Payoff object from the other VanillaOption.
        ThePayoffPtr = other.ThePayoffPtr->clone(); 
    }
    // Return *this to return a reference to the object, for chained assignments.
    return *this; 
}

double VanillaOption::OptionPayoff(double Spot) const{
    return (*ThePayoffPtr)(Spot);
}

double VanillaOption::GetExpiry() const { return Expiry;}

VanillaOption::~VanillaOption()
{
    delete ThePayoffPtr;
}