// LightBinomialTree.cpp
#include <QLibrary/LightBinomialTree.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace QLibrary
{

LightBinomialTree::LightBinomialTree(double Spot_, 
    const Wrapper<Parameters>& r_, 
    const Wrapper<Parameters>& d_, 
    double Volatility_,
    unsigned long Steps_,
    double Time_) : Spot(Spot_),
                    r(r_),
                    d(d_),
                    Volatility(Volatility_),
                    Steps(Steps_),
                    Time(Time_),
                    Discounts(Steps) 
{
    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r->Integral((l*Time)/Steps, ((l+1)*Time)/Steps));
    }
    Layer.resize(Steps+1);
}

double LightBinomialTree::GetThePrice(const TreeProduct& TheProduct)
{

    if (TheProduct.GetFinalTime() != Time)
    {
        throw std::invalid_argument("mismatched product in SimpleBinomialTree.");
    }

    double InitialLogSpot = log(Spot);
    double movedLogSpot = InitialLogSpot + r->Integral(0.0, Time) - d->Integral(0.0,Time);
    movedLogSpot -= 0.5 * Volatility * Volatility * Time;
    double std = Volatility * std::sqrt(Time/Steps);

    for(long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j+2, k++)
    {
        Layer[k] = TheProduct.FinalPayoff(std::exp(movedLogSpot + j * std));
    }

    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;

        double ThisTime = (index*Time)/Steps;
        double movedLogSpot = InitialLogSpot + r->Integral(0.0, ThisTime) - d->Integral(0.0,ThisTime);
        movedLogSpot -= 0.5 * Volatility * Volatility * ThisTime;

        for(long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j+2, k++)
        {
            double Spot = std::exp(movedLogSpot + j * std);
            double FutureDiscountedValue = 0.5*Discounts[index]*(Layer[k] + Layer[k+1]);
            Layer[k] = TheProduct.PreFinalValue(Spot,ThisTime,FutureDiscountedValue);
        }
    }
    return Layer[0];
}

}