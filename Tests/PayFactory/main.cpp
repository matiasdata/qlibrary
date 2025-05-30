// Tests/Payfactory/main.cpp

#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffConstructible.h>
#include <QLibrary/PayoffFactory.h>
#include <string>
#include <iostream>

int main()
{
    double Strike;
    std::string PayoffId;

    std::cout << "Enter strike:\n";
    std::cin >> Strike;
    std::cout << "\nEnter the payoff Id:\n";
    std::cin >> PayoffId;

    QLibrary::Payoff* PayoffPtr = QLibrary::PayoffFactory::Instance().CreatePayoff(PayoffId,Strike);

    if(PayoffPtr != nullptr)
    {
        double Spot;
        std::cout << "\nspot\n";
        std::cin >> Spot;
        std::cout << "\n" << PayoffPtr->operator()(Spot) << "\n";
        delete PayoffPtr;
    }
    return 0;
}