#include <Vanilla.h>

VanillaOption::VanillaOption(const PayoffBridge& ThePayoff_, double Expiry_) : Expiry{Expiry_}, ThePayoff{ThePayoff_} {}

double VanillaOption::OptionPayoff(double Spot) const{
    return ThePayoff(Spot);
}

double VanillaOption::GetExpiry() const { return Expiry;}
