#pragma once

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
    virtual double operator()(double Spot) const;
    virtual Payoff* clone() const;
    virtual ~PayoffCall(){};
private:
    double Strike;
};

class PayoffPut : public Payoff
{
public:
    PayoffPut(double Strike_);
    virtual double operator()(double Spot) const;
    virtual Payoff* clone() const;
    virtual ~PayoffPut(){};
private:
    double Strike;
};

class PayoffDoubleDigital : public Payoff
{
public:
    PayoffDoubleDigital(double LowerLevel_, double UpperLevel_);
    virtual double operator()(double Spot) const;
    virtual Payoff* clone() const;
    virtual ~PayoffDoubleDigital(){};
private:
    double LowerLevel;
    double UpperLevel;
};
