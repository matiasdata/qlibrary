// RandomGen.cpp
#include <QLibrary/RandomGen.h>
//#include <boost/math/distributions/normal.hpp>
#include <limits>
#include <stdexcept>

namespace QLibrary{

constexpr double EPS = std::numeric_limits<double>::epsilon(); // ~2.22e-16


// double inverseCumulativeNormal(double p) {
//     boost::math::normal dist(0.0, 1.0); // standard normal distribution
//     return quantile(dist, p); // returns x such that P(X ≤ x) = p
// }

void RandomBase::getGaussians(MyArray& variates)
{


    getUniforms(variates); // Supposed to overwrite everything

    for(unsigned long i = 0; i < variates.size(); i++)
    {
        double x = variates[i];
        variates[i] = inverseCumulativeNormal(x);
    }
}

void RandomBase::resetDimensionality(unsigned long newDimensionality)
{
    Dimensionality = newDimensionality;
}


void RandomBase::skip(unsigned long numberOfPaths) {
    MyArray tmp(getDimensionality());
    for (unsigned long i = 0; i < numberOfPaths; ++i) {
        getUniforms(tmp); // advance the generator by creating numberOfPaths samples of the required dimensionality.
    }
}



RandomMLCG::RandomMLCG(unsigned long Dimensionality_,
                        std::uint64_t Seed_) : 
                        RandomBase(Dimensionality_),
                        InnerGenerator(Seed_), 
                        InitialSeed(Seed_),
                        Reciprocal(1.0 / static_cast<double>(MLCG::default_m + 1)) {}




RandomMLCG::RandomMLCG(unsigned long Dimensionality_,
                        std::uint64_t Seed_,
                        std::uint64_t m_,
                        std::uint64_t a_,
                        std::uint64_t c_) : 
                        RandomBase(Dimensionality_),
                        InnerGenerator{Seed_, m_, a_, c_},
                        InitialSeed{Seed_},
                        Reciprocal{1.0 / static_cast<double>(m_ + 1)} {}

RandomBase* RandomMLCG::clone() const {
    return new RandomMLCG(*this);  // clone copy constructor
}

void RandomMLCG::getUniforms(MyArray& variates) {
    
    for (unsigned long i = 0; i < getDimensionality(); ++i) {
        // Normalize to [0,1) by dividing by modulus
        double u = static_cast<double>(InnerGenerator.getInteger() + 1) * Reciprocal;
        // Clamp
        u = std::clamp(u, EPS, 1.0 - EPS);
        variates[i] = u;
    }
}

void RandomMLCG::setSeed(std::uint64_t Seed) {
    InitialSeed = Seed;
    InnerGenerator.resetSeed(Seed);
}

void RandomMLCG::reset() {
    InnerGenerator.resetSeed(InitialSeed);
}





double inverseCumulativeNormal(double p)
{
    /* Peter Acklam inverse cumulative function for the standard normal distribution */
    
    /* Coefficients in rational approximations. */
    static const double a[] =
    {
        -3.969683028665376e+01,
        2.209460984245205e+02,
        -2.759285104469687e+02,
        1.383577518672690e+02,
        -3.066479806614716e+01,
        2.506628277459239e+00
    };

    static const double b[] =
    {
        -5.447609879822406e+01,
        1.615858368580409e+02,
        -1.556989798598866e+02,
        6.680131188771972e+01,
        -1.328068155288572e+01
    };

    static const double c[] =
    {
        -7.784894002430293e-03,
        -3.223964580411365e-01,
        -2.400758277161838e+00,
        -2.549732539343734e+00,
        4.374664141464968e+00,
        2.938163982698783e+00
    };

    static const double d[] =
    {
        7.784695709041462e-03,
        3.224671290700398e-01,
        2.445134137142996e+00,
        3.754408661907416e+00
    };
    static const double LOW = 0.02425;
    static const double HIGH = 0.97575;

    double q, r;

    errno = 0;

    if (p < 0 || p > 1)
    {
        throw std::domain_error("p must be in (0,1)");
    }

    else if (p < LOW)
    {
        /* Rational approximation for lower region */
        q = sqrt(-2*log(p));
        return (((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
               ((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
    }
    else if (p > HIGH)
    {
        /* Rational approximation for upper region */
        q  = sqrt(-2*log(1-p));
        return -(((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
                ((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
    }
    else
    {
        /* Rational approximation for central region */
            q = p - 0.5;
            r = q*q;
        return (((((a[0]*r+a[1])*r+a[2])*r+a[3])*r+a[4])*r+a[5])*q /
               (((((b[0]*r+b[1])*r+b[2])*r+b[3])*r+b[4])*r+1);
    }
}

}