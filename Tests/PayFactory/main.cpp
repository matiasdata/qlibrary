// Tests/Payfactory/main.cpp

#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffConstructible.h>
#include <QLibrary/PayoffFactory.h>
#include <string>
#include <iostream>
#include <vector>
#include <QLibrary/SimpleMC.h>

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
        double Vol_;
        double r_;
        double Expiry;
        unsigned long NumberOfPaths = 1000000;
        std::cout << "Enter the Spot:" << std::endl;
        std::cin >> Spot;
        std::cout << "Enter the Expiry:" << std::endl;
        std::cin >> Expiry;
        std::cout << "Enter the volatility:" << std::endl;
        std::cin >> Vol_;
        std::cout << "Enter the risk free rate:" << std::endl;
        std::cin >> r_;
        
        QLibrary::parametersConstant Vol{Vol_};
        QLibrary::parametersConstant r{r_};
        QLibrary::RandomMLCG rg(1,0);
        QLibrary::MCStatisticsMean gatherer_call;
        QLibrary::VanillaOption callOption(*PayoffPtr,Expiry);
        QLibrary::SimpleMonteCarlo(callOption, Spot, Vol, r, NumberOfPaths,gatherer_call,rg);
        std::cout << "Monte Carlo price of a call: " << gatherer_call.getResults()["mean"] << std::endl;
        delete PayoffPtr;
    }
    return 0;
}