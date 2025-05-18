// BinomialTreeVol.h
#pragma once

#include <QLibrary/TreeProduct.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/MyArray.h>
#include <QLibrary/Wrapper.h>
#include <vector>

namespace QLibrary{

class BinomialTreeVol
{
public:
    BinomialTreeVol(double Spot_, 
                        const Wrapper<Parameters>& r_, 
                        const Wrapper<Parameters>& d_, 
                        const Wrapper<Parameters>& Volatility_,
                        unsigned long Steps_,
                        double Time_);   
    double GetThePrice(const TreeProduct& TheProduct);
    ~BinomialTreeVol(){};
protected:
        void BuildTree(); // protected can be accessed by inherited classes

private:
    double Spot;
    const Wrapper<Parameters> r;
    const Wrapper<Parameters> d;
    const Wrapper<Parameters> Volatility;
    unsigned long Steps;
    double Time;
    std::vector<double> Times;
    bool TreeBuilt;
    std::vector<std::vector<std::pair<double,double>>> TheTree; // one tree for the spot and the option values
    MyArray Discounts;
    double VarianceByStep;

};

double InverseIntegralSquare(const Parameters& param, 
                             double Time1,
                             double IntegralSquareValue,
                             double TimeHigh, 
                             double Tolerance = 1e-6) const;

}