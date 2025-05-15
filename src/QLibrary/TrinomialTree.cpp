// BinomialTree.cpp
#include <QLibrary/TrinomialTree.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace QLibrary
{

SimpleTrinomialTree::SimpleTrinomialTree(double Spot_, 
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
                    TreeBuilt(false),
                    Discounts(Steps) {}

void SimpleTrinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    double InitialLogSpot = log(Spot);

    for(unsigned long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(2*i+1);
        double thisTime = (i*Time)/Steps;

        double movedLogSpot = InitialLogSpot + r->Integral(0.0, thisTime) - d->Integral(0.0,thisTime);
        movedLogSpot -= 0.5 * Volatility * Volatility * thisTime;
        double std = Volatility * std::sqrt(Time/Steps); 
        static const double INVSQRT2 = 1.0/std::sqrt(2.0);
        
        for(long j = -static_cast<long>(2*i), k = 0; j <= static_cast<long>(2*i); j = j+2, k++)
        {
            TheTree[i][k].first = std::exp(movedLogSpot + j * INVSQRT2 * std);
        }
    }

    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r->Integral((l*Time)/Steps, ((l+1)*Time)/Steps));
    }
}

double SimpleTrinomialTree::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt) BuildTree();

    if (TheProduct.GetFinalTime() != Time)
    {
        throw std::invalid_argument("mismatched product in SimpleTrinomialTree.");
    }

    for(long j = -static_cast<long>(2*Steps), k = 0; j <= static_cast<long>(2*Steps); j = j+2, k++)
    {
        TheTree[Steps][k].second = TheProduct.FinalPayoff(TheTree[Steps][k].first);
    }

    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = (index*Time)/Steps;
        
        for(long j = -static_cast<long>(2*index), k = 0; j <= static_cast<long>(2*index); j = j+2, k++)
        {
            double Spot = TheTree[index][k].first;
            double FutureDiscountedValue = Discounts[index]*(0.25 * TheTree[index+1][k].second +
                                                             0.5 * TheTree[index+1][k+1].second +
                                                            0.25 * TheTree[index+1][k+2].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,FutureDiscountedValue);
        }
    }
    return TheTree[0][0].second;
}

}