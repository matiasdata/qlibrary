// Parameters.h
#pragma once
#include <vector>

namespace QLibrary{

class Parameters
{
public:
    Parameters(){};
    virtual Parameters* clone() const = 0; // pure virtual function for cloning.
    virtual double Integral(double Time1, double Time2) const = 0; // pure virtual function for integration.
    virtual double IntegralSquare(double Time1,double Time2) const = 0; // pure virtual function for integration parameter squared.
    virtual double InverseIntegralSquare(double Value,
                                         double Time1,
                                         double TimeHigh, 
                                         double Tolerance = 1e-6) const; 
    // virtual function to compute a time Time2 such that IntegralSquare(Time1,Time2) = Value.
    virtual ~Parameters(){};
private:
};
// The Parameters class is an abstract base class that defines the interface for parameter objects.

class parametersConstant : public Parameters
{
public:
    parametersConstant(double Constant_);
    virtual Parameters* clone() const override; // override the clone function
    virtual double Integral(double Time1, double Time2) const override; // override the Integral function
    virtual double IntegralSquare(double Time1, double Time2) const override; // override the IntegralSquare function
    virtual ~parametersConstant() override = default;
private:
    double Constant; // constant parameter
};
// The parametersConstant class is a concrete implementation of the Parameters class that represents a constant parameter.


class parametersPiecewise : public Parameters
{
public:
    parametersPiecewise(const std::vector<double>& Time_, const std::vector<double>& Value_);
    virtual Parameters* clone() const override; // override the clone function
    virtual double Integral(double Time1, double Time2) const override;// override the Integral function
    virtual double IntegralSquare(double Time1, double Time2) const override; // override the IntegralSquare function
    virtual ~parametersPiecewise() override = default;
private:    
    std::vector<double> Time; // vector of time points
    std::vector<double> Value; // vector of parameter values
};

}
// The parametersPiecewise class is a concrete implementation of the Parameters class that represents a piecewise constant parameter.
