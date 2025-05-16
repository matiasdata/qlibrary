// BlackScholesFormulas.h

namespace QLibrary
{
double NormalCDF(double x);

double BlackScholesCall(double Spot,
                      double Strike,
                      double r,
                      double d,
                      double Volatility,
                      double Expiry);
double BlackScholesPut(double Spot,
                      double Strike,
                      double r,
                      double d,
                      double Volatility,
                      double Expiry);

} // namespace QLibrary