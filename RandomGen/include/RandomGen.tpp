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

