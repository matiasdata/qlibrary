// Payoff.cpp
#include <QLibrary/Payoff.h>
#include <algorithm>
#include <stdexcept>

/* PayoffCall Implementation
*/
namespace QLibrary{

PayoffCall::PayoffCall(double Strike_) : Strike{Strike_} 
{
    if (Strike < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}

PayoffCall::PayoffCall(const std::vector<double>& Parameters)
{
    if (Parameters.size() != 1)
    {
        throw std::invalid_argument("PayoffCall requires only one parameter.");
    }
    Strike = Parameters[0];
    
    if (Strike < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}


Payoff* PayoffCall::clone() const { return new PayoffCall(*this);}

/* PayoffPut Implementation
*/

PayoffPut::PayoffPut(double Strike_) : Strike{Strike_} 
{
    if (Strike < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}

PayoffPut::PayoffPut(const std::vector<double>& Parameters)
{
    if (Parameters.size() != 1)
    {
        throw std::invalid_argument("PayoffPut requires only one parameter.");
    }
    Strike = Parameters[0];
    if (Strike < 0)
    {
        throw std::invalid_argument("Strike must be non-negative.");
    }
}


Payoff* PayoffPut::clone() const { return new PayoffPut(*this);}


/* PayoffDoubleDigital Implementation 
*/

PayoffDoubleDigital::PayoffDoubleDigital(double LowerLevel_, double UpperLevel_) : LowerLevel{LowerLevel_}, UpperLevel{UpperLevel_} 
{
    if (LowerLevel < 0 || UpperLevel < 0)
    {
        throw std::invalid_argument("Strikes must be non-negative.");
    }
    if (LowerLevel > UpperLevel)
    {
        throw std::invalid_argument("First argument must be smaller than the second one.");
    }

}

PayoffDoubleDigital::PayoffDoubleDigital(const std::vector<double>& Parameters)
{
    if (Parameters.size() != 2)
    {
        throw std::invalid_argument("PayoffDoubleDigital requires two parameters.");
    }
    LowerLevel = Parameters[0];
    UpperLevel = Parameters[1];
    
    if (LowerLevel < 0 || UpperLevel < 0)
    {
        throw std::invalid_argument("Strikes must be non-negative.");
    }
    if (LowerLevel > UpperLevel)
    {
        throw std::invalid_argument("First argument must be smaller than the second one.");
    }

}

Payoff* PayoffDoubleDigital::clone() const { return new PayoffDoubleDigital(*this);}

}