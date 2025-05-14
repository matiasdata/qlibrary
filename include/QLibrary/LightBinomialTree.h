// LightBinomialTree.h
#pragma once

#include <QLibrary/TreeProduct.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/MyArray.h>
#include <QLibrary/Wrapper.h>
#include <vector>

namespace QLibrary{

class LightBinomialTree
{
public:
LightBinomialTree(double Spot_, 
                        const Wrapper<Parameters>& r_, 
                        const Wrapper<Parameters>& d_, 
                        double Volatility_,
                        unsigned long Steps_,
                        double Time_);   
    double GetThePrice(const TreeProduct& TheProduct);
    ~LightBinomialTree(){};
private:
    double Spot;
    const Wrapper<Parameters> r;
    const Wrapper<Parameters> d;
    double Volatility;
    unsigned long Steps;
    double Time;
    std::vector<std::pair<double,double>> Layer;
    MyArray Discounts;
};

}