#include <Payoff.h>
#include <algorithm>

/* PayoffCall Implementation
*/

PayoffCall::PayoffCall(double Strike_) : Strike{Strike_} {};

double PayoffCall::operator()(double Spot) const
{
    return std::max(Spot - Strike,0.0);
}

/* PayoffPut Implementation
*/

PayoffPut::PayoffPut(double Strike_) : Strike{Strike_} {};

double PayoffPut::operator()(double Spot) const
{
    return std::max(Strike - Spot,0.0);
}


/* PayoffDoubleDigital Implementation 
*/

PayoffDoubleDigital::PayoffDoubleDigital(double LowerLevel_, double UpperLevel_) : LowerLevel{LowerLevel_}, UpperLevel{UpperLevel_} {};

double PayoffDoubleDigital::operator()(double Spot) const
{
    double result = ((Spot < LowerLevel or Spot > UpperLevel)? 0.0 : 1.0);
    return result;
}
