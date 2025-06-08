// RandomGen.h
#pragma once
#include <QLibrary/MyArray.h>
#include <cstdint>

namespace QLibrary{
class RandomBase
{
public:
    RandomBase(unsigned long Dimensionality_) : Dimensionality{Dimensionality_} {};
    inline unsigned long getDimensionality() const;
    virtual RandomBase* clone() const = 0;
    virtual void getUniforms(MyArray& variates) = 0;
    virtual void setSeed(std::uint64_t Seed) = 0;
    virtual void reset() = 0;

    virtual void skip(unsigned long numberOfPaths);
    virtual void getGaussians(MyArray& variates);
    virtual void resetDimensionality(unsigned long newDimensionality);
    virtual ~RandomBase(){};

private:
    unsigned long Dimensionality;
};

inline unsigned long RandomBase::getDimensionality() const 
{
    return Dimensionality;
}


/* Note that we define the interface for GetUniforms and GetGaussians via a reference to an array.
The reason we do this is that we do not wish to waste time copying arrays. Also remember that arrays 
of dynamic size generally involve dynamic memory allocation, i.e. new, and therefore are quite slow
to create and to destroy.
*/
/* Dimensionality is supposed to represent the number of random variables to simulate one path. */

class MLCG{
public:
    
    static inline constexpr std::uint64_t default_m = 4294967296;      // 2^32
    static inline constexpr std::uint64_t default_a = 1664525;
    static inline constexpr std::uint64_t default_c = 1013904223;

    explicit MLCG(std::uint64_t seed_ = 0,
                  std::uint64_t m_ = default_m,
                  std::uint64_t a_ = default_a,
                  std::uint64_t c_ = default_c)
        : seed{seed_}, m{m_}, a{a_}, c{c_} {};

    std::uint64_t getInteger() {
        seed = (a * seed + c) % m;
        return seed;
    }

    void resetSeed(std::uint64_t newSeed) {
        seed = newSeed;
    }

private:
    std::uint64_t seed;
    std::uint64_t m, a, c;
};

// Constants as constexpr for compile-time optimization
// Explicit constructor to avoid accidental implicit conversions

class RandomMLCG : public RandomBase
{
    public:
        RandomMLCG(unsigned long Dimensionality_, std::uint64_t Seed_ = 0);
        RandomMLCG(unsigned long Dimensionality_,
            std::uint64_t Seed_,
            std::uint64_t m_,
            std::uint64_t a_,
            std::uint64_t c_);
        virtual RandomBase* clone() const override;
        virtual void getUniforms(MyArray& variates) override;
        virtual void setSeed(std::uint64_t Seed) override;
        virtual void reset() override;
        virtual ~RandomMLCG() override = default;
        
    
    private:
        MLCG InnerGenerator;
        std::uint64_t InitialSeed;
        const double Reciprocal;
};

double inverseCumulativeNormal(double p);

}

/* A static variable inside a class is a variable that is shared across all instances of the class. For example, the default
 values for m, a and c of our MLCG are shared across al instances.
 
 The constexpr makes it a compile-time constant.

 The inline tells the compiler: this variable can have multiple definitions across translation units, 
 but they all refer to the same object.
 
 */