#include <RandomGen.h>
#include <boost/math/distributions/normal.hpp>

double inverseCumulativeNormal(double p) {
    boost::math::normal dist(0.0, 1.0); // standard normal distribution
    return quantile(dist, p); // returns x such that P(X ≤ x) = p
}

void RandomBase::getGaussians(MyArray& variates)
{
    getUniforms(variates);

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
        variates[i] = static_cast<double>(InnerGenerator.getInteger()) * Reciprocal ;
    }
}

void RandomMLCG::setSeed(std::uint64_t Seed) {
    InitialSeed = Seed;
    InnerGenerator.resetSeed(Seed);
}

void RandomMLCG::reset() {
    InnerGenerator.resetSeed(InitialSeed);
}