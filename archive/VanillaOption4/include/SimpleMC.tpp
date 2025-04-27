#include <SimpleMC.h>
#include <cmath>
#include <random>

void SimpleMonteCarlo(const VanillaOption& theOption,
    double Spot,
    const Parameters& Vol,
    const Parameters& r,
    unsigned long NumberOfPaths,
    MCStatistics<double>& gatherer)
{
    double Expiry = theOption.GetExpiry();
    double variance = Vol.IntegralSquare(0, Expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * std::exp(r.Integral(0,Expiry) + itoCorrection);
    double thisSpot = 0;
    double discounting = std::exp(-r.Integral(0, Expiry));

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution d{0.0, 1.0};

    for(unsigned long i = 0; i < NumberOfPaths; i++)
    {
        double thisGaussian = d(gen);
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayoff = theOption.OptionPayoff(thisSpot);
        gatherer.addSample(thisPayoff * discounting);
    }
    return;
}