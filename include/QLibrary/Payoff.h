#pragma once
#include <vector>

namespace QLibrary{

class Payoff
{
public:
    Payoff(){}; // constructor does not specify anything
    virtual double operator()(double Spot) const = 0;
    virtual Payoff* clone() const = 0; //virtual copy constructor
    virtual ~Payoff(){}; //destructor
private:

};

class PayoffCall : public Payoff
{
public:
    PayoffCall(double Strike_);
    PayoffCall(const std::vector<double>& Parameters);
    virtual inline double operator()(double Spot) const override;
    virtual Payoff* clone() const override;
    virtual ~PayoffCall() override {};
private:
    double Strike;
};

class PayoffPut : public Payoff
{
public:
    PayoffPut(double Strike_);
    PayoffPut(const std::vector<double>& Parameters);
    virtual inline double operator()(double Spot) const override;
    virtual Payoff* clone() const override;
    virtual ~PayoffPut() override {};
private:
    double Strike;
};

class PayoffDoubleDigital : public Payoff
{
public:
    PayoffDoubleDigital(double LowerLevel_, double UpperLevel_);
    PayoffDoubleDigital(const std::vector<double>& Parameters);
    virtual inline double operator()(double Spot) const override;
    virtual Payoff* clone() const override;
    virtual ~PayoffDoubleDigital() override {};
private:
    double LowerLevel;
    double UpperLevel;
};

inline double PayoffCall::operator()(double Spot) const {
        return std::max(Spot - Strike, 0.0);
}

inline double PayoffPut::operator()(double Spot) const
{
    return std::max(Strike - Spot,0.0);
}


inline double PayoffDoubleDigital::operator()(double Spot) const
{
    return (Spot < LowerLevel or Spot > UpperLevel)? 0.0 : 1.0;
}


} // namespace QLibrary