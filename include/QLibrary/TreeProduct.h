// TreeProduct.h
#pragma once

namespace QLibrary{

class TreeProduct
{
public:
    TreeProduct() = delete;
    TreeProduct(double FinalTime_) : FinalTime(FinalTime_) {};
    virtual double FinalPayoff(double Spot) const = 0;
    virtual double PreFinalValue(double Spot, double Time, double DiscountedFutureValue) const = 0;
    virtual ~TreeProduct(){};
    virtual TreeProduct* clone() const = 0;
    double GetFinalTime() const {return FinalTime;};
private:
    double FinalTime;
};

} // namespace QLibrary

