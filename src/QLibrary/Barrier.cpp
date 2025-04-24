// Barrier.cpp
#include <QLibrary/Barrier.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/Wrapper.h>


// UpOutBarrier class implementation
UpOutBarrier::UpOutBarrier(double level_, double rebate_) : level(level_), rebate(rebate_) {};



std::optional<CashFlow> UpOutBarrier::evaluate(const MyArray& SpotValues,const Wrapper<Payoff>& ThePayoff) const
{
    
    for(unsigned long i = 0; i < SpotValues.size(); ++i)
    {
        if(SpotValues[i]>= level){
            return CashFlow(i,rebate);
        }
    }
    unsigned long last = SpotValues.size()-1;
    return CashFlow(last, ThePayoff->operator()(SpotValues[last]));
}

Barrier* UpOutBarrier::clone() const
{
    return new UpOutBarrier(*this);
} 