#include <SimpleMC.h>
#include <Payoff.h>
#include <cmath>
#include <random>

double SimpleMonteCarlo(const VanillaOption& theOption,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPaths)
{
    double Expiry = theOption.GetExpiry();
    double variance = Vol * Vol * Expiry;
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * std::exp(r*Expiry + itoCorrection);
    double thisSpot = 0;
    double runningSum = 0;

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution d{0.0, 1.0};

    for(unsigned long i = 0; i < NumberOfPaths; i++)
    {
        double thisGaussian = d(gen);
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayoff = theOption.OptionPayoff(thisSpot);
        runningSum += thisPayoff;
    }

    double mean = runningSum/NumberOfPaths;
    mean *= std::exp(-r*Expiry);
    return mean;
}