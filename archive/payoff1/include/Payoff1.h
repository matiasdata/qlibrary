#pragma once 

class Payoff
{
public:
    enum OptionType{call, put};
    Payoff(double Strike_, OptionType TheOptionType_);
    double operator()(double Spot) const;
private:
    double Strike;
    OptionType TheOptionType;
};

#include "Payoff1.tpp"