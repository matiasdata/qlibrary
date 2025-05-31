// PayoffConstructible.h
#pragma once


#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffFactory.h>
#include <iostream>
#include <string>
#include <vector>

namespace QLibrary{

template <typename T>
class PayoffHelper
{
public:
    PayoffHelper(std::string);
    static Payoff* Create(const std::vector<double>& Parameters);
};

template <typename T>
PayoffHelper<T>::PayoffHelper(std::string PayoffId)
{
    PayoffFactory& thePayoffFactory = PayoffFactory::Instance();
    thePayoffFactory.RegisterPayoff(PayoffId, PayoffHelper<T>::Create);
}

template <typename T>
Payoff* PayoffHelper<T>::Create(const std::vector<double>& Parameters)
{
    return new T(Parameters);
}

} // namespace QLibrary