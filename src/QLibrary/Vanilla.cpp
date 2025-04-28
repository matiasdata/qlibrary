#include <QLibrary/Vanilla.h>

namespace QLibrary{

VanillaOption::VanillaOption(const Wrapper<Payoff>& ThePayoff_, double Expiry_) : Expiry{Expiry_}, ThePayoff{ThePayoff_} {}

double VanillaOption::OptionPayoff(double Spot) const{
    return (*ThePayoff)(Spot);
}

double VanillaOption::GetExpiry() const { return Expiry;}

}