#include <QLibrary/SimpleMC.h>
#include <cmath>


void SimpleMonteCarlo(const VanillaOption& theOption,
    double Spot,
    const Parameters& Vol,
    const Parameters& r,
    unsigned long NumberOfPaths,
    MCStatistics& gatherer,
    RandomBase& rg)
{
    double Expiry = theOption.GetExpiry();
    double variance = Vol.IntegralSquare(0, Expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * std::exp(r.Integral(0,Expiry) + itoCorrection);
    double thisSpot = 0;
    double discounting = std::exp(-r.Integral(0, Expiry));

    MyArray arr(1);

    for(unsigned long i = 0; i < NumberOfPaths; i++)
    {
        rg.getGaussians(arr);
        double thisGaussian = arr[0];
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayoff = theOption.OptionPayoff(thisSpot);
        gatherer.addSample(thisPayoff * discounting);
    }
    return;
}