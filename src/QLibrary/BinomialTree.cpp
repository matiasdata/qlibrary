// BinomialTree.cpp
#include <QLibrary/BinomialTree.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace QLibrary
{

SimpleBinomialTree::SimpleBinomialTree(double Spot_, 
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

void SimpleBinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    double InitialLogSpot = log(Spot);

    for(unsigned long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(i+1);
        double thisTime = (i*Time)/Steps;

        double movedLogSpot = InitialLogSpot + r->Integral(0.0, thisTime) - d->Integral(0.0,thisTime);
        movedLogSpot -= 0.5 * Volatility * Volatility * thisTime;
        double std = Volatility * std::sqrt(Time/Steps);
        
        for(long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j+2, k++)
        {
            TheTree[i][k].first = std::exp(movedLogSpot + j * std);
        }
    }

    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r->Integral((l*Time)/Steps, ((l+1)*Time)/Steps));
    }
}

double SimpleBinomialTree::GetThePrice(const TreeProduct& TheProduct, bool Martingale)
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
    double dt = Time/Steps;
    double q = Martingale? (std::exp(0.5 * Volatility * Volatility * dt + Volatility * std::sqrt(dt)) - 1)/(std::exp(2 * Volatility * std::sqrt(dt))-1):0.5;
    
    if (Martingale) 
    {
        std::cout << "q = " << q << std::endl;
    }

    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = (index*Time)/Steps;
        
        for(long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j+2, k++)
        {
            double Spot = TheTree[index][k].first;
            double FutureDiscountedValue = Discounts[index]*((1-q) * TheTree[index+1][k].second + q * TheTree[index+1][k+1].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,FutureDiscountedValue);
        }
    }
    return TheTree[0][0].second;
}

}