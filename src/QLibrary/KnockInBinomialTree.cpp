// KnockInBinomialTree.cpp
#include <QLibrary/KnockInBinomialTree.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace QLibrary
{

KnockInBinomialTree::KnockInBinomialTree(double Spot_, 
    const Wrapper<Parameters>& r_, 
    const Wrapper<Parameters>& d_, 
    double Volatility_,
    unsigned long Steps_,
    double Time_,
    double BarrierLevel_) : Spot(Spot_),
                    r(r_),
                    d(d_),
                    Volatility(Volatility_),
                    Steps(Steps_),
                    Time(Time_),
                    BarrierLevel(BarrierLevel_),
                    TreeBuilt(false),
                    Discounts(Steps) {}

void KnockInBinomialTree::BuildTree()
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
            TheTree[i][k].resize(3);
            TheTree[i][k][SPOT] = std::exp(movedLogSpot + j * std);
            TheTree[i][k][VALUE_KNOCKED_IN] = 0.0;
            TheTree[i][k][VALUE_NOT_KNOCKED_IN] = 0.0;
        }
    }

    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r->Integral((l*Time)/Steps, ((l+1)*Time)/Steps));
    }
}

double KnockInBinomialTree::GetThePrice(const TreeProduct& TheProduct, bool KnockedIn)
{
    if (!TreeBuilt) BuildTree();

    if (TheProduct.GetFinalTime() != Time)
    {
        throw std::invalid_argument("mismatched product in KnockInBinomialTree.");
    }

    for(long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j+2, k++)
    {
        TheTree[Steps][k][VALUE_KNOCKED_IN] = TheProduct.FinalPayoff(TheTree[Steps][k][SPOT]);
        TheTree[Steps][k][VALUE_NOT_KNOCKED_IN] = 0.0;
    }
    double q = 0.5;
    
    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = (index*Time)/Steps;
        
        for(long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j+2, k++)
        {
            // case 1 : already KNOCKED_IN at index.
            double thisSpot = TheTree[index][k][SPOT];
            double FutureDiscountedValue = Discounts[index]*((1-q) * TheTree[index+1][k][VALUE_KNOCKED_IN] 
                                                        + q * TheTree[index+1][k+1][VALUE_KNOCKED_IN]);
            TheTree[index][k][VALUE_KNOCKED_IN] = TheProduct.PreFinalValue(thisSpot,ThisTime,FutureDiscountedValue);

            // case 2: NOT_KNOCKED_IN at index.
            int knockedInUp = (TheTree[index+1][k+1][0] <= BarrierLevel)? VALUE_KNOCKED_IN : VALUE_NOT_KNOCKED_IN;
            int knockedInDown = (TheTree[index+1][k][0] <= BarrierLevel)? VALUE_KNOCKED_IN : VALUE_NOT_KNOCKED_IN;
            FutureDiscountedValue = Discounts[index]*((1-q) * TheTree[index+1][k][knockedInUp] + q * TheTree[index+1][k+1][knockedInDown]);
            TheTree[index][k][VALUE_NOT_KNOCKED_IN] = FutureDiscountedValue;
        }
    }
    double result = KnockedIn? TheTree[0][0][VALUE_KNOCKED_IN] : TheTree[0][0][VALUE_NOT_KNOCKED_IN] ;
    return result;
}

}