// PayoffType.h
#pragma once
#include <algorithm>

namespace QLibrary
{

class PayoffCallType
{
public:
    PayoffCallType(double Strike_) : Strike{Strike_} {}
    inline double operator()(double Spot) const
    {
        return std::max(Spot-Strike,0.0);
    }
    ~PayoffCallType() = default;

private:
    double Strike;
};

// CRTP derived classes
class PayoffPutType
{
public:
    PayoffPutType(double Strike_) : Strike{Strike_} {}
    inline double operator()(double Spot) const
    {
        return std::max(Strike-Spot,0.0);
    }
    ~PayoffPutType() = default;
private:
    double Strike;

};


} // namespace QLibrary