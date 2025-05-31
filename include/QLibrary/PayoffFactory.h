// PayoffFactory.h
#pragma once
#include <QLibrary/Payoff.h>
#include <string>
#include <map>
#include <vector>

namespace QLibrary
{


class PayoffFactory
{
public:
    typedef Payoff* (*CreatePayoffFunction)(const std::vector<double>&);
    static PayoffFactory& Instance();
    void RegisterPayoff(std::string, CreatePayoffFunction);
    Payoff* CreatePayoff(std::string PayoffId, const std::vector<double>& Parameters);
    ~PayoffFactory(){};
private:
    std::map<std::string, CreatePayoffFunction> TheCreatorFunctions;
    PayoffFactory(){}; // Constructor is private.
    PayoffFactory(const PayoffFactory&){};
    PayoffFactory& operator=(const PayoffFactory&) {return *this;}
};


} // namespace QLibrary