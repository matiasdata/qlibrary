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
            TheTree[i][k].spot = std::exp(movedLogSpot + j * std);
            TheTree[i][k].valueKnockedIn = 0.0;
            TheTree[i][k].valueNotKnockedIn = 0.0;
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
        TheTree[Steps][k].valueKnockedIn = TheProduct.FinalPayoff(TheTree[Steps][k].spot);
        TheTree[Steps][k].valueNotKnockedIn = 0.0;
    }
    double q = 0.5;
    
    for(unsigned long i = 1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = (index*Time)/Steps;
        
        for(long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j+2, k++)
        {
            // case 1 : already KNOCKED_IN at index.
            double thisSpot = TheTree[index][k].spot;
            double FutureDiscountedValue = Discounts[index]*((1-q) * TheTree[index+1][k].valueKnockedIn 
                                                        + q * TheTree[index+1][k+1].valueKnockedIn);
            TheTree[index][k].valueKnockedIn = TheProduct.PreFinalValue(thisSpot,ThisTime,FutureDiscountedValue);

            // case 2: NOT_KNOCKED_IN at index.
            double valueKnockedInUp = (TheTree[index+1][k+1].spot <= BarrierLevel)? TheTree[index+1][k+1].valueKnockedIn : TheTree[index+1][k+1].valueNotKnockedIn;
            double valueKnockedInDown = (TheTree[index+1][k].spot <= BarrierLevel)? TheTree[index+1][k].valueKnockedIn : TheTree[index+1][k].valueNotKnockedIn;
            FutureDiscountedValue = Discounts[index]*((1-q) * valueKnockedInUp + q * valueKnockedInDown);
            TheTree[index][k].valueNotKnockedIn = FutureDiscountedValue; // if not knocked in there is no early exercise
        }
    }
    double result = KnockedIn? TheTree[0][0].valueKnockedIn : TheTree[0][0].valueNotKnockedIn;
    return result;
}

}