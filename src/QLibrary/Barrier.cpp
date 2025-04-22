#include <QLibrary/Barrier.h>

// Barrier Base class implementation

std::optional<unsigned long> Barrier::operator()(const MyArray& SpotValues) const
{
    for(unsigned long i = 0; i < SpotValues.size(); ++i)
    {
        if(checkOnce(SpotValues[i])) return i;
    }
    return std::nullopt;
}

// UpOutBarrier class implementation
UpOutBarrier::UpOutBarrier(double Barrier_) : Barrier(Barrier_) {};

bool UpOutBarrier::checkOnce(double Spot) const
{
    return (Spot >= Barrier);
}

Barrier* UpOutBarrier::clone() const
{
    return new UpOutBarrier(*this);
} 