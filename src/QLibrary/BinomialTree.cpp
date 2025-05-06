#include <QLibrary/BinomialTree.h>
#include <cmath>

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
                    Discounts(Steps)
{
    TreeBuilt = false;
}

void SimpleBinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    double InitialLogSpot = log(Spot);

    for(unsigned long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(i+1);
        double thisTime = (i*Time)/Steps;

        double movedLogSpot = InitialLogSpot + r.Integral(0.0, thisTime) - q.Integral(0.0,thisTime);
        movedLogSpot -= 0.5 * Volatility * Volatility * thisTime;
        double std = Volatility * std::sqrt(Time/Steps);
        
        for(long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j+2, k++)
        {
            TheTree[i][k].first = std::exp(movedLogSpot + j * std);
        }
    }

    for(unsigned long l = 0; l < Steps; l++)
    {
        Discounts[l] = std::exp(-r.Integral((l*Time)/Steps, ((l+1)*Time)/Steps))
    }
}

}