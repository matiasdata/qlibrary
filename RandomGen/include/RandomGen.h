#pragma once

#include <MyArray.h>

class RandomBase
{
public:
    RandomBase(unsigned long Dimensionality_);
    inline unsigned long getDimesionality() const;
    virtual RandomBase* clone() const = 0;
    virtual void getUniforms(MyArray& variates) = 0;
    virtual void skip(unsigned long numberOfPaths) = 0;
    virtual void setSeed(unsigned long Seed) = 0;
    virtual void reset() = 0;
    
    virtual void getGaussians(MyArray& variates);
    virtual void resetDimesionality(unsigned long NewDimesionality);

private:
    unsigned long Dimensionality;
};

unsigned long RandomBase::getDimesionality() const 
{
    return Dimensionality;
}