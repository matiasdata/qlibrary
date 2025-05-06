#pragma once

#include <QLibrary/TreeProduct.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/MyArray.h>
#include <QLibrary/Wrapper.h>
#include <vector>

namespace QLibrary{

class SimpleBinomialTree
{
public:
    SimpleBinomialTree(double Spot_, 
                        const Wrapper<Parameters>& r_, 
                        const Wrapper<Parameters>& d_, 
                        double Volatility_,
                        unsigned long Steps_,
                        double Time_);   
    double GetThePrice(const TreeProduct& TheProduct);

protected:
        void BuildTree(); // protected can be accessed by inherited classes

private:
    double Spot;
    const Wrapper<Parameters>& r;
    const Wrapper<Parameters>& d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
    std::vector<std::vector<std::pair<double,double>>> TheTree; // one tree for the spot and the option values
    MyArray Discounts;

};

}