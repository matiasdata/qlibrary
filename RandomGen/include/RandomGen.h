#pragma once

#include <MyArray.h>

class RandomBase
{
public:
    RandomBase(unsigned long Dimensionality_) : Dimensionality{Dimensionality_} {};
    inline unsigned long getDimesionality() const;
    virtual RandomBase* clone() const = 0;
    virtual void getUniforms(MyArray& variates) = 0;
    virtual void skip(unsigned long numberOfPaths) = 0;
    virtual void setSeed(unsigned long Seed) = 0;
    virtual void reset() = 0;
    
    virtual void getGaussians(MyArray& variates);
    virtual void resetDimensionality(unsigned long newDimensionality);

private:
    unsigned long Dimensionality;
};

unsigned long RandomBase::getDimesionality() const 
{
    return Dimensionality;
}

/* Note that we define the interface for GetUniforms and GetGaussians via a reference to an array.
The reason we do this is that we do not wish to waste time copying arrays. Also remember that arrays 
of dynamic size generally involve dynamic memory allocation, i.e. new, and therefore are quite slow
to create and to destroy.
*/