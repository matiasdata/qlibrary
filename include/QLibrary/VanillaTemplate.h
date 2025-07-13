// VanillaTemplate.h
#pragma once
#include <QLibrary/Wrapper.h>
#include <QLibrary/PayoffType.h>

namespace QLibrary{

template <typename PayoffType>
class Vanilla
{
public:
    Vanilla(const PayoffType& ThePayoff_, double Expiry_);
    double GetExpiry() const;
    inline double OptionPayoff(double Spot) const;

private:
    double Expiry;
    PayoffType ThePayoff;
};


template <typename PayoffType>
Vanilla<PayoffType>::Vanilla(const PayoffType& ThePayoff_, double Expiry_) : Expiry{Expiry_}, ThePayoff{ThePayoff_} {}


template <typename PayoffType>
double Vanilla<PayoffType>::OptionPayoff(double Spot) const
{
    return ThePayoff(Spot);
}

template <typename PayoffType>
double Vanilla<PayoffType>::GetExpiry() const { return Expiry;}

}
