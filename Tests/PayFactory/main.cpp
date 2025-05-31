// Tests/Payfactory/main.cpp

#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffConstructible.h>
#include <QLibrary/PayoffFactory.h>
#include <string>
#include <iostream>
#include <vector>

int main()
{
    std::string PayoffId;

    int NumParams = 0;
    std::cout << "Enter the number of parameters required by your payoff:\n";
    std::cin >> NumParams;

    std::vector<double> Parameters(NumParams);
    for(int i = 0; i < NumParams; i++)
    {
        std::cout << "Enter parameter " << i+1 << std::endl;
        std::cin >> Parameters[i];
    }
    std::cout << "\nEnter the payoff Id:\n";
    std::cin >> PayoffId;

    QLibrary::Payoff* PayoffPtr = QLibrary::PayoffFactory::Instance().CreatePayoff(PayoffId,Parameters);

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