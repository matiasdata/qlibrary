// BSCallTwo.h
#pragma once

namespace QLibrary
{

class BSCallTwo
{
public:
    BSCallTwo(double r_, double d_, double T_, double Spot_, double Strike_);
    double Price(double Vol) const;
    double Vega(double Vol) const;
private:
    double r;
    double d;
    double T;
    double Spot;
    double Strike;
};

} // namespace QLibrary