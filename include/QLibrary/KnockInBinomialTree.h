// KnockInBinomialTree.h
#pragma once

#include <QLibrary/TreeKnockIn.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/MyArray.h>
#include <QLibrary/Wrapper.h>
#include <vector>

namespace QLibrary{

class KnockInBinomialTree
{
struct Node
{
    double spot;
    double valueKnockedIn;
    double valueNotKnockedIn;
};

public:
    KnockInBinomialTree(double Spot_, 
                        const Wrapper<Parameters>& r_, 
                        const Wrapper<Parameters>& d_, 
                        double Volatility_,
                        unsigned long Steps_,
                        double Time_);   
    double GetThePrice(const TreeKnockIn& TheProduct, bool KnockedIn = false);
    ~KnockInBinomialTree(){};
protected:
    void BuildTree(); // protected can be accessed by inherited classes

private:
    double Spot;
    const Wrapper<Parameters> r;
    const Wrapper<Parameters> d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
    std::vector<std::vector<Node>> TheTree; // one tree for the spot and the option values
    MyArray Discounts;
};

}