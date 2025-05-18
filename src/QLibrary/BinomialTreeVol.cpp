// BinomialTreeVol.cpp
#include <QLibrary/BinomialTreeVol.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace QLibrary
{

BinomialTreeVol::BinomialTreeVol(double Spot_, 
    const Wrapper<Parameters>& r_, 
    const Wrapper<Parameters>& d_, 
    const Wrapper<Parameters>& Volatility_,
    unsigned long Steps_,
    double Time_) : Spot(Spot_),
                    r(r_),
                    d(d_),
                    Volatility(Volatility_),
                    Steps(Steps_),
                    Time(Time_),
                    TreeBuilt(false),
                    Discounts(Steps) 
{
    Times.resize(Steps+1);
    Times[0] = 0.0;
    Times[Steps] = Time;
    VarianceByStep = Volatility->IntegralSquare(0.0,Time)/Steps;
    for(unsigned long i = 1; i < Steps; i++)
    {
        Times[i] = Volatility->InverseIntegralSquare(VarianceByStep,Times[i-1],Time);
    } 
}

void BinomialTreeVol::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    double InitialLogSpot = log(Spot);

    for(unsigned long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(i+1);
        double thisTime = Times[i];

        double movedLogSpot = InitialLogSpot + r->Integral(0.0, thisTime) - d->Integral(0.0,thisTime);
        movedLogSpot -= 0.5 * VarianceByStep * i; // equivalent to 0.5 * Volatility->Integral(0.0, thisTime);
        double std = std::sqrt(VarianceByStep);
        
        for(long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j+2, k++)
        {
            TheTree[i][k].first = std::exp(movedLogSpot + j * std);
        }
    }

    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r->Integral(Times[l], Times[l+1]));
    }
}

double BinomialTreeVol::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt) BuildTree();

    if (TheProduct.GetFinalTime() != Time)
    {
        throw std::invalid_argument("mismatched product in SimpleBinomialTree.");
    }

    for(long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j+2, k++)
    {
        TheTree[Steps][k].second = TheProduct.FinalPayoff(TheTree[Steps][k].first);
    }

    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = Times[i];
        
        for(long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j+2, k++)
        {
            double Spot = TheTree[index][k].first;
            double FutureDiscountedValue = 0.5*Discounts[index]*(TheTree[index+1][k].second + TheTree[index+1][k+1].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,FutureDiscountedValue);
        }
    }
    return TheTree[0][0].second;
}

// double BinomialTreeVol::InverseIntegralSquare(const Wrapper<Parameters>& param, 
//                              double IntegralSquareValue,
//                              double Time1,
//                              double TimeHigh, 
//                              double Tolerance)
// {
//     auto f = [param, Time1](double Time2)
//     {
//         return param->IntegralSquare(Time1,Time2);
//     };

//     return Bisection(IntegralSquareValue,Time1, TimeHigh,Tolerance,f);
// }

}