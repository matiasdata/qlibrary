// BlackScholesFormulas.cpp
#include <QLibrary/BlackScholesFormulas.h>
#include <cmath>
#include <stdexcept>

namespace QLibrary
{

double NormalCDF(double x)
{
    static const double SQRT2 = std::sqrt(2.0); // static to avoid recalculating
    return 0.5 * (1.0 + std::erf(x / SQRT2));
}

const static double OneOverRootTwoPi = 0.398942280401433;

double NormalDensity(double x)
{
   return OneOverRootTwoPi*exp(-x*x/2);
}

double BlackScholesCall(double Spot,
                       double Strike,
                       double r,
                       double d,
                       double Volatility,
                       double Expiry)
{
    if (Spot <= 0.0 || Strike <= 0.0 || Expiry <= 0.0 || Volatility < 0.0)
    {
        throw std::invalid_argument("Invalid arguments in BlackScholesCall");
    }
    double d1 = (std::log(Spot/Strike) + (r - d + 0.5 * Volatility * Volatility) * Expiry) / (Volatility * std::sqrt(Expiry));
    double d2 = d1 - Volatility * std::sqrt(Expiry);
    return Spot * std::exp(-d*Expiry) * NormalCDF(d1) - Strike * std::exp(-r*Expiry) * NormalCDF(d2);
}

double BlackScholesPut(double Spot,
                       double Strike,
                       double r,
                       double d,
                       double Volatility,
                       double Expiry)
{
    if (Spot <= 0.0 || Strike <= 0.0 || Expiry <= 0.0 || Volatility < 0.0)
    {
        throw std::invalid_argument("Invalid arguments in BlackScholesPut");
    }
    double d1 = (std::log(Spot/Strike) + (r - d + 0.5 * Volatility * Volatility) * Expiry) / (Volatility * std::sqrt(Expiry));
    double d2 = d1 - Volatility * std::sqrt(Expiry);
    return Strike * std::exp(-r*Expiry) * NormalCDF(-d2) - Spot * std::exp(-d*Expiry) * NormalCDF(-d1);
}

double BlackScholesCallVega( double Spot,
                        double Strike,
                        double r,
                        double d,
                        double Vol,
                        double Expiry)
{
    double standardDeviation = Vol*sqrt(Expiry);
    double moneyness = log(Spot/Strike);
    double d1 =( moneyness + (r-d)*Expiry + 0.5 * standardDeviation*standardDeviation)/standardDeviation;
    return Spot*exp(-d*Expiry) * sqrt(Expiry)*NormalDensity(d1);
}

} // namespace QLibrary