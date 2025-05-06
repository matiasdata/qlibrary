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

}