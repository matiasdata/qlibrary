// RandomGen.tpp
#include <RandomGen.h>
#include <boost/math/distributions/normal.hpp>
#include <limits>

constexpr double EPS = std::numeric_limits<double>::epsilon(); // ~2.22e-16


double inverseCumulativeNormal(double p) {
    boost::math::normal dist(0.0, 1.0); // standard normal distribution
    return quantile(dist, p); // returns x such that P(X ≤ x) = p
}

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



RandomMLCG::RandomMLCG(unsigned long Dimensionality_, std::uint64_t Seed_) : RandomBase(Dimensionality_), InnerGenerator{Seed_}, InitialSeed{Seed_} {}

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