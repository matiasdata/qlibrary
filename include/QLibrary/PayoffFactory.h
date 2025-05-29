// PayoffFactory.h
#pragma once
#include <QLibrary/Payoff.h>
#include <string>
#include <map>

namespace QLibrary
{


class PayoffFactory
{
public:
    typedef Payoff* (*CreatePayoffFunction)(double);
    static PayoffFactory& Instance();
    void RegisterPayoff(std::string, CreatePayoffFunction);
    Payoff* CreatePayoff(std::string PayoffId, double Strike);
    ~PayoffFactory(){};
private:
    std::map<std::string, CreatePayoffFunction> TheCreatorFunctions;
    PayoffFactory(){}; // Constructor is private.
    PayoffFactory(const PayoffFactory&){};
    PayoffFactory& operator=(const PayoffFactory&) {return *this;}
};


} // namespace QLibrary