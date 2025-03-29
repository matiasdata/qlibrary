#include <PayoffBridge.h>

PayoffBridge::PayoffBridge(const Payoff& ThePayoff_)
{
    ThePayoffPtr = ThePayoff_.clone();
}

PayoffBridge::PayoffBridge(const PayoffBridge& other)
{
    ThePayoffPtr = other.ThePayoffPtr->clone();
}

PayoffBridge& PayoffBridge::operator=(const PayoffBridge& other)
{
    // if statement to prevent self-assignment crashes.
    if(this != &other){
        // Delete the existing Payoff, to prevent memory leaks.
        delete ThePayoffPtr;
        // Clone the Payoff object from the other PayoffBridge.
        ThePayoffPtr = other.ThePayoffPtr->clone(); 
    }
    // Return *this to return a reference to the object, for chained assignments.
    return *this; 
}

inline double PayoffBridge::operator()(double Spot) const{
    return (*ThePayoffPtr)(Spot);
}

PayoffBridge::~PayoffBridge()
{
    delete ThePayoffPtr;
}